/**
 * 希尔排序
 * 
 * 针对直接插入排序算法的改进
 * 
 * https://www.runoob.com/data-structures/shell-sort.html
 */

void sort_shell(int* nums, int numsSize)
{

    int tmp, j;

    for (int gap = numsSize / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < numsSize; i++) {
            for (j = i; j >= gap && nums[j] < nums[j - gap]; j -= gap) {
                tmp = nums[j- gap];
                nums[j - gap] = nums[j];
                nums[j] = tmp;
            }
        }
    }

    return;
}