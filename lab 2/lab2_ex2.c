#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Wrong format!\n");
        return 0;
    }
    
    const char* src_path = argv[1]; //numele fisierului
    char* dst_path = argv[2]; //fisierul destinatie
    struct stat stat_buf;

    stat(src_path, &stat_buf);  //stat_buf retine informatiile relevante despre fisier

    int fd_src = open(src_path, O_RDONLY); //deschidem fisierul sursa pe read only
    int fd_dst = open(dst_path, O_WRONLY); //deschidem fisierul destinatie pe write only
    const int DMAX = 1024;

    char* src_content = malloc(sizeof(char) * stat_buf.st_size + 1); //alocam spatiu variabilei src_content


    int read_f, write_f;

    while((read_f = read(fd_src, src_content, stat_buf.st_size)) > 0)
    {
        //printf("%s", src_content); //afisare provizorie
        int wr = 0;
        src_content[stat_buf.st_size] = '\0';
        while((write_f = write(fd_dst, src_content + wr, stat_buf.st_size - wr)) > 0)
            wr += write_f;
    }


    close(fd_src);
    close(fd_dst);

     return 0;
}