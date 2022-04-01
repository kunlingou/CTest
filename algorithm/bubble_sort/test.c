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

#include "sort_bubble.h"

int majorityElement(int* nums, int numsSize)
{
    sort_bubble(nums, numsSize);
    return nums[numsSize / 2];
}

#define CASE_NUM 4

int main(int argc, char** argv)
{
    int numsArr[CASE_NUM][10] = {
        {3, 3, 3, 4},
        {7, 2, 2, 1, 1, 1, 2, 2},
        {3, 3, 2, 3},
        {3, 2, 3, 3}
    };

    int expect[CASE_NUM] = {
        3,
        2,
        3,
        3
    };

    int *nums = NULL;
    int num;

    for (int i = 0; i < CASE_NUM; i++) {

        nums = &numsArr[i][1];
        num  =  numsArr[i][0];

        int result = majorityElement(nums, num);

        if (result == expect[i]) {
            printf("testCase[%d] execute success.\r\n", i);
        } else {
            printf("testCase[%d] execute failure.\r\n");
        }
    }
    return 0;
}