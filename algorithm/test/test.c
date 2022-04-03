#include <stdio.h>

extern int test_majority_element(int argc, char** argv);
extern int test_bubble_sort(int argc, char** argv);

int main(int argc, char** argv)
{
    int ret = 0;
    printf("suit test_majority_element start.\r\n");
    ret = test_majority_element(argc, argv);
    printf("suit test_majority_element end result = %d.\r\n", ret);
    printf("suit test_bubble_sort start.\r\n");
    ret = test_bubble_sort(argc, argv);
    printf("suit test_bubble_sort end result = %d.\r\n", ret);

    return 0;
}