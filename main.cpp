#include <iostream>
// #include <fstream>
#include <stdio.h>      // getc, FILE
#include <unistd.h>     // pipe
#include <wait.h>       // wait
using namespace std;

char if1_n[] = "input1.txt";
char if2_n[] = "input2.txt";
char of1_n[] = "output.txt";

char sub_prog_name[] = "./sub_prog";

int main(int argc, char* argv[]) {
    FILE* merge_file;
    // pid_t pids[2];
    int filedes[2], status;
    char buff;
    
    merge_file = fopen(of1_n, "w");
    pipe(filedes);
    
    
    if(!fork())
        execl(sub_prog_name, sub_prog_name, &filedes[1], if1_n, NULL);
    if(!fork())
        execl(sub_prog_name, sub_prog_name, &filedes[1], if2_n, NULL);
    
    close(filedes[1]);
    
    do {
        cout << "[LOOP]" << endl;
        read(filedes[0], &buff, 1);
        cout << buff;
    } while(buff != EOF);
    
    
    cout << "Terminating..." << endl;
    close(filedes[0]);
    fclose(merge_file);
    return 0;
}
