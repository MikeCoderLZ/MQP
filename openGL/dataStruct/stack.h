#ifndef STACK_H
#define STACK_H
#include <stddef.h>
#include "nodes.h"

struct stack {

    size_t size;

    struct monoNode *head;

};

struct stack *newStack();

void *pop( struct stack*);

int push( void*, struct stack*);

int deleteStack( struct stack* );

#endif
