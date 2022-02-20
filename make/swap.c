#include <stdio.h>

void test_swap(int *pSrc, int *pDst)
{
    __asm__(
        "movl (%0), %%eax\n\t"
        "movl (%1), %%edx\n\t"
        "movl %%eax, (%1)\n\t"
        "movl %%edx, (%0)\n\t"
        ::"b"(pSrc), "c"(pDst)
    );
    return;
}

void test_swap2(int *pSrc, int *pDst)
{
    int a = *pSrc;
    *pSrc = *pDst;
    *pDst = a;
    return;
}

int main()
{
    int a = 1;
    int b = 2;
    printf("swap0: a = %d, b = %d\r\n", a, b);
    test_swap(&a, &b);
    test_swap2(&a, &b);
    printf("swap1: a = %d, b = %d\r\n", a, b);
    return 0;
}