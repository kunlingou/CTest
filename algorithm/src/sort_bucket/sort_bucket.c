/**
 * 桶排序
 */
#include <stdlib.h>

typedef struct {
    int  cnt;
    int *nums;
} SORT_BUCKET;

#define SORT_BUCKET_SIZE 10

extern void sort_quick(int* nums, int numsSize);

void sort_bucket(int* nums, int numsSize)
{
    SORT_BUCKET buckets[SORT_BUCKET_SIZE];
    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        buckets[i].cnt  = 0;
        buckets[i].nums = malloc(numsSize * sizeof(int));
    }

    SORT_BUCKET *bucket = NULL;
    int div = RAND_MAX / SORT_BUCKET_SIZE;

    for (int i = 0; i < numsSize; i++) {
        bucket = buckets + nums[i] / div;
        bucket->nums[bucket->cnt++] = nums[i];
    }

    int cur = 0;

    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        bucket = buckets + i;
        sort_quick(bucket->nums, bucket->cnt);
        for (int j = 0; j < bucket->cnt; j++) {
            nums[cur++] = bucket->nums[j];
        }
    }

    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        free(buckets[i].nums);
    }
}

extern void sort_quick1(int* nums, int numsSize);

void sort_bucket1(int* nums, int numsSize)
{
    SORT_BUCKET buckets[SORT_BUCKET_SIZE];
    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        buckets[i].cnt  = 0;
        buckets[i].nums = malloc(numsSize * sizeof(int));
    }

    SORT_BUCKET *bucket = NULL;
    int div = RAND_MAX / SORT_BUCKET_SIZE;

    for (int i = 0; i < numsSize; i++) {
        bucket = buckets + nums[i] / div;
        bucket->nums[bucket->cnt++] = nums[i];
    }

    int cur = 0;

    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        bucket = buckets + i;
        sort_quick1(bucket->nums, bucket->cnt);
        for (int j = 0; j < bucket->cnt; j++) {
            nums[cur++] = bucket->nums[j];
        }
    }

    for (int i = 0; i < SORT_BUCKET_SIZE; i++) {
        free(buckets[i].nums);
    }
}