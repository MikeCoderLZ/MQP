#include "biArrary.h"
#include <stdlib.h>
#include <stddef.h>

struct biArray* newBiArrary(){

    struct biArray* newArrary = (struct biArrary*)malloc(sizeof(struct biArrary));

    newArray->size = 0;
    newArray->depth = 0; //not exactly true, but it needs to be initialized
    hnwArray->endOfRow = 0; //that actually is true
    newArray->root = NULL;

    return newArrary;
}

size_t __log2_Int__( size_t num ){

    size_t log = 0;

    // This is as fast as I can make it.
    for(;;){
        (((num = num >> 1) != 0 ) ? log++ : break);
    }

    return log;
}

struct biNode* __getNode__( size_t index, struct biArrary* anArray){

    /*The idea behind this is kind of like running the math
      of the in-place heapsort of an array BACKWARDS.  This allows
      O(log(n)) average insertion and retrieval time and dynamic
      memory allocation.*/

    // The index in the virtual array thus far
    // (starts at the root, index zero)
    size_t currentDepth = __log2_Int__(index) - 1;
    // Holds the results of the subtree selection test
    size_t test = 0;
    // start at the root
    struct biNode* currentNode = anArray->root;

    // The test is the difference between the goal index
    // and the currentIndex. If it is odd, we take the left
    // subtree with new index of 2*currentIndex + 1.
    // Even, and we take the right with new index
    // 2*currentIndex + 2.  If it is zero, we've arrived at
    // our goal, so break out and return the node.
    for(;;){

        if(!(test = (index - (2 << currentDepth) - 1)/(2<<currentDepth))) break;

        if(test % 2){
            currentIndex = 2 * currentIndex + 2;
            currentNode = currentNode->rLink;
        } else {
            currentIndex = 2 * currentIndex + 1;
            currentNode = currentNode->lLink;
        }
    }

    return currentNode;

}

void* get( size_t index, struct biArray* anArrary){

    if( anArrary != NULL){
        return __getNode__(index, anArray)->data;
    }
    return NULL;
}

int set( void* data, size_t index, struct biArray* anArrary){

    if( anArray != NULL ){
        __getNode__(index, anArray)->data = data;
        return 0;
    }
    return -1;
}

int append( void* data, struct biArray* anArray){

    struct biNode* newNode = NULL;
    size_t size = 0;

    //Remember that since indices start at 0, the size of the array
    // is the index of the next unallocated slot
    if( anArray != NULL ){
        size = anArray->size;
        newNode = (struct biNode*)malloc(sizeof(struct biNode));

        if(newNode != NULL){
            if( size == 0 ){
                anArray->root = newNode;
                (anArray->size)++;
                return 0;
            } else {
                newNode->data = data;
                // Find the parent of the next slot in the tree and...
                if( size % 2 ){
                    //if the next slot is even, set the right child
                    //to the new node
                    __getNode__((size-1)/2, anArray)->rLink = newNode;
                } else {
                    //otherwise set the left child to it
                    __getNode__((size-1)/2, anArray)->lLink = newNode;
                }
                (anArray->size)++;
                if( size > anArray->endOfRow + 1){ //We have begun a new row
                    if(size > 1) (anArray->depth)++;
                    // The next end of row is the previous plus the next power of 2         
                    anArray->endOfRow += 2 << anArray->depth;
                }               
                return 0;
            }
        }
    }
    return -1;
}

struct biNode* __recNodeDelete__( struct biNode* aNode ){
    free(aNode->data);
    aNode->data = NULL;

    if(aNode->lLink != NULL){ 
        free( __recNodeDelete__(aNode->lLink));
        aNode->lLink = NULL;
    }
    if(aNode->rLink != NULL){
        free( __recNodeDelete__(aNode->rLink));
        aNode->rLink = NULL;
    }

    return aNode;
}

void deleteBiArray( struct biArray* anArray){
   free( __recNodeDelete__(anArray->root));
   free(anArray);
}
