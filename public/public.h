#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAIL -1

void GenerateRandomNum(int64_t *arrForSort, uint32_t sortNum);
void SimpleBubbleSort(int64_t *arr2Save, int32_t arrLen);
int32_t SwapTwoValues(int64_t *value1, int64_t *value2);
