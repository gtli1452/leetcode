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

    k %= numsSize;
    int tmp[numsSize];

    // copy the last k items
    for (int i = 0; i < k; i++) {
        tmp[i] = nums[numsSize - k + i];
    }
    // copy the first numsSize - k items
    for (int i = 0; i < numsSize - k; i++) {
        tmp[i + k] = nums[i];
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

    /*
     * Refer to
     * http://leetcode.wang/leetcode-189-Rotate-Array.html#%E8%A7%A3%E6%B3%95%E4%B8%80
     */
    for (int i = 0; i < k; i++) {
        int last = nums[numsSize - 1];
        for (int j = numsSize - 1; j > 0; j--) {
            nums[j] = nums[j - 1];
        }
        nums[0] = last;
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
     *  nums[] = x[0], x[1], ..., x[n-k-1], x[n-k], ..., x[n-1]
     *             ^~~~    n-k    ~~~^         ^~~~   k   ~~~^
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

/*
 * This is the reduced-memory version of the solution 1.
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
void rotate_v4(int *nums, int numsSize, int k)
{
    k %= numsSize;
    if (numsSize <= 1 || k == 0)
        return;

    int cur = 0, next = k;
    int used = cur;
    int tmp, data = nums[cur];

    for (int i = 0; i < numsSize; i++) {
        tmp = nums[next];
        nums[next] = data;
        data = tmp;

        /*
         * if cur = used, it means that we meet a circle. So move the next one
         * Refer to haoel's rotate2:
         * https://github.com/haoel/leetcode/blob/master/algorithms/cpp/rotateArray/rotateArray.cpp
         */
        cur = next;
        if (cur == used) {
            used = ++cur;
            data = nums[cur];
        }
        next = (cur + k) % numsSize;
    }
}

/*
 * Very concise version
 * Refer to
 * https://leetcode.com/problems/rotate-array/discuss/54263/3-lines-of-c-in-one-pass-using-swap
 * Time complexity : O(n-1)
 * Space complexity: O(1)
 */
void rotate_v5(int nums[], int n, int k)
{
    if (n == 0)
        return;
    /*
     * The outer loop determines how many items have not been processed, and `k`
     * means that `k` steps to rotate (i.e. the last `k` items will be put
     * to the front).
     *
     * After every outer loop, `k` item will be processed (that's the meaning
     * for `n-=k`).
     *
     * The inner loop swaps the last `k` items to the correct position (move
     * to the front).
     *
     * The netizen's explanation:
     * https://leetcode.com/problems/rotate-array/discuss/54263/3-lines-of-C++-in-one-pass-using-swap/55914
     */
    for (; k %= n; n -= k)
        for (int i = 0; i < k; i++)
            swap(nums++, &nums[n - k]);

    /*
     * A version without undefined behavior (if n = 0) and easier to understand.
     * for (; k %= n; n -= k, nums += k)
     *     for (int i = 0; i < k; i++)
     *         swap(nums[i], nums[n - k + i]);
     */
}

int main()
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    rotate_v5(nums, numsSize, k);

    for (int i = 0; i < numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    return 0;
}