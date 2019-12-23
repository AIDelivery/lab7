#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
    ifstream source_file;
    string bufline;

    int* pipe_des = (int*) argv[1];
    source_file.open(argv[2], std::ifstream::in);
    
    close(pipe_des[0]);

    while(!source_file.eof()) {
        getline(source_file, bufline);
        bufline.append("\n");
        size_t sz = bufline.size();

        write(pipe_des[1], bufline.c_str(), sz);
    }

    char t = '\0';
    write(pipe_des[1], &t, 1);

    cout << "[Subprogram terminating]" << endl;
    close(pipe_des[1]);
    source_file.close();
    exit(0);
}
