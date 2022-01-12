#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
        return errno;
    else
        if(pid == 0)
        {
            printf("My PID=%d, Child PID=%d\n", getppid(), getpid());
            char* argv[] = {"ls", NULL};
            execve("/usr/bin/ls", argv, NULL);
        }
    else
        if(pid > 0)
        {
            wait(NULL);
            printf("Child %d finished\n", pid);
        }
}