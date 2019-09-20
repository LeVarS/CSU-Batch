#ifndef GLOBAL_H
#define GLOBAL_H

#include "queue.h" // For Queue struct and functions specified in queue.h and queue.c
#include "policies.h"

Queue *job_queue; // Creates the queue and stores it in jobQueue
enum scheduling_policies policy;

#endif