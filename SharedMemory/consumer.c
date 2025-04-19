#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For POSIX shared memory
#include <unistd.h>
#include "public.h"

int main() {
    int32_t shmFd;
    int32_t ret = SUCCESS;
    char *ptr = NULL;

    // 打开共享内存对象
    shmFd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shmFd == -1) {
        printf("shm_unlink with problems.\n");
        return FAIL;
    }

    // 映射共享内存到进程地址空间
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    if (ptr == MAP_FAILED) {
        printf("shm_unlink with problems.\n");
        ret = FAIL;
        goto ERR;
    }

    ShmContentT *result = (ShmContentT *)ptr;
    // 从共享内存读取数据
    if (strcmp(result->sendMessage, SHM_MESSAGE) == 0) {
        result->isReceived = true;
        printf("Read message successfully.\n");
    } else {
        printf("Read message with problems.\n");
    }

    // 取消映射
    if (munmap(ptr, SHM_SIZE) == -1) {
        printf("shm_unlink with problems.\n");
        ret = FAIL;
    }
ERR:
    // 关闭共享内存文件描述符
    if (close(shmFd) == -1) {
        printf("shm_unlink with problems.\n");
        ret = FAIL;
    }
    printf("Finish consumer.\n");

    return ret;
}
