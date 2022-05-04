#include <stdio.h>

enum Rainbow{
    red=1,
    orage,
    yellow,
    green,
    blue,
    indigo,
    violet
};


int main()
{
    enum Rainbow rainbow;

    rainbow = yellow;

    printf("%d\n", rainbow);

    printf("Hello, World!\n");
    printf("Hello. - from Yoonwoo.\n");

    int *p = NULL;
    *p = 1;

    return 0;
}

