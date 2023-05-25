#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Before while(1)");
    fflush(stdout);
    while(1);
    printf("After while(1)");
    fflush(NULL);
    exit(0);
}
