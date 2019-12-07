#include <iostream>
// #include <fstream>
#include <string.h>
#include <unistd.h>
using namespace std;

#include <stdio.h>

char* _readline(FILE* file_to_read, int* size) {
    char* res = new char[100];
    char t = 'a';
    int i = 0;
    
    size = &i;
    
    for(i = 0; t != '\n'; i++) {
        t = fgetc(file_to_read);
        if(t == EOF) {
            cout << "AHTUNG" << endl;
            break;
        }
        res[i] = t;
    }
    res[++i] = '\n';
    
    cout << "[STRING TO READ]" << res << "[SIZE OF STRING]" << *size << endl;
    return res;
}

int main(int argc, char* argv[]) {
    FILE* source_file;
    int filedes, n;
    
    filedes = *argv[1];
    source_file = fopen(argv[2], "r");
    
    while(!feof(source_file)) {
        write(filedes, _readline(source_file, &n), n);
        cout << "[SIZE]" << n << endl;
    }
    
    write(filedes, (void*) EOF, sizeof((void*) EOF));
    cout << "[SIZEOF]" << sizeof((void*) EOF) << endl;
    
    close(filedes);
    fclose(source_file);
    exit(0);
}
