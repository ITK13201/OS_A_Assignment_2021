#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  /* open */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#define N 65535

int main(int argc, char *argv[]) {
    int fdi, fdo1, fdo2, split_pos, nread, i;
    char buffer[N], rest_buffer[N];
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
    nread = read(fdi, buffer, N);
    // printf("%s, %d, %d\n", buffer, nread, split_pos);
    if(nread <= split_pos) { // if num of bites read <= split position
        if((write(fdo1,buffer,nread)) != nread)
            write(2, "A write error has occurred\n", 27);
    }
    else if(nread > split_pos){
        if((write(fdo1,buffer,split_pos)) != split_pos)
            write(2, "A write error has occurred\n", 27);
            for(i=0;i<nread - split_pos;i++){
                rest_buffer[i] = buffer[split_pos + i];
            }
        if((write(fdo2,rest_buffer,i)) != i)
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