#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
  int     fd[2], N, result;
  int    semid;
  char   pathname[]="05-3.c";
  key_t  key; 
  struct sembuf mybuf;
  size_t size;
  char  resstring[14];

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t create semaphore set\n");
    exit(-1);
  }

  printf("Enter N:");
  scanf("%d",&N);


  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  result = fork();

  mybuf.sem_num = 0;
  mybuf.sem_op  = 1;
  mybuf.sem_flg = 0;

  if (semop(semid, &mybuf, 1) < 0) {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */
    for(int i=0; i<N; i++){
        if (close(fd[0]) < 0) {
          printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
        }
    
        size = write(fd[1], "Hello, world!", 14);
    
        if (size != 14) {
          printf("Can\'t write all string to pipe (parent)\n");
          exit(-1);
        }
    
        //if (close(fd[1]) < 0) {
        //  printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
        //}
    
        printf("Parent wrote\n");

        mybuf.sem_num = 0;
        mybuf.sem_op  = -1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }
        mybuf.sem_num = 0;
        mybuf.sem_op  = 1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }
        mybuf.sem_num = 0;
        mybuf.sem_op  = 0;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }

        size = read(fd[0], resstring, 14);
    
        if (size < 0) {
          printf("Can\'t read string from pipe\n");
          exit(-1);
        }
    
        printf("parent read, resstring:%s\n", resstring);
    
        //if (close(fd[0]) < 0) {
        //  printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
       // }

    }

  } else {

    /* Child process */

    for(int i=0;i<N;i++) {
        if (close(fd[1]) < 0) {
          printf("child: Can\'t close writing side of pipe\n"); exit(-1);
        }
    
        size = read(fd[0], resstring, 14);
    
        if (size < 0) {
          printf("Can\'t read string from pipe\n");
          exit(-1);
        }
    
        printf("Child read, resstring:%s\n", resstring);
    
        if (close(fd[0]) < 0) {
          printf("child: Can\'t close reading side of pipe\n"); exit(-1);
        }


        size = write(fd[1], "Hello, world!", 14);
    
        if (size != 14) {
          printf("Can\'t write all string to pipe (child)\n");
          exit(-1);
        }
    
        if (close(fd[1]) < 0) {
          printf("child: Can\'t close writing side of pipe\n"); exit(-1);
        }

        printf("Child wrote\n");

        mybuf.sem_num = 0;
        mybuf.sem_op  = -1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }
        mybuf.sem_num = 0;
        mybuf.sem_op  = 1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }
        mybuf.sem_num = 0;
        mybuf.sem_op  = 0;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t wait for condition\n");
          exit(-1);
        }
    }
  }

  return 0;
}
