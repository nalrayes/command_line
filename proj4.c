
#include "proj4.h"

void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
    //printf("\n Cannot be terminated using Ctrl+C \n");
    fflush(stdout);
}

int main()
{

	signal(SIGINT, sigintHandler);
    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}

/*
Bugfix for bug 1:
line 39 in procline

Bugfix for bug 2:
adding thing that catches a "cd"

Bugfix for bug 3:
hardcoding exit, making exit call cntrl-d

Bugfix for bug 4:
install handler that uses fflush

Bugfix for bug 5:

*/

