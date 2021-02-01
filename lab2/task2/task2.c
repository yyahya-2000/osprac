#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  pid = fork();

  if (pid == -1) {
      printf("Some error happened \n");
  } else if (pid == 0) {
      printf("I'm the child\n");
  } else {
      printf("I'm the parent\n");
  } 

  pid  = getpid();
  ppid = getppid();

  printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid);

  return 0;
}
