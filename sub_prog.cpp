#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
    ifstream source_file;
    string bufline;

    int write_to_pipe_des = *argv[1];
    source_file.open(argv[2], std::ifstream::in);

    while(!source_file.eof()) {
        getline(source_file, bufline);
        bufline.append("\n");
        size_t sz = bufline.size();

        write(write_to_pipe_des, bufline.c_str(), sz);
    }

    char t = '\0';
    write(write_to_pipe_des, &t, 1);

    cout << "[Subprogram terminating]" << endl;
    close(write_to_pipe_des);
    source_file.close();
    exit(0);
}
