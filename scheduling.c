#include "scheduling.h" // scheduling poilicies - fcfs, sjf, priority
#include <stdlib.h>

/*
 * First Come First Server scheduling policy - Will reorder in ascending order based on when the job was inserted into the queue
 */

int orderFCFS(struct Queue *queue)
{
    if (queue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    //struct Node tempNode = NULL;
    struct Node *tempPointer = queue->head;
    
    // Selection Sort algorithm to sort for the fcfs policy
    while (tempPointer != NULL)
    {
        struct Node *min = tempPointer;
        struct Node *tempNode = tempPointer->next;
        while (tempNode != NULL) 
        {
            if (min->arrivalTime > tempNode->arrivalTime)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        tempNode = *tempPointer->next;
        *tempPointer = *tempPointer->next;
        *tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}

/*
 * Shortest Job First scheduling poolicy - Will reorder in ascending based on how long the job will take
 */
void orderSJF(struct Queue *queue)
{
    if (queue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }
    //struct Node tempNode = NULL;
    struct Node *tempPointer = queue->head;

    // Selection Sort algorithm to sort for the sjf policy
    while (tempPointer != NULL)
    {
        struct Node *min = tempPointer;
        struct Node *tempNode = tempPointer->next;
        while (tempNode != NULL)
        {
            if (min->jobTime > tempNode->jobTime)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        tempNode = *tempPointer->next;
        *tempPointer = *tempPointer->next;
        *tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}

/*
 *  Priority-based scheduling policy - Will reorder based on job priority with 1 being the highest 2 being the next highest, etc.
 */
void orderPriority(struct Queue *queue)
{
    if (queue->size == 0)
    {
        return -1; // Error code of -1 signifies an empty queue that has no jobs to sort
    }

    //struct Node tempNode = NULL;
    struct Node *tempPointer = queue->head;

    // Selection Sort algorithm to sort for the priority policy
    while (tempPointer != NULL)
    {
        struct Node *min = tempPointer;
        struct Node *tempNode = tempPointer->next;
        while (tempNode != NULL)
        {
            if (min->jobPriority > tempNode->jobPriority)
            {
                min = tempNode;
            }
            tempNode = tempNode->next;
        }
        tempNode = *tempPointer->next;
        *tempPointer = *tempPointer->next;
        *tempPointer->next = tempNode;
        tempPointer = tempPointer->next;
    }
    return 0; // Error code of 0 signifies a successful sort for this policy
}