#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "queue.h"

int orderFCFS( Queue *queue );
int orderSJF( Queue *queue );
int orderPriority( Queue *queue );

#endif