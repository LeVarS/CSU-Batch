#ifndef QUEUE_H
#define QUEUE_H

struct Node;
struct Queue;

void intitializeQueue( struct Queue *queue );
void enQueue( struct Queue * queue, struct Node *newNode );
struct Node* deQueue( struct Queue *queue );

#endif