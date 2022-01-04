#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * Brute fore, this approach uses additional memory
 * Time complexity : O(2n)
 * Space complexity: O(n)
 */
void rotate(int *nums, int numsSize, int k)
{
    if (numsSize <= 1 || k == 0)
        return;

    int tmp[numsSize];

    for (int i = 0; i < numsSize; i++) {
        tmp[(i + k) % numsSize] = nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        nums[i] = tmp[i];
    }
}

/*
 * Brute fore, two for-loop
 * Time complexity : O(n^k)
 * Space complexity: O(2)
 */
void rotate_v2(int *nums, int numsSize, int k)
{
    if (numsSize <= 1 || k == 0)
        return;

    int right;
    int left = nums[0];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < numsSize; j++) {
            right = nums[(j + 1) % numsSize];
            nums[(j + 1) % numsSize] = left;
            left = right;
        }
        left = nums[0];
    }
}

int main()
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    rotate_v2(nums, numsSize, k);

    for (int i = 0; i < numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    return 0;
}