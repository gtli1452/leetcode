#include <stdio.h>
#include <stdlib.h>

_Bool isPowerOfTwo(int n)
{
    return n > 0 && !(n & (n - 1));
}

int main()
{
    int num = 12;
    _Bool x = isPowerOfTwo(num);

    printf("num is %d\n", num);

    if (x)
        printf("num is power of 2!\n");
    else
        printf("num is not power of 2!\n");
    return 0;
}
