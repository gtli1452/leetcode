/* Refer to https://hackmd.io/@sysprog/linux2022-quiz1#%E6%B8%AC%E9%A9%97-1 */

#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *lhs, const void *rhs)
{
    if (*(int *) lhs == *(int *) rhs)
        return 0;
    return *(int *) lhs < *(int *) rhs ? -1 : 1;
}

static int *alloc_wrapper(int a, int b, int *returnSize)
{
    *returnSize = 2;
    int *res = (int *) malloc(sizeof(int) * 2);
    res[0] = a, res[1] = b;
    return res;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int arr[numsSize][2]; /* {value, index} pair */
    for (int i = 0; i < numsSize; i++) {
        arr[i][0] = nums[i];
        arr[i][1] = i;
    }

    /*
     * Refer to
     * https://leetcode.com/problems/two-sum/discuss/189807/
     *
     * After we sort the numbers, we can find a solution in O(n) time
     *
     * 1. Start with the two indexes, pointing to the lowest (lo) and highest
     * (hi) values.
     *
     * 2. If current values are less than our target, then increase lo and hence
     * increase the sum. If the sum is greater than our target, then decrease hi
     * and hence reduce the sum.
     *
     * 3. Continue from 2. so long as the sum doesn't equal the target.
     */
    qsort(arr, numsSize, sizeof(arr[0]), cmp);

    for (int i = 0, j = numsSize - 1; i < j;) {
        if (arr[i][0] + arr[j][0] == target)
            return alloc_wrapper(arr[i][1], arr[j][1], returnSize);
        if (arr[i][0] + arr[j][0] < target)
            i++; /* decrease the sum of arr[i][0] and arr[j][0] */
        else
            j--; /* increase the sum of arr[i][0] and arr[j][0] */
    }

    *returnSize = 0;
    return NULL;
}

int main()
{
    int nums[] = {2, 12, 7, 15, 18};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 9;
    int *returnSize = (int *) malloc(sizeof(int));
    int *ans = NULL;

    ans = twoSum(nums, numsSize, target, returnSize);

    if (*returnSize != 2)
        printf("Not find");
    else
        printf("[%d, %d]", *ans, *(ans + 1));

    return 0;
}