#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

int collatz(int *shm_ptr, int n, int i)
{
    shm_ptr[i] = n;

    if(n == 1)
        return i + 1;
    
    if(n % 2 == 0)
        n /= 2;
    else
        n = n * 3 + 1;

    collatz(shm_ptr, n, i + 1);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
        return -1;

    printf("Starting parent %d\n", getppid());

    pid_t pids[argc];

    char shm_name[] = "collatz";
    int shm_fd;

    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd < 0)
    {
        perror(NULL);
        return errno;
    }

    size_t shm_size = getpagesize() * argc;

    if(ftruncate(shm_fd, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    for(int i = 0; i < argc; i++)
        if((pids[i] = fork()) < 0)
            return errno;
        else
            if(pids[i] == 0)
            {
                int* shm_ptr = mmap(0, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, getpagesize() *i);
                if(shm_ptr == MAP_FAILED)
                {
                    perror(NULL);
                    shm_unlink(shm_name);
                    return errno;
                }
        
                int n = atoi(argv[i + 1]);
                printf("%d: ", n);

                int used_len = collatz(shm_ptr, n, 0);
                for(int j = 0; j < used_len; j++)
                    printf("%d ", shm_ptr[j]);

               printf("\n");
               exit(0);
            }
    

    for(int i = 0; i < argc; i++)
    {
        printf("Done parent %d Me %d\n", getppid(), getpid());
        wait(NULL);
    }

    shm_unlink(shm_name);
    munmap(0, getpagesize() * argc);

    return 0;
}