/**
 * 选择排序
 */

void sort_selection(int* nums, int numsSize)
{

    int min;
    int tmp;

    for (int i = 0; i < numsSize; i++) {

        min = i;

        for (int j = i + 1; j < numsSize; j++) {

            if (nums[min] > nums[j]) {
                min = j;
            }
        }

        if (min != i) {
            tmp = nums[i];
            nums[i] = nums[min];
            nums[min] = tmp;
        }
    }
}