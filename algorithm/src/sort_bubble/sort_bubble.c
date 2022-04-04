/**
 * 冒泡排序
 * 
 * 举例：
 * 
 * 输入：
 * 10,  1, 35, 61, 89, 36, 55
 * 
 * 第1轮（比较6次）：
 * 10,  1, 35, 61, 89, 36, 55 => [ 1, 10], 35, 61, 89, 36, 55  ---- 发生交换
 *  1, 10, 35, 61, 89, 36, 55 =>  1, [10, 35], 61, 89, 36, 55
 *  1, 10, 35, 61, 89, 36, 55 =>  1, 10, [35, 61], 89, 36, 55
 *  1, 10, 35, 61, 89, 36, 55 =>  1, 10, 35, [61, 89], 36, 55
 *  1, 10, 35, 61, 89, 36, 55 =>  1, 10, 35, 61, [36, 89], 55  ---- 发生交换
 *  1, 10, 35, 61, 36, 89, 55 =>  1, 10, 35, 61, 36, [55, 89]  ---- 发生交换
 *  1, 10, 35, 61, 36, 55, 89
 * 
 * 第2轮（比较5次）：
 *  1, 10, 35, 61, 36, 55, 89 =>  [1, 10], 35, 61, 36, 55, 89
 *  1, 10, 35, 61, 36, 55, 89 =>  1, [10, 35], 61, 36, 55, 89
 *  1, 10, 35, 61, 36, 55, 89 =>  1, 10, [35, 61], 36, 55, 89
 *  1, 10, 35, 61, 36, 55, 89 =>  1, 10, 35, [36, 61], 55, 89  ---- 发生交换
 *  1, 10, 35, 36, 61, 55, 89 =>  1, 10, 35, 36, [55, 61], 89  ---- 发生交换
 *  1, 10, 35, 36, 55, 61, 89
 * 
 * 第3轮（比较4次）：
 *  1, 10, 35, 36, 55, 61, 89
 * 
 * 优化点：
 *     1. 当发现当前轮次无交换时，说明已经达到最终结果，不再继续往下比较。
 *     2. 每一轮获取当前轮次第1次替换的位置，下一次从当前位置-1处开始比较。 ---- 效果不好，实现参考sort_bubble2
 */

#ifdef __DEBUG__
#include <stdio.h>
#endif

#define INT_INVALID_VAL 0xFFFFFFFF

void sort_bubble(int* nums, int numsSize)
{
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

    return;
}

void sort_bubble1(int* nums, int numsSize)
{
    int tmp;
    for (int i = 0; i < numsSize; i++) {
        tmp = INT_INVALID_VAL;
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j +1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
        if (tmp == INT_INVALID_VAL) {
            break;
        }
#ifdef __DEBUG__
        printf("nums: ");
        for (int k = 0; k < numsSize; k++) {
            printf("%d ", nums[k]);
        }
        printf("\r\n");
#endif
    }

    return;
}

void sort_bubble2(int* nums, int numsSize)
{
    int tmp;
    int start = 0;
    for (int i = 0; i < numsSize; i++) {
        tmp = INT_INVALID_VAL;
        for (int j = start; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                if (tmp == INT_INVALID_VAL && j > 0) {
                    start = j - 1;
                }
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
        if (tmp == INT_INVALID_VAL) {
            break;
        }
    }

    return;
}
