#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    char buf[PATH_MAX];
    realpath("/home/min/a/jiang85/prog1/tests", buf);
    printf("path: %s\n",buf);
    return 0;
}