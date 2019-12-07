#include <iostream>
#include <fstream>
// #include <stdio.h>      // getc
#include <unistd.h>     // pipe
#include <wait.h>       // wait
using namespace std;

// TEST
char if1_n[] = "input1.txt";
char if2_n[] = "input2.txt";
char of1_n[] = "output.txt";

char sub_prog_name[] = "./sub_prog";

int main(int argc, char* argv[]) {
    ofstream of1;
    pid_t pids[2];
    int filedes[2], status;
    char buff;
    
    // of1.open(of1_n);
    pipe(filedes);
    
    
    if(!(pids[0] = fork()))
        execl(sub_prog_name, sub_prog_name, &filedes[1], if1_n, NULL);
    if(!(pids[1] = fork()))
        execl(sub_prog_name, sub_prog_name, &filedes[1], if2_n, NULL);
    
    close(filedes[1]);
    int i = 0;
    do {
        read(filedes[0], &buff, 1);
        of1 << buff;
        cout << buff;
        i++;
    // } while(waitpid(pids[0], &status, 0) > 0 || waitpid(pids[1], &status, 0) > 0 || buff != '-');
    } while(buff != '\0' && i < 1000);
    
//     do {
//         read(filedes[0], &buff, 1);
//         of1 << buff;
//         cout << buff;
//     } while(buff != '+');
    
    
    
    cout << "Terminating..." << endl;
    close(filedes[0]);
    of1.close();
    return 0;
}
