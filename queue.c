#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
void enQueue(Node *newNode) 
{
    newNode->arrivalTime = clock();
    // If the queue is empty set the head and tail to the new node
    // TODO: Lock the critical region - the jobQueue
    if (job_queue->size == 0) 
    {
        job_queue->head = job_queue->tail = newNode;
        job_queue->tail->next = NULL;
        job_queue->size++;
    }
    else
    {
        // Add the new node to the queue and move the tail to the end of the queue (new Node)
        job_queue->tail->next = newNode;
        job_queue->tail = job_queue->tail->next;
        job_queue->tail->next = NULL;
        job_queue->size++;
    }
    
}

// TODO: change to use global queue - jobQueue
Node* deQueue() 
{
    if (job_queue->size == 0)
    {
        return NULL;
    }
    // TODO: Lock the critical region - the jobQueue
    Node *removedNode;
    removedNode = job_queue->head;
    job_queue->head = job_queue->head->next;
    job_queue->size--;
    return removedNode;
}

void copy_node(Node *destination, Node *source) 
{
    destination->name = (char*) malloc(strlen(source->name) + 1);
    strcpy(destination->name, source->name);
    destination->arrivalTime = source->arrivalTime;
    destination->jobPriority = source->jobPriority;
    destination->jobTime = source->jobTime;
}

void swap_nodes(Node *node1, Node *node2)
{
    Node *tempNode = (Node *) malloc(sizeof(Node)); // Create a place in memory to hold temporary information
    copy_node(tempNode, node1);
    copy_node(node1, node2);
    copy_node(node2, tempNode);

    free (tempNode);
}

void printQueue()
{
    if (job_queue->size == 0) 
    {
        printf("There are no jobs pending or running.\n");
    }
    else
    {   
        printf("Name           CPU_Time   Pri   Arrival_Time   Progress\n");
        Node *tempNode = job_queue->head;
        char str_time[11];
        char str_pri[6];
        while (tempNode != NULL)
        {
            snprintf(str_time, 10, "%d", tempNode->jobTime);
            snprintf(str_pri, 5, "%d", tempNode->jobPriority);
            printf("%-15s%-11s%-6s\n", tempNode->name, str_time, str_pri);
            tempNode = tempNode->next;
        }
    }
}

void print_num_jobs()
{
    printf("Total number of jobs in the queue: %d\n", job_queue->size);
}

