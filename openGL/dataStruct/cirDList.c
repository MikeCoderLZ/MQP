// mikeoliver

#include "cirDList.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef THREAD_MODE
#include <semaphore.h>
#endif

/*
* This is the implementation for the utilities of the circularly
* double-linked list data structure CirDList, part of my growing
* suite of general-purpose data structures.  The API is designed
* in under an OO paradigm, though unlike the perhaps cleaner method
* of having function pointers inside the structure itself for its
* utilities, the functions are just here.  So no polymorphism.
*
* CirDList is the wrapper for the actual implementation undrneath
* which uses the generic data nodes that all the data structures use.
* The utilities manage the biNodes underneath, using a single pointer
* into the list called the cursor to track location in the list.
* There is no "first" element or absolute cardinality of the data
* elements.  In terms of actual implementation, the "right" direction
* if the biNodes corresponds to NEXT, and "left" to PREVious.
*
* Implementation specific functions are denited with double-
* underscores in the manner of Python.  The header file doesn't
* declare these functions, so no one can call them (unless they
* declare prototypes themselves). They exist largely because the
* double-linking means any operation can be done in either
* direction on the list, and the code is relatively the same.
* To keep this critical code easier to maintain, the actual nuts
* and bolts are in one location.
*
* The delete functions have not been well tested yet, as the scale
* of the projects the lists have been used in hasn't been enough to
* necesitate actually using them.  They are quite dangerous
* functions, and may cause memory leaks and strange data loss if
* they are used on lists that still have elements in them.
*
* If compiled with THREAD_MODE defined, CirDList has full thread
* protection at the list level and hidden within the utilities
* themselves.  This means only one thread can acces the list's data
* at a time, implemented with a semaphore for the list cursor.
* There is also an extra semaphore to lock down the etire list, which
* is called explicitly.  This is useful for enforcing a certain access
* order to the list, though it is a bit of a hack.  Use it only when
* necessary.
*
* It is likely that semaphores are not the optimal choice here because
* not much time is spent in the list.  I used them because there are
* the simplest to use and are very clean.  Later implementations
* may use a spin lock for the curLock and a semaphore for the listLock.
*/

/**
* Return a pointer to a newly allocated empty circular list struct.
*
* THREAD_MODE: The two semaphores are initialized to the value 1, as
*    they are intended to be mutexes
*
* Since malloc is used in the implementation, erno should be set
* accordingly.
*
* @return pointer to a struct cirDList; NULL if allocation failed.
*/
struct cirDList *newCirDList(){

    // Attempt memory allocation
    struct cirDList *newList = (struct cirDList*)malloc(sizeof(struct cirDList));
#ifdef DEBUG
    printf("malloc newList: %d\n", newList);
#endif
    // If memory was allocated...
    if( newList != NULL ){
        //Initialize the plane fields 
        newList->size = 0;
        newList->cursor = NULL;

    #ifdef THREAD_MODE
        // Attempt allocation of both semaphores
        if((newList->curLock = (sem_t*)malloc(sizeof(sem_t))) != NULL
           && (newList->listLock = (sem_t*)malloc(sizeof(sem_t))) != NULL){

              // Only spend time initializing semaphores if both can be allocated
              sem_init( (newList->curLock), 0, 1);
              sem_init( (newList->listLock), 0, 1);
            
        } else {
            // One of the semaphores can't be allocated, so free ones that were
            if(newList->listLock != NULL) free(newList->listLock);
            if(newList->curLock != NULL) free( newList->curLock);
            // Since a part of the allocation failed, the whole allocation
            // failed, so free the list and set to NULL for a safe return value
            free(newList);
            newList = NULL;
        }

    #ifdef DEBUG
        printf("newList: %d listLock: %d\n", newList, newList->listLock);
        printf("newList: %d curLock: %d\n", newList, newList->curLock);
    #endif
    #endif

    }

    // Will be NULL if allocation failed at any point
    return newList;

}

/**
* Return then data currently pointed to by the list cursor.
*
* THREAD MODE: If compiled with threading options on, the retrival
* of the data is thread safe but the data retuned must be threadsafe
* itself in order to ensure safe reading and writing.
*
* The implementation of thread safety here is in under a mutex
* paradigm, so although retrieve() would be considered a read-only
* utility function, it stil blocks other readers.  The read-write
* case is difficult to do properly, though I think Linux does have
* an implementation of it somewhere.
*
* Because it is possible to retrieve data from the list without
* removing it, it is inadvisable to use retrieve() in a threaded
* context.
*/
void* retrieve( struct cirDList *aList){
    // If compiled in THREAD_MODE, then use locking with a temporary
    // variable to pop the data pointer outside the locking
    // mechanism
#ifdef THREAD_MODE
    sem_wait(aList->curLock);
    void *data = aList->cursor->data;
    sem_post(aList->curLock);
    return data;
    // Otherwise, do things the easy way.
#else
    return aList->cursor->data;
#endif

}

/**
* Implementation specific function.  Performs both snipToNext()
* and snipToPrev() based on a integer true/false value.  Importing
* modules do not have access to this function, so don't
* go calling it.
*
* THREAD MODE: In a threaded context the snipTo____() functions
* offer better functionality than retreive() since they remove
* the data from the list, meaning it is much more difficult to
* have multiple threads in possesion of the same data. To ensure
* thread safety, the data itself must be thread safe.
*
* @param toNext
*     snips to previous if 0, to next if non-zero
*/
void* __snip__( struct cirDList *aList, int toNext ){
    // Declare a working biNode and a pointer for the data t be
    // snipped
    struct biNode *snippedData = NULL;
    void *data = NULL;

    #ifdef THREAD_MODE
    sem_wait(aList->curLock);
    #endif

    if( aList->size > 0 ) {
        // Only initialize the snpped data pointer after lock has been
        // obtained and we are certain it is worthwhile
        snippedData = aList->cursor;

        // Technically, this "can never happen", but if it does I'd rather
        // it not explode and try a NULL pointer access.

        if( snippedData == NULL ) {
            #ifdef THREAD_MODE
            sem_post(aList->curLock);
            #endif
            return data;
        // snippedData is a safe pointer to access, so do so and snip
        // the data out and clean up the references.
        } else {
            data = snippedData->data;

            if( aList->size == 1 ){
                deleteBiNode( snippedData );
                aList->cursor = NULL;
                aList->size = 0;
            } else {
                snippedData->lLink->rLink = snippedData->rLink;
                snippedData->rLink->lLink = snippedData->lLink;
                // If we are snipping to the next data element, then advance
                // the cursor.  Otherwise, retreat it.
                aList->cursor = (toNext ? snippedData->rLink : snippedData->lLink);
                (aList->size)--;
                deleteBiNode(snippedData);
            }
        }
    }
    #ifdef THREAD_MODE
    sem_post(aList->curLock);
    #endif
    return data;

}

/**
* Remove the element in the list pointed to by the cursor and return
* that data.
*
* THREAD MODE: Retrieval of the data is thread safe, but the data itself
* must be lockable in order to ensure thread safety of edits to it.
*
* NOTES: It would be advantageous to use an inline specifier here, but
* I won't break my code trying to get it to work if I need to expose
* __snip__() to the importing code
*/
void* snipToNext( struct cirDList *aList ){
    return __snip__( aList, 1);
}

/**
* Remove the element in the list pointed to by the cursor and return
* that data.
*
* THREAD MODE: Retrieval of the data is thread safe, but the data itself
* must be lockable in order to ensure thread safety of edits to it.
*
* NOTES: It would be advantageous to use an inline specifier here, but
* I won't break my code trying to get it to work if I need to expose
* __snip__() to the importing code
*/
void* snipToPrev( struct cirDList *aList ){
    return __snip__( aList, 0 );
}

/**
* Implementation specific function that deals with both insertToNext()
* aht insertToPrev() functionality.
*
* @param toNext
*     insert data into the list before the cursor if zero, after it if
*     non-zero
*/
int __insert__( void *data, struct cirDList *aList, int toNext ){

    struct biNode *newNode = newBiNode();

//printf("Lock engaged\n");

#ifdef THREAD_MODE
    sem_wait(aList->curLock);
#endif

    if( aList->size > 0 && aList->cursor == NULL ){
    #ifdef THREAD_MODE
        sem_post(aList->curLock);
    #endif
//        printf("lock disengaged\n");
        return -1;
    }
 
    if(newNode != NULL){
        newNode->data = data;
        if( aList->size == 0 ){
            newNode->rLink = newNode->lLink = newNode;
            aList->cursor = newNode;
            (aList->size)++;
        } else {
            if( toNext ){
                newNode->lLink = aList->cursor;
                newNode->rLink = aList->cursor->rLink;
                aList->cursor->rLink = newNode->rLink->lLink = newNode;
                (aList->size)++;
                //advance( aList );//I realized that these were unnecessary
            } else {
                newNode->lLink = aList->cursor->lLink;
                newNode->rLink = aList->cursor;
                aList->cursor->lLink = newNode->lLink->rLink = newNode;
                (aList->size)++;
                //retreat( aList );//I realized that these were unnecessary
            }
        }

    #ifdef THREAD_MODE
        sem_post(aList->curLock);
//        printf("lock disengaged\n");
    #endif
        return 0;
    }
#ifdef THREAD_MODE
    sem_post(aList->curLock);
//    printf("lock disengaged\n");
#endif
    return -1;

}

/* Again, these two functions would benefit from inlining, but I
*  don't want to mess things up yet*/

/**
* Insert the given data into the list ahead of the cursor.  The cursor
* does not move.
*
* THREAD MODE: Insertions themselves are safe, but the data einserted must
* itself be safe as well.
*/
int insertNext( void *data, struct cirDList *aList ){
    return __insert__(data, aList, 1);
}

/**
* Insert the given data into the list behind the cursor.  The cursor
* does not move.
*
* THREAD MODE: Insertions themselves are safe, but the data einserted must
* itself be safe as well.
*/
int insertPrev( void *data, struct cirDList *aList ){
    return __insert__(data, aList, 0);
}

/**
* Implementation specific helper function.  advance() and retreat()
* call this method to move the cursor one element ahead or one
* element behind.
*
* @param adv
*     move thi cursor ahead if non-zero, move it back if zero
*/

int __mvCursor__( struct cirDList *aList, int adv ){
    if( aList->size > 0 && aList->cursor == NULL ) return -1;
    #ifdef THREAD_MODE
    sem_wait(aList->curLock);
    #endif
 
    if( aList->size > 1 ){
        if( adv ){
            aList->cursor = aList->cursor->rLink;
        } else {
            aList->cursor = aList->cursor->lLink;
        }
    }
    #ifdef THREAD_MODE
    sem_post(aList->curLock);
    #endif
    return 0;

}

int advance( struct cirDList *aList ){
    return __mvCursor__( aList, 1 );
}

int retreat( struct cirDList *aList ){
    return __mvCursor__( aList, 0 );
}

/**
* Insert the first list into the space ahead of the cursor of the
* second list if stitchNext is non-zero, behind it otherwise.
* The two lists become copies of each other with cursors pointing
* to whatever element they were pointing to beforehand.
*
* If either list or both have zero elements, then the first which
* has zero elements will take on the cursor and size of the other,
* whatever it may be.  This means that two zero-length lists will
* come back as two zero length lists, unchanged.  If listA is
* zero length, then it will take on the properties and data of listB.
*
* This is an implementation specific function, and is masked by
* the header file.  So don't go trying to call it, because you can't.
*/

int __stitch__( CirDList *listA, CirDList *listB, int stitchNext){

    struct biNode *tailA = NULL;
    struct biNode *tailB = NULL;

#ifdef THREAD_MODE
    sem_wait(listA->curLock);
    sem_wait(listB->curLock);
#endif

    if(listA->size == 0){
        listA->cursor = listB->cursor;

    } else if(listB->size == 0){
        listB->cursor = listA->cursor;

    } else if(listB->size == 1){

        if(stitchNext){
            listB->cursor->rLink = listA->cursor->rLink;
            listB->cursor->lLink = listA->cursor;

            listA->cursor->rLink->lLink = listB->cursor;
            listA->cursor->rLink = listB->cursor;
        } else {
            listB->cursor->lLink = listA->cursor->lLink;
            listB->cursor->rLink = listA->cursor;

            listA->cursor->lLink->rLink = listB->cursor;
            listA->cursor->lLink = listB->cursor;
        }

    } else {

        if(stitchNext){
            // The tals are the elements after the cursors
            tailA = listA->cursor->rLink;
            tailB = listB->cursor->rLink;
            // Stitch the tail of listA to the cursor of listB
            listB->cursor->rLink = tailA;
            tailA->lLink = listB->cursor;
            // Stitch the tail ot listB to the cursor of listA
            listA->cursor->rLink = tailB;
            tailB->lLink = listA->cursor;
        } else {
            // The tails are the elemnts before the cursors
            tailA = listA->cursor->lLink;
            tailB = listB->cursor->lLink;
            // Stitch the tail of listA to the cursor of listB
            listB->cursor->lLink = tailA;
            tailA->rLink = listB->cursor;
            // Stitch the tail of listB to the cursor of listA
            listA->cursor->lLink = tailB;
            tailB->rLink = listA->cursor;
        }

    }
    // Technically, both lists now have the same length
    listB->size += listA->size;
    listA->size = listB->size;

#ifdef THREAD_MODE
    sem_post(listA->curLock);
    sem_post(listB->curLock);
#endif

    return 0;

}

/**
* Insert the first list into the space ahaed of the the cursor of
* the second list.  Both lists are cut open after the cursor
* and the first list is inserted such that the element that was
* after its cursor is after the cursor of the second list.
*
* Afterwards, listA is a security hazard for both threads and
* memory.  You should delete it as its elemnets are now in listB.
*/

int stitchNext( CirDList *listA, CirDList *listB){
    return __stitch__(listA, listB, 1);
}
/**
* Insert the first list into the space behind the cursor of the second
* list.
*/

int stitchPrev( CirDList *listA, CirDList *listB){
    return __stitch__(listA, listB, 0);
}

#ifdef THREAD_MODE

/**
* Engage the list's lock.  My Project4 implementation needs this extra
* mutex to properly deal with the boundary condition of strings spanning
* a thread's scan block borders.
*/

void lockList( struct cirDList *aList){

   sem_wait(aList->listLock);

   return;

}

/**
* Disengage the list's lock.  My Project4 implementation needs this extra
* mutex to properly deal with the boundary condition of strings spanning
* a thread's scan block borders.
*/

void unlockList( struct cirDList *aList){

   sem_post(aList->listLock);

   return;

}
#endif

/**
* Free memory associtated with the given list.  All data within the list
* is NOT freed, so do NOT call this function on a list with elements
* still in it unless you know what you are doing.
*/
void deleteCirDList( struct cirDList *aList){

/*    while(aList->size > 0){
        snipToNext(aList);
    }*/
    #ifdef THREAD_MODE
    sem_destroy(aList->listLock);
    sem_destroy(aList->curLock);
    #endif
    free(aList);

    return;

}
