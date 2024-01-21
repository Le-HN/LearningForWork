#include "multi_thread.h"

static uint32_t g_execCounter = 0;
pthread_mutex_t mutex;
typedef struct ThreadArgs
{
    int32_t arg;
} ThreadArgsT;


void ThreadExec(void *arg)
{
    ThreadArgsT *threadIdx = (ThreadArgsT *)arg;
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Running thread %d...\n", threadIdx->arg);
    for (uint32_t i = 0; i < TRD_CNT_NUM; i++) {
        g_execCounter++;
    }
    printf("Global counter value is %d.\n", g_execCounter);
    sleep(1);
    pthread_mutex_unlock(&mutex);
}

int32_t main()
{
    pthread_t threadIds[THREAD_NUM] = {0};
    ThreadArgsT arg[THREAD_NUM] = {0};
    for (uint32_t i = 0; i < THREAD_NUM; i++) {
        arg[i].arg = i;
    }
    int32_t ret = SUCCESS;
    for (uint32_t i = 0; i < THREAD_NUM; i++) {
        ret = pthread_create(&threadIds[i], NULL, (void *)ThreadExec, (void *)(&arg[i]));
        if (ret != SUCCESS) {
            printf("Create thread with problem!\n");
            return ret;
        }
    }
    printf("Running main...\n");
    for (uint32_t i = 0; i < THREAD_NUM; i++) {
        ret = pthread_join(threadIds[i], NULL);
        if (ret != SUCCESS) {
            printf("Join thread with problem!\n");
            return ret;
        }
    }
    printf("Success!\n");
    return ret;
}
