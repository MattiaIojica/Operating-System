#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
        return -1;

    printf("Starting parent %d\n", getppid());
    pid_t pids[argc];


    for(int i = 0; i < argc; i++)
    {
        if((pids[i] = fork()) < 0)
            return errno;
        else
            if(pids[i] == 0)
            {
                int n = atoi(argv[i + 1]);
                printf("%d: ", n);


                while(n != 1)
                {
                    printf("%d ", n);

                    if(n % 2 == 0)
                        n = n / 2;
                    else
                        n = n * 3 + 1;
                }
                printf("%d\n", 1);
                exit(0);
            }
    }

    for(int i = 0; i < argc; i++)
    {
        printf("Done Parent %d Me %d\n", getppid(), getpid());
        wait(NULL);
    }
}