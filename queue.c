#include <stdlib.h>
#include <time.h>       // clock_t which is the amount of clock cycles since the program began
#include "queue.h"

// Node structure for jobs
struct Node
{
    const char *name;
    unsigned int jobTime;
    unsigned int jobPriority;
    clock_t arrivalTime;    // Used for FCFS so it will know which jobs got there before the other
    struct Node  *next;
};

struct Queue
{
    struct Node *head, *tail;
    unsigned int size;
};

// Global queue for scheduling and dispatching thread
struct Queue *jobQueue;

/*
 * Initializes a queue and returns it
 */
struct Queue* initializeQueue(struct Queue *queue) 
{
    queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->head = queue ->tail = NULL;
    queue->size = 0;
    return queue;
}

void enQueue(struct Queue *queue, struct Node *newNode) 
{   
    // If the queue is empty set the head and tail to the new node
    if (queue->size == 0) 
    {
        queue->head = queue->tail = newNode;
        queue->size++;
    }
    else
    {
        // Add the new node to the queue and move the tail to the end of the queue (new Node)
        queue->tail->next = newNode;
        queue->tail = queue->tail->next;
        queue->size++;
    }
    
}

struct Node* deQueue(struct Queue *queue) 
{
    if (queue->size == 0)
    {
        return NULL;
    }
    struct Node *removedNode;
    removedNode = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    return removedNode;
}

