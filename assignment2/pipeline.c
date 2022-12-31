#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    char line[257];
    char *file[100][12];
    char *lines[12]; // 12 > 1 command, 10 args, 1 null
    char *templine = NULL;
    int numargs = 0;
    pid_t pid;
    int my_pipe[2];
    if(pipe(my_pipe) == -1) {
        perror("Cannot create pipe\n");
    }
    int lineNumber = 0;

    while (fgets(line,257,stdin)){
        templine = strtok(line," \n");
        while(templine != NULL) {
            lines[numargs] = templine;
            templine = strtok(NULL," \n");
            numargs++;
        }
        lines[numargs] = NULL;
        for (int i = 0; i < 12; i++){
            file[lineNumber][i] = lines[i]; // copy lines to 2d array which stores all stdin input
        }

        // if not first command
        if (lineNumber != 0){
            pid = fork();
            if (pid < 0) {
                printf("Failed Fork\n");
            }
            // Parent
            if (pid > 0) {
                close(my_pipe[1]);
                dup2(my_pipe[0], STDIN_FILENO);
                close(my_pipe[0]);
                wait(NULL);
                execvp(lines[0],lines); // parent process runs current line
            }// Child
            else // I.e. my_pid == 0
            {
                close(my_pipe[0]);
                dup2(my_pipe[1], STDOUT_FILENO);
                close(my_pipe[1]);
                char *temp[12];
                for (int i = 0; i < 12; i++){
                    temp[i] = file[lineNumber-1][i];
                }
                execvp(temp[0],temp); // child process runs previous line
            }
        }

        for (int i = 0; i < numargs; i++){
            lines[i] = NULL;
        }
        numargs = 0;
        lineNumber++;
    }
    return 0;
}
