#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    long int x = 0x0000FFFE;
    char str[5] = {0};

    memcpy(str, &x, 4);

    return 0;
}
