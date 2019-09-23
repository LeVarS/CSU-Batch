#include <stdio.h>
#include <pthread.h>
#include "parser.h"
#include "bthread.h" //TODO: MIGHT NOT NEED

int main()
{
    pthread_t scheduling, dispatching;
    while(1)
    {
        parse();
    }
    return 0;
}
