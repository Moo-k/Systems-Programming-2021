#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

struct commands{
    char **args;
};

int main()
{
    int	result;
	void setup();

	prompt = DFL_PROMPT ;
	setup(); // setup shell and prompt

    /* take user input as char *
     * using | as delimiter, if char * can be split into multiple pointers, use fork to execute child processes
     * close write end of pipe so that the next child process will read from previous process
     * using < as delimiter, if char * can be split into multiple pointers, use dup2 to set the second pointer to be the input stream
     * using > as delimiter, if input can be split, set the second pointer to be the output stream
     */
     
	return 0;
}

void setup()
{
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr,"Error: %s,%s\n", s1, s2);
	exit(n);
}
