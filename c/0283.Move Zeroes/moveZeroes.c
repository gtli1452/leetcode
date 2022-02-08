#include <stdio.h>
#include <stdlib.h>

/*
 * Brute force
 * Time complexity : O(N)
 * Space complexity: O(N)
 */
void moveZeroes(int *nums, int numsSize)
{
    /* Space complexity must be O(1) */
    int *tmp = (int *) malloc(sizeof(int) * numsSize);
    int j = 0;
    int head = 0, tail = numsSize - 1;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0)
            tmp[tail--] = nums[i];
        else
            tmp[head++] = nums[i];
        if (head > tail)
            break;
    }

    for (int i = 0; i < numsSize; i++)
        nums[i] = tmp[i];
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
 * Two-pointer
 * Time complexity : O(N)
 * Space complexity: O(1)
 */
void moveZeroes_v2(int *nums, int numsSize)
{
    /* i runs toward the end of the array, j points to the first zero-item */
    int j = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0)
            swap(&nums[i], &nums[j]);
        if (nums[j] != 0)
            j++;
    }

    /* simplied version
        for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0)
            swap(&nums[i], &nums[j++]);
    }
    */
}

/*
 * Two-pointer, move non-zero items and count numbers, then put the zero in the
 * residual of arrays.
 * Time complexity : O(N)
 * Space complexity: O(1)
 */
void moveZeroes_v3(int *nums, int numsSize)
{
    /* j point to the next position of the processed non-zero item */
    int j = 0;

    /*
     * If the current element is not 0, then we need to
     * append it just behind last non 0 element we found.
     */
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[j++] = nums[i];
        }
    }

    /*
     * After we have finished processing new elements,
     * all the non-zero elements are already at beginning of array.
     * We just need to fill remaining array with 0's.
     */
    for (int i = j; i < numsSize; i++)
        nums[i] = 0;
}

int main(void)
{
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    moveZeroes(nums, numsSize);

    for (int i = 0; i < numsSize; i++)
        printf("%d, ", nums[i]);

    return 0;
}