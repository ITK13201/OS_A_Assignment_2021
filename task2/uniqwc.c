#include <sys/types.h> /* fork, read, wait, write */
#include <sys/uio.h>   /* read, write */
#include <sys/wait.h>  /* wait */
#include <unistd.h>    /* close, fork, pipe, read, write */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int fd[2];
  pid_t pid;
  if(pipe(fd)<0){
    perror("pipe");
    exit(1);
  }
  if((pid = fork()) == 0){/* child process */
    close(fd[1]);
    close(0);
    dup(fd[0]);
    if(argc !=3){
      execlp("wc", "wc", "-l", NULL);
    }
    else{
      execlp("wc", "wc", argv[2], NULL);
    }
    close(fd[0]);
  } 
  else if(pid == -1){
    perror("fork");
    exit(1);
  }
  else{/* parent process */
    close(fd[0]);
    close(1);
    dup(fd[1]);
    if(argc >= 2) {
      execlp("uniq", "uniq", argv[1], NULL);
    }
    close(fd[1]);
  }
}