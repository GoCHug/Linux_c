#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
#include <crypt.h>
#include <string.h>

int main(int argc, char ** argv) {
    char* crypted_pass;
    char* input_pass;
    struct spwd *shadowline;
    if(argc < 2) {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    input_pass = getpass("PassWord:");//使用 getpass() 函数获取用户输入的密码，该函数会在终端中显示 "PassWord:" 提示，并隐藏用户输入的密码，避免密码泄露。

    shadowline = getspnam(argv[1]);//使用 getspnam() 函数从系统中的 /etc/shadow 文件中读取用户的加密后的密码。argv[1] 为命令行参数中传递的用户名

    crypted_pass = crypt(input_pass, shadowline->sp_pwdp);//使用 crypt() 函数将用户输入的密码进行加密，返回加密后的结果。这里的第二个参数是从系统中读取的加密后的密码，用于指定加密算法和盐值。

    if (strcmp(shadowline->sp_pwdp, crypted_pass) == 0){
        puts("ok!");
    } else {
        puts("false!");
    }

    exit(0);
}