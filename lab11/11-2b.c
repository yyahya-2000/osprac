#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255
#define MSG_EXCEPT 255

int main(void)
{
  int msqid;
  char pathname[]="11-1a.c";
  key_t  key;
  int len, maxlen;

   struct mymsgbuf
  {
    long mtype;
    struct{
	int myKey;
	char myValue[81];
    }myInfo;
    
  } mybuf;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }
  int i=1;
 
  while (1) {
    //
    // In an infinite loop, accept messages of any type in FIFO order
    // with a maximum length of 81 characters
    // until a message of type LAST_MESSAGE is received.
    //
    maxlen = 109 + sizeof(int);
printf("b will read\n");
    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, MSG_EXCEPT)) < 0) {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
    printf("b read\n");
    //
    // If the received message is of type LAST_MESSAGE,
    // then terminate and remove the message queue from the system.
    // Otherwise, print the text of the received message.
    //
    if (mybuf.mtype == LAST_MESSAGE) {
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(0);
    }

    printf("--11-2b.c--message type = %ld, key = %d, value =%s\n", mybuf.mtype,    mybuf.myInfo.myKey,mybuf.myInfo.myValue );
    //
    // Fill in the structure for the message and
    // determine the length of the informative part.
    //
    mybuf.mtype = 2;
    strcpy(mybuf.myInfo.myValue, "This is text message from b");
    len = strlen(mybuf.myInfo.myValue)+ sizeof(int) +1;
    mybuf.myInfo.myKey = i++;
    //
    // Send the message. If there is an error,
    // report it and delete the message queue from the system.
    //
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }


  }

  return 0;
}
