#include <stdio.h>

extern int test_sort(int argc, char** argv);

int main(int argc, char** argv)
{

#ifdef __DEBUG__
    printf("debug version.\r\n");
#else
    printf("release version.\r\n");
#endif

    test_sort(argc, argv);

    return 0;
}