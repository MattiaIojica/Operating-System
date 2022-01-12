#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
        return -1;

    int n = atoi(argv[1]);
    pid_t pid = fork();

    if(pid < 0)
        return errno;
    else 
        if(pid != 0 && n > 1)
        {
            if(n % 2 == 0)
           	 n = n / 2;
            else
           	 n = 3 * n + 1;

            char str[10];
            sprintf(str, "%d", n);

            char *argv2[] = {"collatz", str};
            execve("/home/mattia/Documents/lab4/collatz", argv2, NULL);
        }
        else
                if(pid == 0)
        {
            wait(NULL);
            printf("%d ", n);
            if(n == 1)
                printf("\nChild %d finished\n", getpid());
        }


}