#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char line[257];
    pid_t pid;

    while (fgets(line,257,stdin)!=NULL){ // read each line of stdin
        char *templine = NULL;
        char *lines[12]; // 12 > 1 command, 10 args, 1 null
        templine = strtok(line," \n"); // remove " \n" character from line
        int numargs = 0;
        while(templine != NULL) {
            lines[numargs++] = templine;
            templine = strtok(NULL," \n");
        }
        lines[numargs] = NULL; // set last position of array to NULL for execvp

        pid = fork(); // create fork
        if(pid < 0){
            printf("Child creation failed\n");
        }   else if (pid == 0){ // child process
            if(execvp(lines[0],lines) < 0){
                printf("execvp failed\n");
            }
        }   else{ // parent process
            wait(NULL);
        }
    }
    return 0;
}
