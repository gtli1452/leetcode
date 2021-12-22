#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int hammingWeight(uint32_t n)
{
    int bit_number = 0;

    while (n) {
        n &= n - 1;
        bit_number++;
    }

    return bit_number;
}

int main()
{
    int num = 0xffa;
    int x = hammingWeight(num);

    printf("num is 0x%x, numbers of 1 bits of num is %d\n", num, x);
    return 0;
}
