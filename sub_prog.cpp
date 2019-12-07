#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

#include <stdio.h>

int main(int argc, char* argv[]) {
    string filename, buffline;
    ifstream if1;
    int filedes;
    
    filedes = *argv[1];
    filename = argv[2];
    
    if1.open(filename);
    
    while(!if1.eof()) {
        getline(if1, buffline);
        write(filedes, buffline.c_str(), buffline.size());
        // write(filedes, (void*) (EOF), 1);
    }
    
    write(filedes, "\0", 1);
    
    close(filedes);
    if1.close();
    exit(0);
}
