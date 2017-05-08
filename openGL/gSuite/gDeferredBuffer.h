#include "./gSuite.h"
#include "./gTexture.h"
#include "./gShade.h"
#include "../datastruct/cirDList.h"
#ifndef G_DEFERRED_BUFFER_H_
#define G_DEFERRED_BUFFER_H_

/**
 * A GDeferredBuffer is a wrapper for a special combination of an
 * OpenGl Framebuffer, Renderbuffers, Textures, and Shader Program.
 *
 * Initialization of the GDeferredBuffer involves allocation of an
 * offscreen Framebuffer, a set number of Rendrebuffers to be used
 * as render targets, and a number of textures equal to the number
 * of Renderbuffers which the results of a render pass are copied to.
 *
 * You provide the GDeferredBuffer with a shading program to fill the
 * Renderbuffers with.
 */

/**Use this type to name your GDefLayers*/
typedef unsigned int gDefLayerEnum;

/**
 * This structure is a wrapper for a pairing of a GTexture with a
 * a GRenderbuffer*/
struct gDefLayer{

    gDefLayerEnum name;

    GTexture *texture;
    GLint level;
    GLint layer;

    GRenderbuffer *renderbuffer;

};
typedef struct gDefLayer GDefLayer;

/**Allocation of the renderbuffer is done internally.  The
 * attachment point is always the same as the currentAttachment
 * in the given base texture.*/
GDefLayer *makeGDefLayer( gDefLayerEnum name,
                          GTexture *baseTexture,
                          GLint level,
                          GLint layer,
                          GLsizei samples /**multisample renderbuffers*/);

struct gDefBuffer{

    GLuint glFramebufferID;

    /**List of GDefLayers in this GDeferredBuffer*/
    CirDList *defLayers;

    GLenum defaultTarget;
    GLenum currentTarget;
    gBool isBound;

    /**GShader *deferredShader;*/

};
typedef struct gDefBuffer GDefBuffer;

GDefBuffer *newGDefBuffer(void);
GDefBuffer *makeGDefBuffer(GLenum defaultTarget/**,
                                GShader *deferredShader*/);

/**
 * Sets the currentTarget of the deffered buffer's framebuffer.*/
gReturn setGDefBufferTarget(GDefBuffer *self,
                            GLenum target);
/**
 * Sets the current target to the default target of the deferred buffer*/
gReturn resetGDefBufferTarget(GDefBuffer *self);

/** Binds the given deferred buffer ti the curent OpeinGL context.*/
gReturn bindGDefBuffer(GDefBuffer *self);

/**gReturn setDeferredShader(GDefBuffer *self,
                          GShader *deferredShader);*/

/** Adds a deferred layer to this deferred buffer.*/
gReturn addDefLayer( GDefBuffer *self,
                     GDefLayer *defLayer);

/** Returns a texture of the current contents of the given deferred layer.*/
GTexture *getTexture( GDefBuffer *self,
                     gDefLayerEnum name);

#endif