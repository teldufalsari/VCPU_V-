#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sys/stat.h>
#include "VCPU.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
        exit(-1);


    struct stat buf;
    stat(argv[1], &buf);

    FILE* input = fopen(argv[1], "rb");

    char* code = (char*) calloc(buf.st_size, sizeof(char));

    fread(code, sizeof(char), buf.st_size, input);

    fclose(input);

    run(code);

    free(code);

    return 0;
}