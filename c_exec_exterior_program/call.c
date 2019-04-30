#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(void)
{
        pid_t pid;

        printf("root getpid:%d\n", getpid());
        printf("root getppid:%d\n", getppid());

        pid = fork();
        if (pid < 0) {
                fprintf(stderr, "Error fork %d\n", errno);
                exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
                //子プロセス処理
                printf("child pid:%d\n", pid);
                printf("child getpid:%d\n", getpid());
                printf("child getppid:%d\n", getppid());
                _exit(0); //子プロセスでは終了時には_exitを呼ぶことに注意!
        }
        else {
                //親プロセス処理
                printf("parent pid:%d\n", pid);
                printf("parent getpid:%d\n", getpid());
                printf("parent getppid:%d\n", getppid());
                waitpid(pid, NULL, 0); //子プロセス終了を待つ
                //kill(pid, SIGKILL); //子プロセスにシグナルを送信する
                exit(0); //親プロセスでは終了時にはexitを呼ぶ
        }

        return 0;
}
