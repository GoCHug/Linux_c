#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {
    FILE *fps, *fpd;
    char buf[BUFSIZE];

    if (argc < 3) {
        fprintf(stderr, "Usage:%s <src_file> <dest_file>\n", argv[0]);
        exit(1);
    }    

    fps = fopen(argv[1], "r");
    if (fps == NULL) {
        perror("open()");
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if (fps == NULL) {
        fclose(fps);
        perror("open()");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fps) != NULL) {
        fputs(buf, fpd);
    }

    fclose(fpd);
    fclose(fps);//先关闭依赖别人的对象，再关闭被依赖的对象

    exit(0);
}