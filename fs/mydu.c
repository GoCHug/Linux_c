#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define PATHSIZE 1024

static int path_noloop(const char *path) {
    char *pos;
    pos = strrchr(path, '/');
    if (pos == NULL) {
        exit(1);
    }
    if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0) {
        return 0;
    }
    return 1;
}

static int64_t mydu(const char *path) {
    static struct stat statres;
    static char nextpath[PATHSIZE];//递归的优化 没有过递归点的可以放到静态区
    glob_t globres;
    int64_t sum;

    if (lstat(path, &statres) < 0) {
        perror("lstat()");
        exit(1);
    }
    //终止条件
    if (!S_ISDIR(statres.st_mode)) {//非目录
        return statres.st_blocks / 2;
    }

    //目录
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/*", PATHSIZE);
    if (glob(nextpath, 0, NULL, &globres) < 0) {
        perror("glob()");
        exit(1);
    }
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/.*", PATHSIZE);//这个目录下的隐藏文件
    if (glob(nextpath, GLOB_APPEND, NULL, &globres) < 0) {//GLOB_APPEND追加
        perror("glob()");
        exit(1);
    }

    sum = statres.st_blocks / 2;//当前目录大小
    for (int i = 0; i < globres.gl_pathc; i++) {
        if (path_noloop(globres.gl_pathv[i])) {
        sum += mydu(globres.gl_pathv[i]);
        }
    }
    globfree(&globres);//释放空间
    return sum;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    printf("%ld\n", mydu(argv[1]));
    exit(0);
}