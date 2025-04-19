#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAIL -1
#define SHM_NAME "shared_memory"
#define SHM_SIZE 1024
#define SHM_PRIV 0666
#define SHM_MESSAGE "Hello, have you recieved the message?"
#define SHM_MSG_SIZE strlen(SHM_MESSAGE) + 1

void GenerateRandomNum(int64_t *arrForSort, uint32_t sortNum);
void SimpleBubbleSort(int64_t *arr2Save, int32_t arrLen);
int32_t SwapTwoValues(int64_t *value1, int64_t *value2);

typedef struct ShmContent {
    const char sendMessage[50];
    bool isReceived;
} ShmContentT;
