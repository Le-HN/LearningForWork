#include "public.h"

void GenerateRandomNum(int64_t *arrForSort, uint32_t sortNum)
{
    for (uint32_t i = 0; i < sortNum; i++) {
        arrForSort[i] = rand();
        printf("%d: %ld\n", i, arrForSort[i]);
    }
}

void SimpleBubbleSort(int64_t *arr2Save, int32_t arrLen)
{
    for (uint32_t i = 0; i < arrLen; i++) {
        for (uint32_t j = 0; j < arrLen - i - 1; j++) {
            if (arr2Save[j] > arr2Save[j + 1]) {
                uint32_t temp = arr2Save[j];
                arr2Save[j] = arr2Save[j + 1];
                arr2Save[j + 1] = temp;
            }
        }
    }
}

int32_t SwapTwoValues(int64_t *value1, int64_t *value2)
{
    if (value1 == NULL || value2 == NULL) {
        return FAIL;
    }
    int64_t tmp = *value1;
    *value1 = *value2;
    *value2 = tmp;
    return SUCCESS;
}
