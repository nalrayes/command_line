
#include "proj4.h"


int main()
{


    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}

/*
Bugfix for bug 1:
In the file procline.c, as is convention for a switch statement, 
every case is ended with a "break" statement. The issue here is
that we want the program to run until the user tells us to stop,
so keeping the "break" statement will stop the shell from 
processing any inputs, although the outer while loop keeps the 
program running. The break statement on line 25 was thus commented
out.
*/