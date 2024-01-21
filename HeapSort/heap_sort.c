#include "heap_sort.h"

static void ExecuteHeapSort(int64_t *arrayForSort, int64_t *resArray)
{
    uint32_t curHeapBottom = SORT_NUM - 1;
    while (curHeapBottom > 0) {
        uint32_t curIdx = curHeapBottom;
        // move the biggest value to root
        while (curIdx > 0) {
            if (arrayForSort[(curIdx - 1) / 2] < arrayForSort[curIdx]) {
                int32_t ret = SwapTwoValues(&arrayForSort[(curIdx - 1) / 2], &arrayForSort[curIdx]);
                if (ret != SUCCESS) {
                    printf("Swap values failed during moving biggest value to root!\n");
                }
            }
            curIdx--;
        }
        // save root value to the last val in res value and set curHeapBottom
        int32_t ret = SwapTwoValues(&arrayForSort[0], &arrayForSort[curHeapBottom]);
        if (ret != SUCCESS) {
            printf("Swap values failed during switching root value with the last value!\n");
        }
        resArray[curHeapBottom] = arrayForSort[curHeapBottom];
        curHeapBottom--;
    }
    resArray[curHeapBottom] = arrayForSort[curHeapBottom];
}

static int32_t VerifyResult(int64_t *arrayForSort, int64_t *resArray)
{
    SimpleBubbleSort(arrayForSort, SORT_NUM);
    for (uint32_t i = 0; i < SORT_NUM; i++) {
        if (arrayForSort[i] != resArray[i]) {
            return FAIL;
        }
        printf("%ld\n", resArray[i]);
    }
    return SUCCESS;
}

int32_t main()
{
    int64_t arrayForSort[SORT_NUM] = {0};
    int64_t resArray[SORT_NUM] = {0};
    GenerateRandomNum(arrayForSort, SORT_NUM);
    ExecuteHeapSort(arrayForSort, resArray);
    int32_t ret = VerifyResult(arrayForSort, resArray);
    if (ret != SUCCESS) {
        printf("Result incorrect!\n");
        return ret;
    }
    printf("Success!\n");
    return ret;
}
