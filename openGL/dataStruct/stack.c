#include "stack.h"
#include <stdlib.h>

struct stack *newStack(){

    struct stack *newStack = (struct stack*)malloc(sizeof(struct stack));

    if( newStack != NULL ){
        newStack->size = 0;
        newStack->head = NULL;
    }

    return newStack;

}

void *pop( struct stack *aStack ){
   
    struct monoNode *dataNode = aStack->head;
    void *data = NULL;
   
    if( aStack->size > 0 ){
        dataNode->data;
        aStack->head = aStack->head->rLink;
        (aStack->size)--;
        deleteMonoNode(dataNode);
    }

    return data;

}

int push( void *someData , struct stack *aStack){

    struct monoNode *newStackNode = newMonoNode();

    if( newStackNode != NULL ) {
        newStackNode->data = someData;
        newStackNode->rLink = aStack->head;
        aStack->head = newStakNode;
        (aStack->size)++;

        return 0;
    }

    return -1;
}

int deleteStack( struct stack aStack ){

    while(aStack->size > 0){
        pop( aStack );
    }

    free( aStack );
}
