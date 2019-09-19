#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "queue.h"

void orderFCFS(struct Queue *queue);
void orderSJF(struct Queue *queue);
void orderPriority(struct Queue *queue);

#endif