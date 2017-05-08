// mikeoliver

#ifndef NODES_H
#define NODES_H

/**
* The node structures handle the behind-the-scenes business of
* tracking the elements of various data structures.  Any thread-safety
* is implemented in the specific data structure's implementation.
*
* In general, a data structure's specific implementation is the only
* place that these structures should be visable or their utilities
* called.
*/

// A simple data structure node with a single pointer to a child
struct monoNode {

    void *data;

    struct monoNode *rLink;

};

// A simple data structure node with two pointers to its two children.
struct biNode {

    void *data;

    struct biNode *rLink;
    struct biNode *lLink;

};

struct monoNode *newMonoNode();

struct biNode *newBiNode();

void deleteMonoNode( struct monoNode* aMonoNode );

void deleteBiNode( struct biNode* aBiNode);
#endif
