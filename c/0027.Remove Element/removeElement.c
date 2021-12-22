#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

int removeElement(int *nums, int numsSize, int val)
{
    if (nums == NULL || numsSize == 0)
        return 0;

    int j = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != val) {
            nums[j++] = nums[i];
        }
    }

    /*
     * j points to the next position to put the item which is not equal val.
     * j is the length of modified elements, it's different with 0026.Remove
     * Duplicates From Sorted Array.
     */
    return j;
}

int main()
{
    int nums[] = {2, 1, 0, 2, 4, 4, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int val = 2;

    int k = removeElement(nums, numsSize, val);

    for (int i = 0; i < k; i++) {
        printf("%d, ", nums[k]);
    }
    return 0;
}
