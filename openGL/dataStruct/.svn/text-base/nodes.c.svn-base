// mikeoliver

#include <stdlib.h>
#include "nodes.h"

/**
* The node utilites implementation.  Nothing terribly interesting
* here, only setting pointers to NuLLs to make sure illegal memory
* access _always_ fails.~~
*/

struct monoNode *newMonoNode(){

    struct monoNode *newNode = (struct monoNode *)malloc( sizeof(struct monoNode));

    newNode->data = newNode->rLink = NULL;

    return newNode;

}

struct biNode *newBiNode(){

    struct biNode *newNode = (struct biNode *)malloc(sizeof(struct biNode));

    newNode->data = newNode->rLink = newNode->lLink = NULL;

    return newNode;

}

void deleteMonoNode( struct monoNode* aMonoNode ){

    free( aMonoNode );
    return;

}

void deleteBiNode( struct biNode* aBiNode){

    free( aBiNode );
    return;

}
