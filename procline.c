
#include "proj4.h"


/* shell input line */
int procline(void)
{

    char *arg[MAXARG + 1];  //pointer array for runcommand
    int toktype;        // type of token in command
    int narg ;          // number of arguments so far
    int type;           //type =  FOREGROUND or BACKGROUND
    int status;


    while ( 1 ) // loop forever
    {
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))

        {

        case ARG:
            if(narg<MAXARG)
                narg++;
            break;

        case EOL: 
        case SEMICOLON: 
        case AMPERSAND:
            if(toktype == AMPERSAND)
                type = BACKGROUND;
            else
                type = FOREGROUND;

            if(narg != 0)
            {
                arg[narg] = 0;
                narg = 0;
                status = runcommand(arg, type);
            }

            if( toktype == EOL ){
                return;
            }
            //narg = 0;
            break; 
        }
    }
}
