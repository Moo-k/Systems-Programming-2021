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
	// NOTE: i am horrible at C code, so instead of presenting code that doesn't work, I've instead decided to submit this assignment in mostly pseudo-code
    // pls have mercy
    int	result;
	void setup();

	prompt = DFL_PROMPT ;
	setup(); // setup shell and prompt

    /* read in user input (char *), using '|' as a delimiter to separate user input into a 2D character array (char **)
     * using splitline, split each pointer in the 2D array into an array of {commands} structs (end up with an array of structs with members char ** (arguments))
     * if number of structs in the array > 1, use for loop for each struct in struct array to fork processes
     * such that the child uses execute() on the first element of the struct array
     * if successful (1), close write end of pipe so that the next child process will read from the read end of pipe
     * free everything using freelist, and free user input pointer
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
