/**
 * 选择排序
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>


int cmpFunc(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

void test_qsort(int* nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), cmpFunc);
}

#define TEST_BUBBLE_SORT_CASE_NUM 9

typedef void (*sort_func)(int* nums, int numsSize);

int test_sortByFunc(int argc, char** argv, sort_func func)
{
    int numsArr[TEST_BUBBLE_SORT_CASE_NUM][20] = {
        {15, 3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48},
        {3, 3, 3, 4},
        {7, 2, 2, 1, 1, 1, 2, 2},
        {3, 3, 2, 3},
        {3, 2, 3, 3},
        {8, 10, 9, 8, 7, 6, 5, 4, 3},
        {8, 1, 2, 3, 4, 1, 2, 3, 4},
        {8, 1, 2, 3, 4, 8, 7, 6, 5},
        {8, 7, 6, 9, 3, 1, 5, 2, 4},
    };

    int expectArr[TEST_BUBBLE_SORT_CASE_NUM][20] = {
        {2, 3, 4, 5, 15, 19, 26, 27, 36, 38, 44, 46, 47, 48, 50},
        {3, 3, 4},
        {1, 1, 1, 2, 2, 2, 2},
        {2, 3, 3},
        {2, 3, 3},
        {3, 4, 5, 6, 7, 8, 9, 10},
        {1, 1, 2, 2, 3, 3, 4, 4},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 9},
    };

    int *nums = NULL;
    int num;
    int *expect = NULL;

    for (int i = 0; i < TEST_BUBBLE_SORT_CASE_NUM; i++) {

        nums = &numsArr[i][1];
        num  =  numsArr[i][0];

        func(nums, num);

        expect = expectArr[i];

        for (int j = 0; j < num; j++) {
            if (nums[j] != expect[j]) {
                printf("testCase[%d] execute failure expect [%d] = %d, actual = %d.\r\n", i, j, expect[j], nums[j]);
                return -1;
            }
        }
    }

    return 0;
}

int g_testPerfArrSize = 1000;
int g_testPerfArrNum  = 1000;

int test_sortPerfByFunc(int argc, char** argv, sort_func func)
{
    int arrSize   = g_testPerfArrSize;
    int arrNum    = g_testPerfArrNum;
    int *perfNums = malloc(sizeof(int) * arrSize);

    int tick1 = times(NULL);

    // int maxTimes = 10000000 / perfNum;

    for (int tryTimes = 0; tryTimes < arrNum; tryTimes++) {
        for (int i = 0; i < arrSize; i++) {
            perfNums[i] = rand();
        }
        func(perfNums, arrSize);
    }

    int tick2 = times(NULL);

    free(perfNums);

    return tick2 - tick1;
}

int test_sort_one(int argc, char** argv, char *funcName, sort_func func)
{
    int ret = test_sortByFunc(argc, argv, func);
    int cost = test_sortPerfByFunc(argc, argv, func);
    printf("%20s %20s %20d\r\n", funcName, ret == 0 ? "OK" : "NOK", cost);

    return ret;
}

extern void sort_bubble(int* nums, int numsSize);
extern void sort_bubble2(int* nums, int numsSize);
extern void sort_bubble1(int* nums, int numsSize);
extern void sort_insertion(int* nums, int numsSize);
extern void sort_selection(int* nums, int numsSize);
extern void sort_shell(int* nums, int numsSize);
extern void sort_quick(int* nums, int numsSize);
extern void sort_quick1(int* nums, int numsSize);

int __test_sort(int argc, char** argv)
{
    printf("arr[size: %d, num: %d]\r\n", g_testPerfArrSize, g_testPerfArrNum);
    printf("%20s %20s %20s\r\n", "name", "result", "costTick");
    test_sort_one(argc, argv, "sort_quick1",    sort_quick1);
    test_sort_one(argc, argv, "sort_quick",     sort_quick);
    test_sort_one(argc, argv, "sort_shell",     sort_shell);
    test_sort_one(argc, argv, "test_qsort",     test_qsort);
    test_sort_one(argc, argv, "sort_insertion", sort_insertion);
    test_sort_one(argc, argv, "sort_bubble",    sort_bubble);
    test_sort_one(argc, argv, "sort_bubble1",   sort_bubble1);
    test_sort_one(argc, argv, "sort_bubble2",   sort_bubble2);
    test_sort_one(argc, argv, "sort_selection", sort_selection);
    printf("\r\n");
    return 0;
}

int test_sort(int argc, char** argv)
{
    printf("Sorting algorithm performance test:\r\n\r\n");

    g_testPerfArrSize = 10;
    g_testPerfArrNum  = 100000;
    __test_sort(argc, argv);

    g_testPerfArrSize = 100;
    g_testPerfArrNum  = 10000;
    __test_sort(argc, argv);

    g_testPerfArrSize = 1000;
    g_testPerfArrNum  = 1000;
    __test_sort(argc, argv);

    g_testPerfArrSize = 10000;
    g_testPerfArrNum  = 100;
    __test_sort(argc, argv);

    g_testPerfArrSize = 100000;
    g_testPerfArrNum  = 10;
    __test_sort(argc, argv);
    return 0;
}