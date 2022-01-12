#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
 
 
 
int* randomt(int word_size)
{
    int *r = malloc(word_size * sizeof(int));
 
    for(int i = 0; i < word_size; i++)
        r[i] = i;
 
    for(int i = 0; i < word_size; i++)
    {
        int random_index = rand() % word_size;
 
        int aux = r[i];
        r[i] = r[random_index];
        r[random_index] = aux;
    }
 
    return r;
}
 
 
 
int main(int argc, char *argv[])
{
    if(argc == 2 || argc == 3)
    {
 
        int fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
        struct stat sb;
 
        if(fstat(fd, &sb) == -1)
        {
            perror("Couldn't get file size!\n");
        }
 
        //printf("File size: %ld\n", sb.st_size);
 
        char *in_file = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 
        if(argc == 2)
        {
            FILE *prm;
 
            prm = fopen("permutari.txt", "w");
 
            for(int i = 0; i < sb.st_size; i++)
                if(isalpha(in_file[i]))
                {
                    int len = -1;
                    char aux[100];
                    while(isalpha(in_file[i]) && i < sb.st_size)
                    {
                        aux[++len] = in_file[i];
                        i++;
                    }
                    //i--; //pentru caracterele speciale(' .,!')
                    aux[++len] = '\0';
 
                    int *r = randomt(len); //genereaza o permutare random
 
                    for(int j = 0; j < len; j++)
                    {
                        in_file[i - len + j] = aux[r[j]];
                        fprintf(prm, "%d", r[j]);
                    }
                    fprintf(prm, "\n");
 
                }
 
            fclose(prm);
        }
        else
            {
                FILE *prm;
 
                prm = fopen(argv[2], "r");
 
                for(int i = 0; i < sb.st_size; i++)
                    if(isalpha(in_file[i]))
                    {
                        int len = -1;
                        char aux[30];
                        while(isalpha(in_file[i]) && i < sb.st_size)
                        {
                            aux[++len] = in_file[i];
                            i++;
                        }
                        //i--; //pentru caracterele speciale(' .,!')
                        aux[++len] = '\0';
 
                        char permutare[30];
 
 
                        fscanf(prm, "%s", permutare);
 
                        for(int j = 0; j < len; j++)
                        {
                            in_file[i - len + (permutare[j] - '0')] = aux[j];
 
                        }
                    }
                fclose(prm);
 
            }
 
        //printf("\n"); 
 
        munmap(in_file, sb.st_size);
        close(fd);
    }
    else
    {
        printf("Wrong number of files!");
        return -1;
    }
}
 