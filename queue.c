#include <stdlib.h>
#include <time.h>       // clock_t which is the amount of clock cycles since the program began
#include "queue.h"


/*
 * Initializes a queue and returns it
 */
Queue* initializeQueue() 
{
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->head = queue ->tail = NULL;
    queue->size = 0;
    return queue;
}

void enQueue(Queue *queue, Node *newNode) 
{
    newNode->arrivalTime = clock();
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

Node* deQueue(Queue *queue) 
{
    if (queue->size == 0)
    {
        return NULL;
    }
    Node *removedNode;
    removedNode = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    return removedNode;
}

