#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {

    printf("*****************************************************************\n");
    printf("The number of words on the command line that started the program:\n");
    printf("-----------------------------------------------------------------\n");
    printf("argc = %d\n", argc);
    printf("-----------------------------------------------------------------\n");

    printf("\n*****************************************************************\n");
    printf("An array of pointers to the full contents of the command line:\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < argc; ++i) {
        printf("argc[%d] = %s\n", i, argv[i]);
    }
    printf("-----------------------------------------------------------------\n");

    printf("\n*****************************************************************\n");
    printf("An array of pointers to the process environment parameters:\n");
    printf("-----------------------------------------------------------------\n");
    char *temp = "";
    int i = 0;
    while ((temp = envp[i++]) != NULL) {
        printf("envp[%d] = %s\n", i, temp);
    }
    printf("-----------------------------------------------------------------\n");

    return 0;
}
