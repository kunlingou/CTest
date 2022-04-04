/**
 * 
 * https://leetcode-cn.com/problems/majority-element/
 * 
 * 题目：
 * 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 * 
 * 示例：
 * 输入：[2,2,1,1,1,2,2]
 * 输出：2
 * 
 * 要求：时间复杂度为 O(n)、空间复杂度为 O(1)
 */
#include <stdio.h>
#include <sys/times.h>

#include "sort_bubble.h"

int majorityElement(int* nums, int numsSize)
{
    sort_bubble(nums, numsSize);

    // num = 10 => i = 4, 5
    // num = 9  => i = 4
    return nums[numsSize / 2];
}

#define test_majority_element_CASE_NUM 4

int test_majority_element(int argc, char** argv)
{
    int numsArr[test_majority_element_CASE_NUM][10] = {
        {3, 3, 3, 4},
        {7, 2, 2, 1, 1, 1, 2, 2},
        {3, 3, 2, 3},
        {3, 2, 3, 3}
    };

    int expect[test_majority_element_CASE_NUM] = {
        3,
        2,
        3,
        3
    };

    int *nums = NULL;
    int num;

    for (int i = 0; i < test_majority_element_CASE_NUM; i++) {

        nums = &numsArr[i][1];
        num  =  numsArr[i][0];

        int result = majorityElement(nums, num);

        if (result == expect[i]) {
            // printf("testCase[%d] execute success.\r\n", i);
        } else {
            printf("testCase[%d] execute failure.\r\n", i);
            return -1;
        }
    }
    return 0;
}

#define TEST_BUBBLE_SORT_CASE_NUM 7

int test_bubble_sort(int argc, char** argv)
{
    int numsArr[TEST_BUBBLE_SORT_CASE_NUM][10] = {
        {3, 3, 3, 4},
        {7, 2, 2, 1, 1, 1, 2, 2},
        {3, 3, 2, 3},
        {3, 2, 3, 3},
        {8, 10, 9, 8, 7, 6, 5, 4, 3},
        {8, 1, 2, 3, 4, 1, 2, 3, 4},
        {8, 1, 2, 3, 4, 8, 7, 6, 5}
    };

    int expectArr[TEST_BUBBLE_SORT_CASE_NUM][10] = {
        {3, 3, 4},
        {1, 1, 1, 2, 2, 2, 2},
        {2, 3, 3},
        {2, 3, 3},
        {3, 4, 5, 6, 7, 8, 9, 10},
        {1, 1, 2, 2, 3, 3, 4, 4},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };

    int *nums = NULL;
    int num;
    int *expect = NULL;

    int tick1 = times(NULL);

    for (int tryTimes = 0; tryTimes < 1000000; tryTimes++) {
        for (int i = 0; i < TEST_BUBBLE_SORT_CASE_NUM; i++) {

            nums = &numsArr[i][1];
            num  =  numsArr[i][0];

            sort_bubble(nums, num);

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

    printf("test_bubble_sort execute cost %d tick.\r\n", tick2 - tick1);

    return 0;
}