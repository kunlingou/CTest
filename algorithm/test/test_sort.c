/**
 * 选择排序
 */
#include <stdio.h>
#include <sys/times.h>

#define TEST_BUBBLE_SORT_CASE_NUM 8

typedef void (*sort_func)(int* nums, int numsSize);

int test_sortByFunc(int argc, char** argv, char *funcName, sort_func func)
{
    int numsArr[TEST_BUBBLE_SORT_CASE_NUM][10] = {
        {3, 3, 3, 4},
        {7, 2, 2, 1, 1, 1, 2, 2},
        {3, 3, 2, 3},
        {3, 2, 3, 3},
        {8, 10, 9, 8, 7, 6, 5, 4, 3},
        {8, 1, 2, 3, 4, 1, 2, 3, 4},
        {8, 1, 2, 3, 4, 8, 7, 6, 5},
        {8, 7, 6, 9, 3, 1, 5, 2, 4}
    };

    int expectArr[TEST_BUBBLE_SORT_CASE_NUM][10] = {
        {3, 3, 4},
        {1, 1, 1, 2, 2, 2, 2},
        {2, 3, 3},
        {2, 3, 3},
        {3, 4, 5, 6, 7, 8, 9, 10},
        {1, 1, 2, 2, 3, 3, 4, 4},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 9}
    };

    int *nums = NULL;
    int num;
    int *expect = NULL;

    int tick1 = times(NULL);

    for (int tryTimes = 0; tryTimes < 2000000; tryTimes++) {
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
    }

    int tick2 = times(NULL);

    printf("[%s] execute cost %d tick.\r\n", funcName, tick2 - tick1);

    return 0;
}

int __test_sort(int argc, char** argv, char *funcName, sort_func func)
{
    int ret = 0;

    printf("[%s] suit start.\r\n", funcName);
    ret = test_sortByFunc(argc, argv, funcName, func);
    printf("[%s] suit end result = %d.\r\n", funcName, ret);

    return ret;
}

extern void sort_bubble(int* nums, int numsSize);
extern void sort_bubble2(int* nums, int numsSize);
extern void sort_insertion(int* nums, int numsSize);
extern void sort_selection(int* nums, int numsSize);
extern void sort_shell(int* nums, int numsSize);

int test_sort(int argc, char** argv)
{    
    __test_sort(argc, argv, "sort_bubble",    sort_bubble);
    __test_sort(argc, argv, "sort_bubble2",   sort_bubble2);
    __test_sort(argc, argv, "sort_insertion", sort_insertion);
    __test_sort(argc, argv, "sort_selection", sort_selection);
    __test_sort(argc, argv, "sort_shell",     sort_shell);    

    return 0;
}