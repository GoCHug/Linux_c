#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *fp;
    // 一定要初始化，否则指针会指向内存中的随机位置
    char *linebuf = NULL;
    size_t linesize = 0;
    if(argc < 2) {
        fprintf(stderr, "Usage...\n");
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    while(1) {
        // 当返回-1时则读完
    	if(getline(&linebuf, &linesize, fp) < 0)
            break;
       	printf("%ld\n", strlen(linebuf));
        printf("%ld\n", linesize);
    }
    fclose(fp);
    exit(0);
}
