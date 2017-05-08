#ifndef BIARRARY_H
#define BIARRARY_H
#include <stddef.h>

struct biArray {

    size_t size;
    size_t depth;

    size_t endOfRow;

    struct biNode* root;

};

struct biArray* newBiArray();

void* get( size_t, struct biArray*);

int set( void*, size_t, struct biArray* );

int append( void*, struct biArray* );

void deleteBiArrary( struct biArray* );

#endif
