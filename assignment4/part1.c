#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int i = 0; // declare int i for for loop
    pthread_t tid; // initialise thread id

    pthread_create(&tid, NULL, slow_function2, (void *)&tid); // create thread for slow fn 2

    for (i = 0; i < 10; i++){ // for loop to run slow fn 1 10 times, with threading so they run simultaneously
        pthread_create(&tid, NULL, slow_function1, (void *)&tid);
    }
  
    pthread_exit(NULL); // exit thread
    return 0;
}
