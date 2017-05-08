#include <stdio.h>
#include "cirDList.h"

int main( int argc, char *argv[] ){

    struct cirDList *aList = newCirDList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    insertNext(&a, aList);
    insertNext(&b, aList);
    insertPrev(&c, aList);
    insertNext(&d, aList);
 
    printf( "%d\n", *((int*) retrieve( aList )));
    advance( aList );
    printf( "%d\n", *((int*) retrieve( aList )));
    advance( aList );
    printf( "%d\n", *((int*) retrieve( aList )));
    advance( aList );
    printf( "%d\n", *((int*) retrieve( aList )));
 
deleteCirDList( aList );

    return 0;

}
