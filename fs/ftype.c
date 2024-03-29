#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int ftype(const char *fname) {
    struct stat statres;

    if(stat(fname, &statres) < 0) {
        perror("stat()");
        exit(1);
    }

    if(S_ISREG(statres.st_mode))
        return '-';
    else if(S_ISDIR(statres.st_mode))
        return 'd';
    else if(S_ISSOCK(statres.st_mode))
        return 's';
    else
        return '?';
}

static int fper(const char *fname) {
    struct stat statres;

    if(stat(fname, &statres)) {
        perror("fper()");
        exit(1);
    }

    return statres.st_mode & S_IRWXU;
}


int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    printf("File type: %c\n", ftype(argv[1]));
	printf("Permission of owner: %o\n", fper(argv[1]));
    exit(0);
}