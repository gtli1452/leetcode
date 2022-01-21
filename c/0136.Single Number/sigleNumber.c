#include "stdio.h"
#include "stdlib.h"

int singleNumber(int *nums, int numsSize)
{
    if (numsSize < 2)
        return *nums;

    int a = 0;

    /*
     * There are 3 key points to use the XOR operator to solve this problem:
     * 1. XOR operator is commutative. (A ^ B = B ^ A)
     * 2. A ^ A = 0;
     * 3. A ^ 0 = A;
     */
    for (int i = 0; i < numsSize; i++) {
        a ^= nums[i];
    }

    return a;
}

int main(void)
{
    int nums[] = {1, 5, -100, -100, 99, 99, 1};
    int tmp = singleNumber(nums, sizeof(nums) / sizeof(nums[0]));

    printf("single: %d", tmp);

    return 0;
}