#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>


int main() {
    char fName[] = "a";
    char content[] = "a regular file";
    char sLName[] = "1";

    FILE *filePointer = fopen(fName, "w+");

    if (filePointer == NULL) {
        perror("Cannot create or open the file! ");
        exit(1);
    }

    fprintf(filePointer, "%s", content);
    if (fclose(filePointer) < 0) {
        perror("Cannot close file ");
    }

    if (symlink(fName, sLName) != 0) {
        perror("symlink() error ");
        unlink(fName);
    }

    if (fopen(sLName, "w+") == NULL) {
        printf("Recursion depth is: %d\n", 0);
        unlink(sLName);
        return 0;
    }

    int i = 2;
    while (1) {

        char start[PATH_MAX];
        char end[PATH_MAX];
        sprintf(start, "%d", i - 1);
        sprintf(end, "%d", i);
        if (symlink(start, end) != 0) {
            perror("symlink() error ");
            unlink(start);
            break;
        }

        if (fopen(end, "r") == NULL) {
            printf("Recursion depth is: %d\n", i - 1);
            unlink(end);
            return 0;
        }
        i++;
    }
}
