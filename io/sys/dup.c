#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FNAME "./tmp"

int main(void) {
    int fd;
    // close(1); // 关闭stdout，使描述符1空闲
    // if((fd = open(FNAME, O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0) {
    //     perror("open()");
    //     exit(1);
    // }

   
    if((fd = open(FNAME, O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0) {
        perror("open()");
        exit(1);
    }
    //  //方法2；使用dup 存在两种问题：1.open打开的时候fd就是1，close把1关了 2.多进程/线程并发的时候，close(1)后可能被别的进程占了。这两步操作不原子
    // close(1);
    // // 复制fd，让其占据1的描述符
    // dup(fd);

    //方法3：使用dup2
    // 如果fd = 1，则什么也不做，返回fd
    // 如果fd != 1，则关闭1指向的结构体，再打开1，指向fd的结构体，返回1
    dup2(fd, 1);

    //如果fd不是1才关闭原来的fd
    if (fd != 1) {
        close(fd); 
    }


    puts("Hello World");

    exit(0);
}
