#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    FILE *fp;
    fp = fopen("tmp", "w");
    if (fp == NULL) {
        // fprintf(stderr, "fopen() failed! errno = %d\n", errno);
        perror("fopen()");
        exit(1);
    }
    puts("OK!");
    fclose(fp);
    exit(0);
}