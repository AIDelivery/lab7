#include <iostream>
#include <stdio.h>      // getc, FILE
#include <unistd.h>     // pipe
using namespace std;

char if1_n[] = "input1.txt";
char if2_n[] = "input2.txt";
char of1_n[] = "output.txt";

char sub_prog_name[] = "./sub_prog";

int main(int argc, char* argv[]) {
    FILE* merge_file;
    pid_t pid1, pid2;
    int filedes[2];
    char buff;
    
    merge_file = fopen(of1_n, "w");
    pipe(filedes);
    
    
    if((pid1 = fork()) == 0)
        execl(sub_prog_name, sub_prog_name, &filedes[1], if1_n, NULL);
    else if(pid1 < 0)
        return -1;
    
    if((pid2 = fork()) == 0)
        execl(sub_prog_name, sub_prog_name, &filedes[1], if2_n, NULL);
    else if(pid2 < 0)
        return -1;
    
    
    close(filedes[1]);
    
    cout << endl << "File content:" << endl << endl << "\t - - - - -" << endl;
    
    while(read(filedes[0], &buff, 1)) {
        cout << buff;
        fwrite(&buff, sizeof(buff), 1, merge_file);
    }
    
    cout << "\t - - - - -" << endl << endl << "[Terminating...]" << endl;
    close(filedes[0]);
    fclose(merge_file);
    
    return 0;
}
