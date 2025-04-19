#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For POSIX shared memory
#include <unistd.h>
#include "public.h"

int main() {
    int32_t shmFd;
    int32_t ret = SUCCESS;
    char *ptr = NULL;

    // 创建共享内存对象
    shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, SHM_PRIV);
    if (shmFd == -1) {
        printf("Shm open with problems.\n");
        return FAIL;
    }

    // 设置共享内存大小
    if (ftruncate(shmFd, SHM_SIZE) == -1) {
        printf("ftruncate with problems.\n");
        ret = FAIL;
        goto ERR1;
    }

    // 映射共享内存到进程地址空间
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    if (ptr == MAP_FAILED) {
        printf("mmap with problems.\n");
        ret = FAIL;
        goto ERR2;
    }

    const char *message = SHM_MESSAGE;
    bool isConsumerReceived = false;
    // 向共享内存写入数据
    (void)memcpy(ptr, message, SHM_MSG_SIZE);
    (void)memcpy(ptr + SHM_MSG_SIZE, &isConsumerReceived, sizeof(bool));

    // 等待消费者读取
    uint32_t loopCnt = 0;
    ShmContentT *result = (ShmContentT *)ptr;
    while (!isConsumerReceived && loopCnt < 20) {
        isConsumerReceived = result->isReceived;
        usleep(500000);
        loopCnt++;
    }

    if (!isConsumerReceived) {
        printf("Consumer didn't receive message.\n");
        ret = FAIL;
        goto ERR1;
    } else {
        printf("Consumer received message.\n");
    }
    
    // 取消映射
    if (munmap(ptr, SHM_SIZE) == -1) {
        printf("munmap with problems.\n");
        ret = FAIL;
        goto ERR1;
    }

ERR1:
    // 关闭共享内存文件描述符
    if (close(shmFd) == -1) {
        printf("close shmFd with problems.\n");
        ret = FAIL;
    }
ERR2:
    // 销毁分配的共享内存
    if (shm_unlink(SHM_NAME) == -1) {
        printf("shm_unlink with problems.\n");
        ret = FAIL;
    }
    printf("Finish producer.\n");

    return ret;
}
