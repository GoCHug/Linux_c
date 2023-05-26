#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

/*
-y:year 2/4
-m:month
-d:day
-H:hour 12/24
-M:minute
-S:second
*/

int main(int argc, char **argv) {
    FILE *fp = stdout;//定义时候要初始化
    time_t stamp;
    struct tm *tm;
    char timestr[TIMESTRSIZE];
    int c;
    char fmtstr[FMTSTRSIZE];
    fmtstr[0] = '\0';

    stamp = time(NULL);
    tm = localtime(&stamp);

    while (1) {
        c = getopt(argc, argv, "-H:MSy:md");//把需要参数修饰的选项后面加上冒号
        if (c < 0) break;

        switch (c) {
            case 1://getopt拿到一个非选项传参，返回1，然后optind就指向非选项传参的下一个argv
                if (fp == stdout) {//先入为主 只打印到第一个非选项传参的文件中
                    fp = fopen(argv[optind - 1], "w");
                    if (fp == NULL) {
                        perror("fopen()");
                        fp = stdout;
                    }
                }
                break;
            case 'H':
                if (strcmp(optarg, "12") == 0) {
                    strncat(fmtstr, "%I(%P) ", FMTSTRSIZE);
                } else if (strcmp(optarg, "24") == 0) {
                    strncat(fmtstr, "%H ", FMTSTRSIZE);
                } else {
                    fprintf(stderr, "Invalid argument of -H\n");
                }
                break;
            case 'M':
                strncat(fmtstr, "%M ", FMTSTRSIZE);
                break;
            case 'S':
                strncat(fmtstr, "%S ", FMTSTRSIZE);
                break;
            case 'y':
                if (strcmp(optarg, "2") == 0) {
                    strncat(fmtstr, "%y ", FMTSTRSIZE);
                } else if (strcmp(optarg, "4") == 0) {
                    strncat(fmtstr, "%Y ", FMTSTRSIZE);
                } else {
                    fprintf(stderr, "Invalid argument of -y\n");
                }
                break;
            case 'm':
                strncat(fmtstr, "%m ", FMTSTRSIZE);
                break;
            case 'd':
                strncat(fmtstr, "%d", FMTSTRSIZE);
                break;
            default:
                break;
        }
    }

    strncat(fmtstr, "\n", FMTSTRSIZE);
    strftime(timestr, TIMESTRSIZE, fmtstr, tm);
    fputs(timestr, fp);

    if (fp != stdout) {
        fclose(fp);
    }

    exit(0);
}