#ifndef BITREE_H
#define BITREE_H
#include <stddef.h>
#include "nodes.h"

struct biTree {

    size_t nodes;
    size_t depth;

    struct biNode *root;
    struct biNode *nextSlot;

};

struct biTree *newBiTree();

int addToBiTree( void* );

int deleteBiTree( struct biTree* );
#endif
