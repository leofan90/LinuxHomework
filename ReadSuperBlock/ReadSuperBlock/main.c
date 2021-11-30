//
//  main.c
//  ReadSuperBlock
//
//  Created by LEO on 2021/11/29.
//  Copyright © 2021 LEO. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
int readsuperblock(char* s){
    int result;
    pid_t pid = vfork();
    if (pid == -1) {
        result = -1;
    } else if (pid == 0) {
        char* comm[100];
        comm[0] = "dumpe2fs";
        comm[1] = s;
        comm[2] = NULL;
        execvp(comm[0], comm+0);
        exit(errno); // 执行出错，返回errno
    } else {
        int status;
        waitpid(pid, &status, 0);
        int err = WEXITSTATUS(status); // 读取子进程的返回码

        if (err) { // 返回码不为0，意味着子进程执行出错，用红色字体打印出错信息
            printf("Error: %s\n", strerror(err));
        }
    }
    return 0;
}
int main()
{
    char file[100];
    printf("请输入想要打印的格式化设备文件超级块:\n");
    scanf("%s", file);
    readsuperblock(file);
}
