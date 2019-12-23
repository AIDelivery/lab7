#include <iostream>
#include <stdio.h>      // getc, FILE
#include <unistd.h>     // pipe
using namespace std;

char sub_prog_name[] = "./sub_prog";


int main(int argc, char* argv[]) {
    FILE* merge_file;
    pid_t pid1, pid2;
    int filedes[2];
    char buff;
    int opened_files = 2;

    merge_file = fopen(argv[1], "w");
    pipe(filedes);


    if((pid1 = fork()) == 0)
        execl(sub_prog_name, sub_prog_name, &filedes[1], argv[2], NULL);
    else if(pid1 < 0)
        return -1;

    if((pid2 = fork()) == 0)
        execl(sub_prog_name, sub_prog_name, &filedes[1], argv[3], NULL);
    else if(pid2 < 0)
        return -1;

    cout << endl << endl << "[Subprocesses created]" << endl;
    close(filedes[1]);

    cout << endl << "Pipe content:" << endl << endl << "\t - - - - -" << endl;

    while(true) {
        int temp = read(filedes[0], &buff, 1);

        if (temp && buff == '\0')
            opened_files--;
        else if (temp) {
            cout << buff;
            fwrite(&buff, sizeof(buff), 1, merge_file);
        }
        else if (!temp && opened_files > 0)
            usleep(10000);
        else break;

    }

    cout << "\t - - - - -" << endl << endl << "[Terminating...]" << endl;
    close(filedes[0]);
    fclose(merge_file);

    return 0;
}
