#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// #define NUM_MSG 1000
 
struct thread_args
{
    int x;
    int y;
    int ret;
};

typedef struct thread_args thread_args;

void* thread_routine(void* arg)
{
    {

    // printf("Message from thread\n");
    // sleep(1);
 
    // while(1);
 
    // for(int i = 0; i < NUM_MSG; i++)
    // {
    //     printf("Hello from thread\n");
    //     usleep(1);
    // }


    // printf("PID = %d\n", getpid());
    // printf("TID = %d\n", gettid());

    // char* argv[] = {"pwd", NULL};
    // execve("/usr/bin/pwd", argv, NULL);
    }

    //varianta 2
    thread_args* args_ptr = (thread_args*)arg;
    printf("Received argument %d %d\n", args_ptr->x, args_ptr->y);
    args_ptr->ret = args_ptr->x + args_ptr->y;


    //varianta 1
    thread_args args = *(thread_args*)arg;
    printf("Received argument %d %d\n", args.x, args.y);

    int* sum = malloc(sizeof(*sum));
    *sum = args.x + args.y;
    
    return sum;
    // return NULL;
}


int global_arg = 0;

void* thread_globalvar(void* arg)
{
    // printf("Value of global arg = %d\n", global_arg);
    int step =*(int*)arg;
    for(int i = 0; i < 100000; i++)
    global_arg += step;
    return NULL;
}
 
#define THREADS 10

int main()
{
    pthread_t thread[THREADS];
    int args[THREADS];
    args[0] = 1;
    args[1] = -1;
    for(int i = 0; i < THREADS; i++)
    {
        // pthread_create(&thread[i], NULL, thread_globalvar, NULL);
        pthread_create(&thread[i], NULL, thread_globalvar, &args[i]);
    }

     for(int i = 0; i < THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    printf("%d\n", global_arg);

    // pthread_t thread;
    // // pthread_t thread1, thread2;

    // // int thread_arg = 10;
    // thread_args args = {.x = 10, .y =13};

    // // args.x = 10;
    // // args.y = 13;

    // pthread_create(&thread, NULL, thread_routine, &args);
    
    // void* retval;
    // pthread_join(thread, &retval);

    // printf("Thread computed %d\n", *(int*)retval);
    // printf("Thread computed %d\n", args.ret);

    // free(retval);

    // pthread_join(thread, NULL);

    // thread_arg = 11;
    // pthread_create(&thread2, NULL, thread_routine, &thread_arg);

    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);

{
    // printf("pthread_t = %ld\n", thread);

    // while(1)

    //  for(int i = 0; i < NUM_MSG; i++)
    //  {
    //     printf("Hello from main\n");
    //     usleep(1);
    //  }
 
    // printf("PID = %d\n", getpid());
    // printf("TID = %d\n", gettid());
    
 
    // printf("After join\n");
    // sleep(1);
    // sleep(1);
}

}