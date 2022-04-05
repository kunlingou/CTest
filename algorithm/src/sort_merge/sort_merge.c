/**
 * 并归排序
 * 
 * 稳定、高效的排序，时间复杂度nlogn
 */
#include <stdlib.h>

inline void merge(int* nums, int left, int mid, int right, int *tmp)
{

    int cur1 = left;
    int cur2 = mid + 1;
    int cur3 = 0;

    while (cur1 <= mid && cur2 <= right) {
        tmp[cur3++] = (nums[cur1] <= nums[cur2]) ? nums[cur1++] : nums[cur2++];
    }

    while (cur1 <= mid) {
        tmp[cur3++] = nums[cur1++];
    }

    while (cur2 <= right) {
        tmp[cur3++] = nums[cur2++];
    }

    for (int i = 0; i < cur3; i++) {
        nums[left + i] = tmp[i];
    }

    return;
}

void __sort_merge(int* nums, int left, int right, int *tmp)
{

    if (left < right) {

        int id = (left + right) / 2;

        __sort_merge(nums, left, id, tmp);
        __sort_merge(nums, id + 1, right, tmp);

        merge(nums, left, id, right, tmp);
    }
}

void sort_merge(int* nums, int numsSize)
{
    int *tmp = malloc(numsSize * sizeof(int));

    __sort_merge(nums, 0, numsSize - 1, tmp);

    free(tmp);
}