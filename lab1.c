#include <stdio.h>
#include <unistd.h>

int main(){
printf ("%d\n",getuid());
printf ("%d\n",getgid());
return 0;
};