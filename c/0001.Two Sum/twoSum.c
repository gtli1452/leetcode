#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Brute force
 * Time complexity : O(N^2)
 * Space complexity: O(1)
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *ans = (int *) malloc(sizeof(int) * 2);

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                *ans = i;
                *(ans + 1) = j;
            }
        }
    }

    return ans;
}

int main()
{
    int nums[] = {2, 7, 11, 13, 17};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;
    int *ansPtr = NULL;

    ansPtr = twoSum(nums, numsSize, 9, &returnSize);

    printf("[%d, %d]", *ansPtr, *(ansPtr + 1));
    return 0;
}
