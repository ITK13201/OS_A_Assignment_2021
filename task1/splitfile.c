#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  /* open */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <unistd.h>
#define N 65535

int main(int argc, char *argv[]) {
    int fdi, fdo1, fdo2, split_pos, nread;
    char buffer[N];
    // get split position
    if ((split_pos = atoi(argv[4])) <= 0) {
        perror("invalid");
        exit(1);
    }
    // open files
    if ((fdi = open(argv[1], O_RDONLY)) == -1) {
        perror("open fdi");
        exit(1);
    }
    if ((fdo1 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0777)) == -1) {
        perror("open fdo1");
        exit(1);
    }
    if ((fdo2 = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0777)) == -1) {
        perror("open fdo2");
        exit(1);
    }
    // read files 
    nread = read(fdi, buffer, split_pos);
    if((write(fdo1,buffer,nread)) != nread)
            write(2, "A write error has occurred\n", 27);
    if(nread == split_pos) {
        if (lseek(fdi, split_pos, SEEK_SET) == -1) {
            perror("lseek");
            exit(1);
        }
        nread = read(fdi, buffer, N);
        if((write(fdo2, buffer, nread)) != nread)
            write(2, "A write error has occurred\n", 27);
    }
    // close files
    if (close(fdo1) == -1) {
        perror("close fdo1");
        exit(1);
    }
    if (close(fdo2) == -1) {
        perror("close fdo2");
        exit(1);
    }
    return 0;
}