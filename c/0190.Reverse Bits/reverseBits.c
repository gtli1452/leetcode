#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t reverseBits(uint32_t n)
{
    uint32_t rev = 0;

    for (int i = 0; i < 32; i++) {
        rev = (rev << 1) + (n % 2);
        n = n >> 1;
    }

    return rev;
}

int main()
{
    uint32_t x = 0b00000010100101000001111010011100;
    uint32_t y = 0;

    y = reverseBits(x);

    printf("Original:%d\n", x);
    printf("Rverse  :%d\n", y);
    return 0;
}
