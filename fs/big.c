#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;

    if(argc < 2) {
        fprintf(stderr, "Usage...");
        exit(1);
    }

    if((fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0) {
        perror("open");
        exit(1);
    }
	// 先让指针从文件开头向后移动5G个字节
    lseek(fd, 5LL * 1024LL * 1024LL * 1024LL - 1LL, SEEK_SET);
	// 在最后写入一个空字符
    write(fd, "", 1);

    close(fd);

    exit(0);
}
