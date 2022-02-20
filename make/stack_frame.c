#include <stdio.h>

int test_add(int a, int b)
{

    int c = a + b;

    return  c;
}

int main()
{

    int a = 1;
    int b = 2;

    int c = test_add(a, b);

    printf("c = %d\r\n", c);

    return 0;
}