/**
 * 堆排序
 * 
 * 一种选择排序，稳定、高效的排序，时间复杂度nlogn
 */
#include <stdlib.h>

void adjust_heap(int* nums, int numsSize, int nodeId)
{

    int tmp = nums[nodeId];
    for (int i = nodeId * 2 + 1; i < numsSize; i = i * 2 + 1) {

        if (i + 1 < numsSize && nums[i] < nums[i + 1]) {
            i++;
        }

        if (nums[i] > tmp) {
            nums[nodeId] = nums[i];
            nodeId = i;
        }
    }

    nums[nodeId] = tmp;
}

void __sort_heap(int* nums, int numsSize)
{
    if (numsSize == 1) {
        return;
    }

    for (int i = numsSize / 2 - 1; i >= 0; i--) {
        adjust_heap(nums, numsSize, i);
    }

    for (int i = numsSize - 1; i > 0; i--) {
        int tmp = nums[i];
        nums[i] = nums[0];
        nums[0] = tmp;

        adjust_heap(nums, i, 0);
    }
}

void sort_heap(int* nums, int numsSize)
{
    __sort_heap(nums, numsSize);
}