#include <stdio.h>

void test()
{
    int a = 5;

    int b = (++a) + (++a) + (++a) + (++a);

    printf("\r\nb:%d\r\n",b);
}

void main()
{

    test();
}