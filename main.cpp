#include <iostream>
#include <stdio.h>
#include <unistd.h> // pipe
#include <wait.h>

char sub_prog_name[] = "./sub_prog";

int main(int argc, char **argv) {
    int filedes[2];
    FILE *f;
    int status;
    char buff;
    
    pipe(filedes);
    f = fopen("TT.txt", "r");
    
    
    if(!fork())
        execl(sub_prog_name, sub_prog_name, &filedes[0], &filedes[1], NULL);
    else {
        close(filedes[0]);
        while(!feof(f)) {
            buff = fgetc(f);
            write(filedes[1], &buff, 1);
        }
        
        fclose(f);
        wait(&status);
        close(filedes[1]);
    }
    
    return 0;
}
