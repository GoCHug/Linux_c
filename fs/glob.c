#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
// 通配符
#define PAT "/home/gch/linux_c/fs/*"

static int errfunc(const char *epath, int eerrno) {
    puts(epath);
    fprintf(stderr, "ERROR: %d", eerrno);
    return 1;
}

int main() {
    glob_t globres;
    int err;
    err = glob(PAT, 0, errfunc, &globres);

    if(err) {
        printf("ERROR CODE = %d\n", err);
        exit(1);
    }

    int i;

    for(i = 0; i < globres.gl_pathc; i++) {
        puts(globres.gl_pathv[i]);
    }
    // 释放空间
	globfree(&globres);
    exit(0);
}