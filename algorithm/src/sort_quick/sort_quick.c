/**
 * 快速排序
 * 
 * https://www.runoob.com/w3cnote/quick-sort-2.html
 */

inline int paritition(int* nums, int left, int right)
{
    int tmp = nums[left];

    while (left < right) {
        
        while (left < right && nums[right] >= tmp) {
            right--;
        }
        nums[left] = nums[right];

        while (left < right && nums[left] <= tmp) {
            left++;
        }
        nums[right] = nums[left];
    }

    nums[left] = tmp;
    return left;
}

extern void sort_shell(int* nums, int numsSize);

void __sort_quick(int* nums, int left, int right)
{
    if (left < right) {

        int id = paritition(nums, left, right);

        __sort_quick(nums, left, id - 1);
        __sort_quick(nums, id + 1, right);
    }
}

void sort_quick(int* nums, int numsSize)
{
    __sort_quick(nums, 0, numsSize - 1);
}

void __sort_quick1(int* nums, int left, int right)
{
    if (right - left <= 20) {
        sort_shell(nums, right - left + 1);
        return;
    }

    if (left < right) {

        int id = paritition(nums, left, right);

        __sort_quick1(nums, left, id - 1);
        __sort_quick1(nums, id + 1, right);
    }
}

void sort_quick1(int* nums, int numsSize)
{
    __sort_quick1(nums, 0, numsSize - 1);
}