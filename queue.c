#include <stdlib.h>
#include <stdio.h>
#include <time.h>       // clock_t which is the amount of clock cycles since the program began
#include "queue.h"
#include "global.h"


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

// TODO: change to use global queue - jobQueue
void enQueue(Queue *queue, Node *newNode) 
{
    newNode->arrivalTime = clock();
    // If the queue is empty set the head and tail to the new node
    if (queue->size == 0) 
    {
        queue->head = queue->tail = newNode;
        queue->tail->next = NULL;
        queue->size++;
    }
    else
    {
        // Add the new node to the queue and move the tail to the end of the queue (new Node)
        queue->tail->next = newNode;
        queue->tail = queue->tail->next;
        queue->tail->next = NULL;
        queue->size++;
    }
    
}

// TODO: change to use global queue - jobQueue
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

void printQueue(Queue *queue)
{
    if (queue->size == 0) 
    {
        printf("There are no jobs pending or running.\n");
    }
    else
    {
        Node *tempNode = queue->head;
        while (tempNode != NULL)
        {
            printf("%s", tempNode->name);
            //printf("%s\t%d\t%d", tempNode->name, tempNode->jobTime, tempNode->jobPriority);
            tempNode = tempNode->next;
        }
        printf("\n");
    }
}

void print_num_jobs()
{
    printf("Total number of jobs in the queue: %d\n", job_queue->size);
}

