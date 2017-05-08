//mikeoliver

#ifndef CIRDLIST_H
#define CIRDLIST_H
#include <stddef.h>
#include "nodes.h"

// Include thread functionality if we are compiling for thread mode
#ifdef THREAD_MODE
#include <semaphore.h>
#endif

/**
* A cirDList is a circular doubly-linked list.  It has one
* internal pointer to the elements of the list called the cursor.
* Insertions and deletions happen at this point, and there are 
* two variations, next and previous, for each operation.
*
* Inserting to next inserts the data into the list "ahead" of the cursor.
* Inserting to previous inserts "behind" the cursor.  THe cursor does
* not move after insertions; it remains on the data element it was on
* before insertions.
*
* Removals in the list are called "snips" since you are clipping the
* element out.  Snipping to next leaves the cursor on what would be
* the next element, whereas snipping to previous leaves the cursor on
* what would be the previous element.  Retrieve returns the data at
* the curent location of the cursor in the list, it does not remove
* data from the list.
*
* Advance and retreat move the cursor in the direction specified.
* 
*/
struct cirDList {

    size_t size;

    // If compiled in threadsafe mode include semaphore lock on the cursor
    #ifdef THREAD_MODE
    sem_t *listLock;
    sem_t *curLock;
    #endif

    struct biNode *cursor;

};

typedef struct cirDList CirDList;

struct cirDList *newCirDList();

void* retrieve( struct cirDList*);

void* snipToNext( struct cirDList*);

void* snipToPrev( struct cirDList*);

int insertNext( void*, struct cirDList* );

int insertPrev( void*, struct cirDList* );

int advance( struct cirDList*);

int retreat( struct cirDList*);

int stitchNext( struct cirDList*, struct cirDList*);

int stitchPrev( struct cirDList*, struct cirDList*);
#ifdef THREAD_MODE
void lockList( struct cirDList *);

void unlockList( struct cirDList *);
#endif
void deleteCirDList( struct cirDList* );

#endif
