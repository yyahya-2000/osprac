#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid;
    pid = fork();

    if (pid == -1) {
        printf("Some error happened \n");
    } else if (pid == 0) {

        (void) execle("/usr/bin/cat", "/usr/bin/cat", "task04.c", 0, envp);
        //
        // We get here only when an error occurs.
        //
        printf("Error on program start\n");
        exit(-1);
    } else {
        printf("I'm the parent\n");
    }

    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid);

    return 0;
}

