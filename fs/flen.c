#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 注意返回值是off_t类型
static off_t flen(const char *fname) {
    struct stat statres; // 声明一个stat类型的结构体statres
    if(stat(fname, &statres) < 0) {
        perror("stat()");
        exit(1);
    }
	// 返回st_size成员
    return statres.st_size;
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    printf("total size: %ld\n", flen(argv[1]));

    exit(0);
}