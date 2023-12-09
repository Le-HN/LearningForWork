#include "external_sort.h"

static void SortAndSave2File(int64_t *arr2Save, int32_t arrLen, FileListT *fileList)
{
    // simple bubble sort
    SimpleBubbleSort(arr2Save, arrLen);
    // save sorted list to file
    FILE *fp = NULL;
    char filePath[20] = {0};
    sprintf(filePath, "./tempfile_%ld.txt", fileList->curIdx);
    fp = fopen(filePath, "w");
    fwrite((void *)arr2Save, sizeof(int64_t) * arrLen, 1, fp);
    fclose(fp);
    fileList->curIdx++;
    fileList->usedLen++;
}

static void ExecuteExternalSort(int64_t *arrForSort)
{
    int32_t itemNum = MEM_BYTE_LIMIT / sizeof(int64_t);
    int64_t *arrMem = (int64_t *)malloc(itemNum * sizeof(int64_t));
    memset(arrMem, 0, itemNum * sizeof(int64_t));
    FileListT fileList = {
        .curIdx = 0,
        .usedLen = 0,
    };
    int32_t numInMem = 0;
    for (uint32_t i = 0; i < SORT_NUM; i++) {
        if (numInMem >= itemNum) {
            SortAndSave2File(arrMem, numInMem, &fileList);
            numInMem = 0;
        }
        arrMem[numInMem] = arrForSort[i];
        numInMem++;
    }
    // the last batch in mem, we only consider the length of last batch is the same as previous batches now
    if (numInMem != 0) {
        SortAndSave2File(arrMem, numInMem, &fileList);
        numInMem = 0;
    }
    memset(arrMem, 0, itemNum * sizeof(int64_t));
    fileList.fileCursors = (uint32_t *)malloc(sizeof(uint32_t) * fileList.usedLen);
    memset(fileList.fileCursors, 0, fileList.usedLen * sizeof(uint32_t));
    uint32_t arrMemIdx = 0;
    while (true) {
        uint32_t minFileIdx = 0;
        int64_t minValue = INT64_MAX;
        uint32_t emptyCounter = 0;
        for (uint32_t i = 0; i < fileList.usedLen; i++) {
            if (fileList.fileCursors[i] < itemNum) {
                FILE *fp = NULL;
                char filePath[20] = {0};
                sprintf(filePath, "./tempfile_%ld.txt", i);
                fp = fopen(filePath, "r");
                fseek(fp, fileList.fileCursors[i] * sizeof(int64_t), SEEK_SET);
                int64_t value;
                fread(&value, sizeof(int64_t), 1, fp);
                if (minValue > value) {
                    minValue = value;
                    minFileIdx = i;
                }
                fclose(fp);
            } else {
                emptyCounter++;
            }
        }
        if (emptyCounter >= itemNum) {
            break;
        }
        arrMem[arrMemIdx] = minValue;
        arrMemIdx++;
        fileList.fileCursors[minFileIdx]++;
        if (arrMemIdx >= itemNum) {
            FILE *fp = NULL;
            char filePath[20] = "final_result.txt";
            fp = fopen(filePath, "a");
            for (uint32_t i = 0; i < itemNum; i++) {
                fprintf(fp, "%ld\n", arrMem[i]);
            }
            fclose(fp);
            arrMemIdx = 0;
        }
    }
    free(arrMem);
    free(fileList.fileCursors);
}

bool IsResultCorrect()
{
	FILE* f1, * f2;
	uint32_t size1, size2;
	char buffer1[1024], buffer2[1024];
	f1 = fopen("./final_result.txt", "rb+");
	f2 = fopen("./expected.txt", "rb+");
	while (true)
	{
		size1 = fread(buffer1, 1, 1024, f1);
		size2 = fread(buffer2, 1, 1024, f2);
		if (size1 != size2)
		{
			goto ERROR;
		}
		if (size1 < 1)
			break;
		for (int i = 0; i < size1; i++)
		{
			if (buffer1[i] != buffer2[i])
			{
				goto ERROR;
			}
		}
	}
	return true;
ERROR:
	if (f1)
		fclose(f1);
	if (f2)
		fclose(f2);
	return false;
}

static int32_t VerifyResult(int64_t *arrForSort)
{
    SimpleBubbleSort(arrForSort, SORT_NUM);
    FILE *fp = NULL;
    const char *filePath = "./expected.txt";
    fp = fopen(filePath, "w");
    for (uint32_t i = 0; i < SORT_NUM; i++) {
        fprintf(fp, "%ld\n", arrForSort[i]);
    }
    fclose(fp);
    if (!IsResultCorrect) {
        return FAIL;
    }
    return SUCCESS;
}

int32_t main()
{
    int64_t arrayForSort[SORT_NUM] = {0};
    system("rm -rf ./final_result.txt");
    system("rm -rf ./expected.txt");
    GenerateRandomNum(arrayForSort, SORT_NUM);
    ExecuteExternalSort(arrayForSort);
    int32_t ret = VerifyResult(arrayForSort);
    if (ret != SUCCESS) {
        printf("Result incorrect!\n");
    }
    printf("Success!\n");
    system("rm -rf ./tempfile*");
    return ret;
}
