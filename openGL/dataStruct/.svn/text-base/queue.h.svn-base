#ifndef QUEUE_H
#define QUEUE_H
#include "nodes.h"
#include <stddef.h>

struct queue {

    size_t size;

    struct monoNode *first;
    struct monoNode *last;

};

struct queue *newQueue();

void *dequeue();

int enqueue( void* );

int deleteQueue( struct queue* );
#endif
