#include "stdio.h"
#include "stdlib.h"

int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    *returnSize = 0;

    int *ans = (int *) malloc(sizeof(int) * (digitsSize + 1));
    int carry = 1;

    for (int i = digitsSize - 1; i >= 0; i--) {
        ans[i + 1] = digits[i] + carry;

        if (ans[i + 1] > 9) {
            carry = 1;
            ans[i + 1] -= 10;
        } else {
            carry = 0;
        }

        (*returnSize)++;
    }

    if (carry) {
        ans[0] = carry;
        (*returnSize)++;
    } else {
        ans++;
    }

    return ans;
}

int main(void)
{
    int digits[] = {1, 2, 3};
    int returnSize;
    int digitsSize = sizeof(digits) / sizeof(digits[0]);
    int *ans = plusOne(digits, digitsSize, &returnSize);


    for (int i = 0; i < digitsSize; i++)
        printf("%d, ", digits[i]);

    printf("\n");

    for (int i = 0; i < returnSize; i++)
        printf("%d, ", ans[i]);

    if (returnSize > digitsSize)
        free(ans);
    else
        free(--ans);

    return 0;
}