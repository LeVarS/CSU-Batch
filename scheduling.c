#include <stdlib.h>
#include <stdio.h>
#include "scheduling.h" // scheduling poilicies - fcfs, sjf, priority
#include "global.h"
#include "policies.h"
#include "queue.h"

/*
 * Print Policy Function - Prints the current policy
 */
void print_policy() 
{
    if (policy == FCFS)
    {
        printf("Scheduling Policy: FCFS.\n");
    }
    else if (policy == SJF)
    {
        printf("Scheduling Policy: SJF.\n");
    }
    else
    {
        printf("Scheduling Policy: Priority.\n");
    }
}

/*
 * First Come First Server scheduling policy - Will reorder in ascending order based on when the job was inserted into the queue
 */
int orderFCFS()
{
    if (job_queue->size == 0)
    {
        printf("No jobs inside of queue to order into FCFS policy\n");
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (job_queue->size == 1)
    {
        printf("Only 1 job in queue. No need to reorder for FCFS policy.\n");
        return 0;
    }
    // TODO: Lock the critical region - the jobQueue
    //struct Node tempNode = NULL;
    Node *tempPointer =job_queue->head;
    
    // Selection Sort algorithm to sort for the fcfs policy
    
    while (tempPointer != NULL)
    {
        Node *min = tempPointer;
        Node *tempNode = tempPointer->next;
        while (tempNode != NULL) 
        {
            if (min->arrivalTime > tempNode->arrivalTime)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        if (tempPointer != min)
        {
            swap_nodes(tempPointer, min);
            tempPointer = tempPointer->next;
        }
        else
        {
            tempPointer = tempPointer->next;
        }
    
    }
    printf("Scheduling policy is switched to FCFS. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0; // Error code of 0 signifies a successful sort for this policy

}

/*
 * Shortest Job First scheduling poolicy - Will reorder in ascending based on how long the job will take
 */
int orderSJF()
{
    if (job_queue->size == 0)
    {
        printf("No jobs inside of queue to order into SJF policy\n");
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (job_queue->size == 1) 
    {
        printf("Only 1 job in queue. No need to reorder for SJF policy.\n");
        return 0;
    }
    // TODO: Lock the critical region - the jobQueue
    //struct Node tempNode = NULL;
    Node *tempPointer =job_queue->head;

    // Selection Sort algorithm to sort for the sjf policy
    while (tempPointer != NULL)
    {
        Node *min = tempPointer;
        Node *tempNode = tempPointer->next;
        while (tempNode != NULL)
        {
            if (min->jobTime > tempNode->jobTime)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        if (tempPointer != min)
        {
            swap_nodes(tempPointer, min);
            tempPointer = tempPointer->next;
        }
        else
        {
            tempPointer = tempPointer->next;
        }
    }
    printf("Scheduling policy is switched to SJF. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = SJF;
    return 0; // Error code of 0 signifies a successful sort for this policy
}

/*
 *  Priority-based scheduling policy - Will reorder based on job priority with 1 being the highest 2 being the next highest, etc.
 */
int orderPriority()
{
    if (job_queue->size == 0)
    {
        printf("No jobs inside of queue to order into Priority policy\n");
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (job_queue->size == 1)
    {
        printf("Only 1 job in queue. No need to reorder for Priority policy.\n");
        return 0;
    }
    // TODO: Lock the critical region - the jobQueue
    //struct Node tempNode = NULL;
    Node *tempPointer =job_queue->head;

    // Selection Sort algorithm to sort for the priority policy
    while (tempPointer != NULL)
    {
        Node *min = tempPointer;
        Node *tempNode = tempPointer->next;
        while (tempNode != NULL)
        {
            if (min->jobPriority > tempNode->jobPriority)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        if (tempPointer != min)
        {
            swap_nodes(tempPointer, min);
            tempPointer = tempPointer->next;
        }
        else 
        {
            tempPointer = tempPointer->next;
        }
    }
    printf("Scheduling policy is switched to Priority. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = PRIORITY;
    return 0; // Error code of 0 signifies a successful sort for this policy
}