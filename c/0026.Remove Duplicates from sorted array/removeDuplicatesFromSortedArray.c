#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

int removeDuplicates(int *nums, int numsSize)
{
    // Check nums[] is not NULL and numsSize is not zero.
    if (nums == NULL || numsSize == 0)
        return 0;

    int cnt = 1;  // counter for unique item.
    int *run = nums, *walk = nums;

    /*
     * There are two pointers, run and walk. The 'run' goes toward the end of
     * nums[], and the 'walk' points to the end of modified items.
     *
     * In the process of running to the end of nums[], if we find the
     * non-duplicate, 'walk' 1-step and put the value to the position which
     * 'walk' points to.
     */
    for (int i = 0; i < numsSize - 1; i++) {
        if (*run != *++run) {
            walk[++cnt] = *run;
        }
    }

    return cnt;
}

/* Simplied the code */
int removeDuplicates_v2(int *nums, int numsSize)
{
    if (numsSize <= 1)
        return numsSize;

    int j = 0;  // the index of the modified items

    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i] != nums[i + 1]) {  // check non-duplicates
            nums[++j] = nums[i + 1];   // j+1 first, then put the unique item.
        }
    }

    // j points to the last of unique elements, so the length is j + 1.
    return j + 1;
}

/* Change the checking condition */
int removeDuplicates_v3(int *nums, int numsSize)
{
    if (nums == NULL || numsSize == 0)
        return 0;

    int j = 0;  // the index of the modified items

    /*
     * Check the fast-runner i and the slow-runner j, if we find
     * nums[i] != nums[j], put the value (i.e. nums[i]) to nums[j+1].
     *
     * Note the start and the end of i are different from v2. We skip the i=0
     * (no need to check nums[i=0] and nums[j=0], it's always the same.) and the
     * i will run to the end of array.
     */
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[j]) {
            nums[++j] = nums[i];
        }
    }

    // j points to the last of unique elements, so the length is j + 1.
    return j + 1;
}

/* using while loop */
int removeDuplicates_v4(int *nums, int numsSize)
{
    if (nums == NULL || numsSize == 0)
        return 0;

    int i = 1;  // nums[i=0] and nums[j=0] are same.
    int j = 0;  // the index of the modified items

    while (i < numsSize) {
        if (nums[i] != nums[j])
            nums[++j] = nums[i];
        i++;
    }

    // j points to the last of unique elements, so the length is j + 1.
    return j + 1;
}

int main()
{
    int nums[] = {0, 0, 1, 2, 2, 4, 4, 4, 5};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = removeDuplicates(nums, numsSize);

    for (int i; i < k; i++) {
        printf("%d, ", nums[i]);
    }
    return 0;
}