#ifndef G_DIFF_FRAMEWORK_H_
#define G_DIFF_FRAMEWORK_H_

#include "GL/glew.h"
#include "./gSuite.h"
#include "./gBuffer.h"
#include "./gShade.h"

/**
 * A GLayerCfg is a structure that controls the render settings of
 * a specific graphics buffer, such as what shading algorithms to use.
 *
 * Expect alot of refactoring and build-breaks from this structure.
 * */

struct gLayerCfg{

    /** The Data Buffer associated witht his layer */
    GBuffer* layerBuffer;

    /**
     * Shader Controls and links. These will later be replaced by
     * my thread-safe linked-lists for shader swapping in the paint()
     * function.  Only one per Buffer for now.
     */
    GShader* shadeProgram;

    // GL Buffer configuration settings

    /**Paint function; implementation specific.  The void* parameter lets
     * you pass in one structure as an argument*/
    int (*paint)(struct gLayerCfg*, void*);
};
typedef struct gLayerCfg GLayerCfg;

/**
 * Return a pointer to a newly allocated GBufferCfg struct.
 * */

GLayerCfg* newGLayerCfg();

GLayerCfg* wrapGLayerCfg(int(*)(GLayerCfg*, void*),GBuffer*, GShader*);



/**
 * Frees the memory associated with the GBufferCfg given.
 * The pointer given points to the pointer of the GBufferCfg to free;
 * after a successful free operation, the given pointer is set to NULL.
 * */
int deleteGLayerCfg(GLayerCfg**);

/**struct gCamera{

    GVector3f* upVector;
    GVector3f*

}*/

/**
 * RenderCFG is a structure which encapsulates a defered shading setup.
 * It holds an array of GBuffers and references to compositing routines
 * as well as the communication hub to World Control's geometry
 * information.
 * */

struct gRenderCfg{

    // GBuffer list.  Array will probably be fine; we can upgrade to
    // LLists if we need to.

    GLayerCfg** bufferCfgs;
    size_t nBuffers;

    // The render routine is implementation specific; you'll need
    // to implement it and assign it to the renderCfg structure.
    // You pass it a pointer to the renderCfg structure that will
    // use it when you call the function

    int (*render)(struct gRenderCfg*, void*);

};

typedef struct gRenderCfg GRenderCfg;

/**
 * Return a newly allocated pointer to a blank RenderCfg structure.
 * The integer parameter indicates how many GBuffers will exists in
 * this RenderCfg.
 * */
GRenderCfg* newGRenderCfg(size_t);
GRenderCfg* makeGRenderCfg(size_t,int(*)(GRenderCfg*, void*));

int setBufferN(GRenderCfg*, size_t, GLayerCfg*);

/**
 * Free the memory associated with the given RenderCfg structure.
 * The pointer given is a pointer to the pointer that points to the
 * RenderCfg structure you wish to delete.
 * After a successful free operation, the pointer to the RenderCfg
 * is set to NULL, NOT the pointer passed.
 * */

int deleteGRenderCfg(GRenderCfg**);

/**
 * Retrieve a pointer to a GBufferCfg by index.
 * */
GLayerCfg* getGFrameBuffCfg(size_t);

#endif