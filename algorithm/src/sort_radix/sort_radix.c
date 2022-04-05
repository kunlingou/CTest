/**
 * 基数排序
 * 
 * 一种非比较型整数排序算法，根据键值的每位数字来分配桶
 */
#include <stdlib.h>

typedef struct {
    int  cnt;
    int *nums;
} SORT_BUCKET;

#define SORT_BUCKET_SIZE 10

void sort_radix(int* nums, int numsSize)
{
    SORT_BUCKET buckets[SORT_BUCKET_SIZE];
    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        buckets[i].cnt  = 0;
        buckets[i].nums = malloc(numsSize * sizeof(int));
    }

    int id, cur, nextDiv;

    for (int div = 1; div < 100000; div *= 10) {

        nextDiv = div * 10;

        for (int i = 0; i < numsSize; i++) {
            id = nums[i] % nextDiv / div;
            buckets[id].nums[buckets[id].cnt++] = nums[i];
        }

        cur = 0;

        for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
            for (int j = 0; j < buckets[i].cnt; j++) {
                nums[cur++] = buckets[i].nums[j];
            }
            buckets[i].cnt = 0;
        }
    }

    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        free(buckets[i].nums);
    }
}