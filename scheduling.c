#include <stdlib.h>
#include <stdio.h>
#include "scheduling.h" // scheduling poilicies - fcfs, sjf, priority
#include "global.h"

    /*
 * First Come First Server scheduling policy - Will reorder in ascending order based on when the job was inserted into the queue
 */
    // TODO: change to use global queue - jobQueue
    int orderFCFS()
{
    if (jobQueue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (jobQueue->size == 1)
    {
        printf("Only 1 job in queue. No need to reorder for FCFS policy.\n");
        return 0;
    }
    //struct Node tempNode = NULL;
    Node *tempPointer = jobQueue->head;
    
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
        tempNode = tempPointer->next;
        tempPointer = tempPointer->next;
        tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}

/*
 * Shortest Job First scheduling poolicy - Will reorder in ascending based on how long the job will take
 */
// TODO: change to use global queue - jobQueue
int orderSJF()
{
    if (jobQueue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (jobQueue->size == 1) 
    {
        printf("Only 1 job in queue. No need to reorder for SJF policy.\n");
        return 0;
    }
    //struct Node tempNode = NULL;
    Node *tempPointer = jobQueue->head;

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
        tempNode = tempPointer->next;
        tempPointer = tempPointer->next;
        tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}

/*
 *  Priority-based scheduling policy - Will reorder based on job priority with 1 being the highest 2 being the next highest, etc.
 */
// TODO: change to use global queue - jobQueue
int orderPriority()
{
    if (jobQueue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    if (jobQueue->size == 1)
    {
        printf("Only 1 job in queue. No need to reorder for Priority policy.\n");
        return 0;
    }
    //struct Node tempNode = NULL;
    Node *tempPointer = jobQueue->head;

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
        tempNode = tempPointer->next;
        tempPointer = tempPointer->next;
        tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}