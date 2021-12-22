#include <stdio.h>
#include <stdlib.h>

_Bool isPowerOfFour(int num)
{
    return num > 0 && !(num & (num - 1)) && num & 0x55555555;
    // return (num > 0) && (!(num & (num - 1))) && !((num - 1) % 3);
}

int main()
{
    int num = 12;
    _Bool x = isPowerOfFour(num);

    printf("num is %d\n", num);

    if (x)
        printf("num is power of 4!\n");
    else
        printf("num is not power of 4!\n");
    return 0;
}
