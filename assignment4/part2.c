#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;
pthread_cond_t cond;
pthread_cond_t cond2;
pthread_mutex_t lock; 

// ####################################################################################
// ## Please write some code in the following two functions

void * writer(void * in_ptr)
{
    char **array = (char **) in_ptr; // case input void ptr as char double ptr
	int count = 0;
    for (count = 0; count < total_commands; count++){ // for each line of input (from main fgets)
        pthread_mutex_lock(&lock); // lock mutex
        if (get_written()!=0){ // if read
            pthread_cond_wait(&cond, &lock); // wait for cond condition
        }
        bad_write(array[count]); // call write on line of input
        pthread_cond_signal(&cond2); // signal cond2 condition
        pthread_mutex_unlock(&lock); // unlock mutex
    }
    return NULL;
}

void * reader(void * empty)
{
    int count = 0;
    for (count = 0; count < total_commands; count++){ // for each line of input (from main fgets)
        pthread_mutex_lock(&lock); // lock mutex
        if (get_written() != 1){ // if written
            pthread_cond_wait(&cond2, &lock); // wait for cond2 condition
        }
        bad_read(&empty); // call read with empty pointer
        pthread_cond_signal(&cond); // signal cond condition
        pthread_mutex_unlock(&lock); // unlock mutex
    }
    return NULL;
}


// ################################################################################
// ## DO NOT MODIFY 

int main()
{

	// ## Parse STDIN and read into commands
	char * commands[100];
	char line[256];
    while (fgets(line, 256, stdin))
    {
		commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
 		strcpy(commands[total_commands], line);
		total_commands = total_commands + 1;
	}

	pthread_t write1;
	pthread_t read1;

	// Creates a thread which executes writer!
	if(pthread_create(&write1, NULL, writer, commands))
	{
		fprintf(stderr, "Error creating write thread\n");
		return 1;
	}

	// Creates a thread which executes reader!
	if(pthread_create(&read1, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating read thread\n");
		return 1;
	}

	// Ensure Threads Join Well
	if(pthread_join(write1, NULL)) 
	{
		fprintf(stderr, "Error joining write thread\n");
		return 2;
	}

	if(pthread_join(read1, NULL)) 
	{
		fprintf(stderr, "Error joining read thread\n");
		return 2;
	}

	// Did you really call the right functions?
	get_output();

	// I am a responsible memory user!
	int command_i;
	for (command_i = 0; command_i < total_commands; command_i++)
	{
		free(commands[command_i]);
	}
	return 0;

}
// ## DO NOT MODIFY 
// ################################################################################
