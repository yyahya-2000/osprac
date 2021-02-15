#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  int     size;
  char    buffer[15];
  //
  // Clear the file creation mask of the current process so that
  // the access rights of the created file exactly match the open () call parameter.
  //
  (void)umask(0);
  //
  // Try to open a file named myfile in the current directory for output operations only.
  // If the file does not exist, try to create it with access rights 0666,
  // i.e. read-write for all categories of users.
  //
  if ((fd = open("myfile", O_RDWR , 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }
  //
  // Try to read 14 bytes from our array to the file,
  // i.e. the entire string "Hello, world!" along with the end-of-line sign.
  //
  size = read(fd, buffer, 14);
  if (size != 14) {
    printf("Can\'t read all string\n");
    exit(-1);
  }

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }
  printf("%s\n",buffer);
  return 0;
}
