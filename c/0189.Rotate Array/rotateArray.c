#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * Brute force: this approach uses additional memory
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
 * Brute force: two for-loop
 * Time complexity : O(kn)
 * Space complexity: O(2)
 */
void rotate_v2(int *nums, int numsSize, int k)
{
    if (numsSize <= 1 || k == 0)
        return;

    k %= numsSize;

    for (int i = 0; i < k; i++) {
        int cur = nums[0];
        for (int j = 1; j < numsSize; j++) {
            int tmp = nums[j];
            nums[j] = cur;
            cur = tmp;
        }
        nums[0] = cur;
    }
}

void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

/* Time complexity: O(n/2)*/
void reverse(int *start, int *end)
{
    while (start < end) {
        swap(start++, end--);
    }
}

/*
 * Reverse version
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
void rotate_v3(int *nums, int numsSize, int k)
{
    if (numsSize <= 1 || k == 0)
        return;

    /* Reduce the operation.
     * E.g. nums[] = [1, 2, 3], k1 = 2, k2 = 7
     * rotate k1 step : [3, 2, 1], rotate k2 step : [3, 2, 1]
     * Obviously, rotating k1 is equivalent to rotating k2
     */
    k %= numsSize;

    /*
     *  nums[] = x[0], x[1], ..., x[len-k-1], x[len-k], ..., x[len-1]
     *             ^~~~    len-k    ~~~^          ^~~~   k    ~~~^
     *
     * the key point is that (X^T * Y^T)^T = YX, where
     * - X and Y are sub-array of nums
     * - T is the reverse operation, e.g., X = [1, 2, 3], X^T = [3, 2, 1]
     * Refer to
     * https://github.com/haoel/leetcode/blob/master/algorithms/cpp/rotateArray/rotateArray.cpp
     */
    reverse(&nums[0], &nums[numsSize - k - 1]);
    reverse(&nums[numsSize - k], &nums[numsSize - 1]);
    reverse(&nums[0], &nums[numsSize - 1]);
}

int main()
{
    int nums[] = {1, 2, 3, 4, 5};
    int k = 2;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    rotate_v2(nums, numsSize, k);

    // reverse(nums + 2, nums + numsSize - 2);

    for (int i = 0; i < numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    return 0;
}