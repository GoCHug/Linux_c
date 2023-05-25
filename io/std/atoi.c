#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char str[] = "123456";

    printf("%d\n", atoi(str)); // 123456

    // char str[] = "123a456";
	// // 遇到字符就停止
    // printf("%d\n", atoi(str)); // 123

    exit(0);
}
