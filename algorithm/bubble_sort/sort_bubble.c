/**
 * 冒泡排序
 */
void sort_bubble(int* nums, int numsSize)
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
    return;
}
