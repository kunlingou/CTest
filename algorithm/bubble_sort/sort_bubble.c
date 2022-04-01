/**
 * 
 * 冒泡排序
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

int majorityElement2(int* nums, int numsSize)
{
    // num = 10
    // i = 0 => j = 0->8
    // i = 1 => j = 0->7
    int tmp;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp; 
            }
        }
    }

    // num = 10 => i = 4, 5
    // num = 9  => i = 4
    return nums[numsSize / 2];
}

int majorityElement(int* nums, int numsSize)
{
    int cur = nums[0];
    int cnt = 1;
    for (int i = 1; i < numsSize; i++) {

        if (cur == nums[i]) {
            cnt++;
            continue;
        }

        if (cnt) {
            cnt--;
            continue;
        }

        cur = nums[i];
    }

    return cur;
}

int main(int argc, char argv[])
{

    int nums[] = {3, 3, 4};

    int result = majorityElement(nums, sizeof(nums)/sizeof(nums[0]));

    printf("\r\nresult: %d\r\n", result);

    return 0;
}