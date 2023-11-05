#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAIL -1
#define SORT_NUM 100       // num of nums for sort
#define MEM_BYTE_LIMIT 80  // suppose the memory limit is 80 bytes, which can save 10 int64_t nums

typedef struct FileList{
    uint32_t curIdx;
    uint32_t usedLen;
    uint32_t *fileCursors;
} FileListT;
