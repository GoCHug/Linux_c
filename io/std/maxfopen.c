#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int count = 0;
    FILE *fp;
    while (1) {
        fp = fopen("tmp", "r");
        if (fp == NULL) {
            perror("fopen()");
            break;
        }
        count++;
    }
    printf("count = %d\n",count);

    exit(0);
}