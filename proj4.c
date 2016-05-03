
#include "proj4.h"
/*
Signal handler that flushes the output stream whenever a given
signal is recieved. Intended for use with SIGINT.

author: Naif Alrayes
*/
void siginthandler(int sig_num)
{
	fflush(stdout);
}
/*
Signal handler that ensures child processes have reaped after
they have been terminated. Intended for use with SIGCHLD.

author: Naif Alrayes
*/
void sigchldhandler(int sig_num) 
{
	pid_t pid;
	int status;
	while(1) {
		pid = waitpid(-1, &status, WNOHANG);
		if (pid <= 0)
			break;
	}	
}

int main()
{

	signal(SIGINT, siginthandler);
	signal(SIGCHLD, sigchldhandler);
    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {

        procline();
    }
    printf("\n");
    return 0;
}

/*
Bugfix for bug 1:
Before the buigfix, the number of arguments was reset to zero at line 48 (which
is now commented out). More specifically, it was after the functioned returned
due to the line ending, or return being pressed. Since the number of arguments 
doesn't change, arg[narg] does not hold the correct token, so the next
command entered is not processed.

Bugfix for bug 2:
Changing directory is not executed under execve, so the first thing runcommand
should do is check to if the command "cd" is entered. This is done by comparing
the first argument of cline to "cd". If it is, in fact, "cd", we should change
directory accordingly: if no argument is given, simply go to the users home
directory. Otherwise, go to the specified location.

Bugfix for bug 3:
Does the same thing as for detecting "cd", except when "exit" is detected,
exit(0) is called to terminate the shell.

Bugfix for bug 4:
To resolve this, a handler should be installed. This handler will make sure
that if SIGINT (Cntrl-C) is pressed, the shell will not terminate. It does this 
by the handler siginthandler which uses fflush(stdout) to ignore the signal. This 
ensures that SIGINT will  not terminate the shell while still terminating running
processes. This fix did incur one bug: it SIGINT would  still terminate background
processes, behaviour not seen while working in the UNIX shell. To fix this, I 
installed another handler that ignored SIGINT right before execvp is called for
background processes.

Bugfix for bug 5:
To fix this bug, I added a handler that will ensure that all terminated child 
processes are reaped. When a child process is terminated, it sends SIGCHLD to 
the parent. So I installed a handler that uses waitpid to ensure that all child
processes are reaped when SIGCHLD is recieved. It uses waitpid with the option
WNOHANG to ensure that it doesn't wait for ALL children to terminate, but instead
will exit immediately if no children have terminated.
*/

