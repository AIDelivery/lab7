#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "HELLO from " << argv[0] << endl << "Pipe text:" << endl << endl;
    int filedes[2];
    char buff;
    
    filedes[0] = *argv[1];
    filedes[1] = *argv[2];
    
    close(filedes[1]);
    
    do {
        read(filedes[0], &buff, 1);
        printf("%c", buff);
    }
    while(buff != EOF);
    close(filedes[0]);
    exit(0);
}
