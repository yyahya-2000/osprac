#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main()
{
  int pfd;
  int fd[2];
  char a[100];
  int size=0;

  if((pfd=pipe(fd))<0)
  {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  else
  {
    size = 0;
    // write into pipe by 1 byte until it will block waiting some another proccess to read 
    while (write(fd[1], "a", 1)==1)
    {
       size++;
       printf("%d\n",size);
    }
    
  }
  return 0;
}
