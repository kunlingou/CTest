/**
 * 插入排序
 * 
 * https://www.runoob.com/data-structures/insertion-sort.html
 */

void sort_insertion(int* nums, int numsSize)
{

    int tmp;

    for (int i = 0; i < numsSize - 1; i++) {

        for (int j = i; j >= 0; j--) {

            if (nums[j] > nums[j + 1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}