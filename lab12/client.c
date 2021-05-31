#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int msqid;

    char pathname[] = "server.c";

    key_t key; /* IPC ключ */

    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct {
            int PID;
            float num;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    /*Процесс отправки*/

    mybuf.mtype = 1;
    mybuf.info.PID = getpid();
    printf("Enter float value:\n");
    float value;
    scanf("%f", &value);
    mybuf.info.num=value;

    len = sizeof(mybuf.info);

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) /*Функция отправки*/
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    maxlen = sizeof(mybuf.info);

    if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, getpid(), 0)) < 0) /*Функция приема*/
    {
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }

    printf("message type = %ld, square =%f\n", mybuf.mtype, mybuf.info.num);
    printf("\n");

    return 0;
}
