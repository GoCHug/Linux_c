#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "./out"
#define BUFSIZE 1024

int main() {
    FILE *fp;
    int count = 0;//记录现在有多少行
    char  buf[BUFSIZE];
    time_t stamp;
    struct tm *tm;


    fp = fopen(FNAME, "a+");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fp) != NULL)
        count++;

    while (1) {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp, "%-4d%d-%d-%d %02d:%02d:%02d\n", ++count, \
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        fflush(fp);//除了终端设备是行缓冲，这是全缓冲
        sleep(1);
    }

    fclose(fp);

    exit(0);
}