#include "proj4.h"

// execute a command with optional wait
int runcommand(char **cline, int where) {
    pid_t pid;
    int status;
    if (strcmp(cline[0], "cd") == 0){
        if (cline[1] == NULL) {
            cline[1] = getenv("HOME");
        }
        chdir(cline[1]);
        return 0;
    }
    switch(pid=fork()) {
    case -1:
        perror(SHELL_NAME);
        return (-1);
    //code for child
    case 0:
        execvp(*cline,cline);
        // we should never get to this code, since execve does not return
        perror(*cline);
        exit(1);
    }
    // code for parent
    // if background process print pid and exit
    // program is running in the background
    if(where == BACKGROUND) {
        printf("[Process id %d]\n",pid);
        return (0);
    }

    // wait until process pid exits
    if (waitpid(pid,&status,0) == -1)
        return (-1);
    else
        return (status);
}
