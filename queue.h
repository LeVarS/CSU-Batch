#ifndef QUEUE_H
#define QUEUE_H

#include <time.h> // clock_t which is the amount of clock cycles since the program began

// Node structure for jobs
typedef struct Node
{
    const char *name;
    unsigned int jobTime;
    unsigned int jobPriority;
    clock_t arrivalTime; // Used for FCFS so it will know which jobs got there before the other
    Node *next;
} Node;

typedef struct Queue
{
    Node *head, *tail;
    unsigned int size;
} Queue;

Queue* intitializeQueue( );
void enQueue( Queue * queue, Node *newNode );
Node* deQueue( Queue *queue );

#endif