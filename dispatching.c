#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "global.h"
#include "queue.h"

int run_job() 
{
    //TODO: Encapsulate in "loop" that will wait until the user chose to quit or the user put jobs in the queue
    pid_t child_pid = fork();

    //TODO: Pull execution time from head of queue and put it as first element in list as a string
    char *temp[] = {"<execution time>", NULL};

    if (child_pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }
    if (child_pid == 0)
    {
        /* Calls process output file and waits for given time that was in Noode
         * This will simulate a job being executed
         */
        execv("./process", temp);
        //exit(0);
    }
    
    int status;
    wait(&status);

    if (status == 0)
    {
        printf("Parent: It worked\n");

        // TODO: Unocmment when ready
        //deQueue();
    }
    else if (status == 1)
    {
        printf("Terminated with error\n");
    }
}