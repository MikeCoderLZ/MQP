#ifndef G_TEXTURE_H_
#define G_TEXUTRE_H_

#include "./gSuite.h"
#include "../dataStruct/cirDList.h"

struct gTexParams{

    /**There is no parameter for number of samples in a multisample
     * textur.  I can't find a function that sets that parametr, so I
     * am guessing it might be set when you print a multisample
     * renderbuffer to a texture, since that is the only place you
     * multisampled pixel data */

    /** Filtering settings*/
    GLenum minFilter;
    GLenum magFilter;

    /**How to wrap texture coordinates; Remember to use CLAMP_TO_EDGE
     * for non-tiling textures*/
    GLenum wrapS;
    GLenum wrapT;
    GLenum wrapR;

    /**Don't know what this does yet*/
    GLfloat priority;
    /**Min and Max LOD sampling; don't confuse this with Levels*/
    GLfloat minLod;
    GLfloat maxLod;
    GLfloat lodBias;
    /**The Min and Max mipmap levels*/
    GLuint baseLevels;
    GLuint maxLevels;
    /**Depth map info, basically; the mode and function params
     * are for depth-based shadow maps*/
    GLenum depthMode;
    GLenum compareMode;
    GLenum compareFunc;

};
typedef struct gTexParams GTexParams;

struct gImageParams{

    GLint imageLevel;

    GLenum glImageFormat;

    GLsizei width;
    GLsizei height;
    GLsizei depth;
    GLsizei samples;

    GLenum componentFormat;
    GLenum componentType;
    GDataPtr imageData;

};
typedef struct gImageParams GImageParams;

struct gTexture{

    GLuint glID;

    GLenum defaultTarget;
    GLenum currentTarget;

    GLenum defaultUnit;
    GLenum currentUnit;
    gBool isBound;
    
    /** These are for attaching textures to framebuffers*/
    GLenum defaultAttachment;
    GLenum currentAttachment;
    gBool isAttached;

    CirDList *imageParams;

    GTexParams *parameters;

};
typedef struct gTexture GTexture;

GTexture *newGTexture(GLenum target, GLenum unit);

/**This changes the current target of the texture*/
gReturn setGTextureTarget(GTexture *self, GLenum target);
/**This changes the current target to the default target*/
gReturn resetGTextureTarget(GTexture *self);
/**This changes the default target of the texture*/
gReturn changeGTextureTarget(GTexture *self, GLenum target);

/**This changes the current unit of the texture*/
gReturn setGTextureUnit(GTexture *self, GLenum unit);
/**This changes the current unit to the default target*/
gReturn resetGTextureUnit(GTexture *self);
/**This changes the default unit of the texture*/
gReturn changeGTextureUnit(GTexture *self, GLenum unit);

/**Currently the Active texture image unit will be set to whatever
 * the current one is for the this texture*/
gReturn bindGTexture(GTexture *self);

/**This changes the current attachment of the texture*/
gReturn setGTextureAttachment(GTexture *self, GLenum attachment);
/**This changes the current attachment to the default target*/
gReturn resetGTextureAttachment(GTexture *self);
/**This changes the default attachment of the texture*/
gReturn changeGTextureAttachment(GTexture *self, GLenum attachment);

gReturn setFilters( GTexture *self,
                    GLenum minFilter,
                    GLenum magFilter);
gReturn setMinFilter( GTexture *self, GLenum minFilter);
gReturn setMagFilter( GTexture *self, GLenum magFilter);

gReturn loadFilters( GTexture *self);

gReturn setWrapping( GTexture *self,
                     GLenum wrapS,
                     GLenum wrapT,
                     GLenum wrapR);
gReturn setWrapS( GTexture *self, GLenum wrapS);
gReturn setWrapT( GTexture *self, GLenum wrapT);
gReturn setWrapR( GTexture *self, GLenum wrapR);

gReturn loadWrapping( GTexture *self);

gReturn setPriority( GTexture *self, GLfloat priority);

gReturn loadPriority( GTexture *self);

gReturn setLods( GTexture *self,
                 GLfloat lodBias,
                 GLfloat minLod,
                 GLfloat maxLod);
gReturn setLodBias( GTexture *self, GLenum lodBias);
gReturn setMinLod( GTexture *self, GLfloat minLod);
gReturn setMaxLod( GTexture *self, GLfloat maxLod);

gReturn loadLods( GTexture *self);


gReturn setLevels( GTexture *self,
                    GLint baseLevels,
                    GLint maxLevels);
gReturn setBaseLevels( GTexture *self, GLint baseLevels);
gReturn setMaxLevels( GTexture *self, GLint maxLevels);

gReturn loadLevels( GTexture *self);

gReturn setDepthComp( GTexture *self,
                      GLenum depthMode,
                      GLenum depthCompareMode,
                      GLenum depthCompareFunc);
gReturn setDepthMode( GTexture *self, GLenum depthMode);
gReturn setDepthCompareMode( GTexture *self, GLenum depthCompareMode);
gReturn setDepthCompareFunc( GTexture *self, GLenum depthCompareFunc);

gReturn loadDepthComp( GTexture *self);

gReturn loadParams( GTexture *self);

/**
 * Adding an image adds the image specified to the GTexture given.
 * The given GTexture is bound during this process, so be careful
 * until a binding control stack can be written up to alleviate
 * the issues implicit with such a system.
 */

gReturn addImage1D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData);

gReturn addImage2D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLsizei height,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData);

gReturn addImage3D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLsizei height,
                    GLsizei depth,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData);

struct gRenderbuffer{
    GLuint glID;

    GLenum storageFormat;

    GLsizei width;
    GLsizei height;

    GLsizei samples;

    GLenum defaultAttachment;
    GLenum currentAttachment;
    gBool isAttached;

};
typedef struct gRenderbuffer GRenderbuffer;

//GRenderbuffer *newGRenderbuffer(void);
GRenderbuffer *makeGRenderbuffer(GLenum storageFormat,
                                 GLsizei width,
                                 GLsizei height,
                                 GLsizei samples,
                                 GLenum attachmentPoint);
gReturn loadGRenderbuffer(GRenderbuffer *self);

gReturn deleteGRenderbuffer(GRenderbuffer **self);

#endif

