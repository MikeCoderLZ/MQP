#include "./gTexture.h"
#include "../dataStruct/cirDList.h"
#include <stdlib.h>


GTexture *newGTexture(GLenum target, GLenum unit){

    GTexture *newTexture = (GTexture *)malloc(sizeof(GTexture));

    if(newTexture == NULL){
        return NULL;
    }

    GTexParams *newParams = (GTexParams *)malloc(sizeof(GTexParams));

    if(newParams == NULL){
        free(newTexture);
        return NULL;
    }

    CirDList *imageList = newCirDList();


    if(imageList == NULL){
        free(newTexture);
        free(newParams);
        return NULL;
    }

    glGenTextures(1, &(newTexture->glID));

    newTexture->defaultTarget = target;
    newTexture->currentTarget = target;

    newTexture->defaultUnit = unit;
    newTexture->currentUnit = unit;

    newTexture->isBound = G_FALSE;

    newTexture->defaultAttachment = GL_FRONT;
    newTexture->currentAttachment = GL_FRONT;
    newTexture->isAttached = G_FALSE;

    newParams->minFilter = GL_NEAREST;
    newParams->magFilter = GL_NEAREST;

    newParams->wrapS = GL_REPEAT;
    newParams->wrapT = GL_REPEAT;
    newParams->wrapR = GL_REPEAT;

    newParams->priority = 0.0f;

    newParams->minLod = 0.0f;
    newParams->maxLod = 1.0f;
    newParams->lodBias = 0.0f;

    newParams->baseLevels = 0;
    newParams->maxLevels = 1;

    newParams->depthMode = 0;
    newParams->compareMode = 0;
    newParams->compareFunc = 0;

    newTexture->imageParams = imageList;
    newTexture->parameters = newParams;

}

/**This changes the current target of the texture*/
gReturn setGTextureTarget(GTexture *self, GLenum target){
    if(self == NULL) return G_SELF_NULL;

    self->currentTarget = target;
    return G_SUCCESS;   
}
/**This changes the current target to the default target*/
gReturn resetGTextureTarget(GTexture *self){
    if(self == NULL) return G_SELF_NULL;

    self->currentTarget = self->defaultTarget;
    return G_SUCCESS;   
}

/**This changes the default target of the texture*/
gReturn changeGTextureTarget(GTexture *self, GLenum target){
    if(self == NULL) return G_SELF_NULL;

    self->defaultTarget = target;
    return G_SUCCESS;
}

/**This changes the current unit of the texture*/
gReturn setGTextureUnit(GTexture *self, GLenum unit){
    if(self == NULL) return G_SELF_NULL;

    self->currentUnit = unit;
    return G_SUCCESS;   
}
/**This changes the current unit to the default target*/
gReturn resetGTextureUnit(GTexture *self){
    if(self == NULL) return G_SELF_NULL;

    self->currentUnit = self->defaultUnit;
    return G_SUCCESS;    
}
/**This changes the default unit of the texture*/
gReturn changeGTextureUnit(GTexture *self, GLenum unit){
   if(self == NULL) return G_SELF_NULL;

   self->defaultUnit = unit;
   return G_SUCCESS;

}

/**Currently the Active texture image unit will be set to whatever
 * the current one is for the this texture*/
gReturn bindGTexture(GTexture *self){
    if(self == NULL) return G_SELF_NULL;
    if(self->isBound == G_FALSE){
        glActiveTexture( self->currentUnit);
        glBindTexture(self->currentTarget, self->glID);
        self->isBound = G_TRUE;
    }
    return G_SUCCESS;
}

/**This changes the current attachment of the texture*/
gReturn setGTextureAttachment(GTexture *self, GLenum attachment){
    if(self == NULL) return G_SELF_NULL;

    self->currentAttachment = attachment;
    return G_SUCCESS;   
}
/**This changes the current attachment to the default target*/
gReturn resetGTextureAttachment(GTexture *self){
    if(self == NULL) return G_SELF_NULL;

    self->currentAttachment = self->defaultAttachment;
    return G_SUCCESS;   
}
/**This changes the default attachment of the texture*/
gReturn changeGTextureAttachment(GTexture *self, GLenum attachment){
    if(self == NULL) return G_SELF_NULL;

    self->defaultAttachment = attachment;
    return G_SUCCESS;
}

gReturn setFilters( GTexture *self,
                    GLenum minFilter,
                    GLenum magFilter){
    if(self == NULL) return G_SELF_NULL;
    
    self->parameters->minFilter = minFilter;
    self->parameters->magFilter = magFilter;
    return G_SUCCESS;
}

gReturn setMinFilter(GTexture *self, GLenum minFilter){
    if(self == NULL) return G_SELF_NULL;
    
    self->parameters->minFilter = minFilter;
    return G_SUCCESS;
}

gReturn setMagFilter(GTexture *self, GLenum magFilter){
    if(self == NULL) return G_SELF_NULL;

    self->parameters->magFilter = magFilter;
    return G_SUCCESS;
}

gReturn loadFilters( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameteri(self->currentTarget,GL_TEXTURE_MIN_FILTER, self->parameters->minFilter);
    glTexParameteri(self->currentTarget,GL_TEXTURE_MAG_FILTER, self->parameters->magFilter);
    return G_SUCCESS;

}

gReturn setWrapping( GTexture *self,
                     GLenum wrapS,
                     GLenum wrapT,
                     GLenum wrapR){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->wrapS = wrapS;
    self->parameters->wrapT = wrapT;
    self->parameters->wrapR = wrapR;
    return G_SUCCESS;
}

gReturn setWrapS( GTexture *self,
                     GLenum wrapS){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->wrapS = wrapS;
    return G_SUCCESS;
}

gReturn setWrapT( GTexture *self,
                     GLenum wrapT){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->wrapT = wrapT;
    return G_SUCCESS;
}

gReturn setWrapR( GTexture *self,
                     GLenum wrapR){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->wrapR = wrapR;
    return G_SUCCESS;
}

gReturn loadWrapping( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_S, self->parameters->wrapS);
    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_T, self->parameters->wrapT);
    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_R, self->parameters->wrapR);
    return G_SUCCESS;

}

gReturn setPriority( GTexture *self,
                     GLfloat priority){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->priority = priority;
    return G_SUCCESS;
}

gReturn loadPriority( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameterf(self->currentTarget,GL_TEXTURE_PRIORITY, self->parameters->priority);
    return G_SUCCESS;

}


gReturn setLods( GTexture *self,
                    GLfloat lodBias,
                     GLfloat minLod,
                     GLfloat maxLod){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->lodBias = lodBias;
    self->parameters->minLod = minLod;
    self->parameters->maxLod = maxLod;
    return G_SUCCESS;
}

gReturn setLodBias( GTexture *self,
                     GLfloat lodBias){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->lodBias = lodBias;
    return G_SUCCESS;
}


gReturn setMinLod( GTexture *self,
                     GLfloat minLod){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->minLod = minLod;
    return G_SUCCESS;
}

gReturn setMaxLod( GTexture *self,
                     GLfloat maxLod){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->maxLod = maxLod;
    return G_SUCCESS;
}

gReturn loadLods( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameterf(self->currentTarget,GL_TEXTURE_LOD_BIAS, self->parameters->lodBias);
    glTexParameterf(self->currentTarget,GL_TEXTURE_MIN_LOD, self->parameters->minLod);
    glTexParameterf(self->currentTarget,GL_TEXTURE_MAX_LOD, self->parameters->maxLod);
    return G_SUCCESS;

}

gReturn setLevels( GTexture *self,
                     GLint baseLevels,
                     GLint maxLevels){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->baseLevels = baseLevels;
    self->parameters->maxLevels = maxLevels;
    return G_SUCCESS;
}

gReturn setBaseLevels( GTexture *self,
                     GLint baseLevels){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->baseLevels = baseLevels;
    return G_SUCCESS;
}

gReturn setMaxLevels( GTexture *self,
                     GLint maxLevels){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->maxLevels = maxLevels;
    return G_SUCCESS;
}

gReturn loadLevels( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameteri(self->currentTarget,GL_TEXTURE_BASE_LEVEL, self->parameters->baseLevels);
    glTexParameteri(self->currentTarget,GL_TEXTURE_MAX_LEVEL, self->parameters->maxLevels);
    return G_SUCCESS;

}

gReturn setDepthComp( GTexture *self,
                      GLenum depthMode,
                      GLenum depthCompareMode,
                      GLenum depthCompareFunc){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->depthMode = depthMode;
    self->parameters->compareMode = depthCompareMode;
    self->parameters->compareFunc = depthCompareFunc;
    return G_SUCCESS;
}

gReturn setDepthMode( GTexture *self,
                      GLenum depthMode){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->depthMode = depthMode;
    return G_SUCCESS;
}

gReturn setDepthCompareMode( GTexture *self,
                             GLenum depthCompareMode){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->compareMode = depthCompareMode;
    return G_SUCCESS;
}

gReturn setDepthCompareFunc( GTexture *self,
                             GLenum depthCompareFunc){

    if(self == NULL) return G_SELF_NULL;

    self->parameters->compareFunc = depthCompareFunc;
    return G_SUCCESS;
}

gReturn loadDepthComp( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    glTexParameteri(self->currentTarget,GL_DEPTH_TEXTURE_MODE, self->parameters->depthMode);
    glTexParameteri(self->currentTarget,GL_TEXTURE_COMPARE_MODE, self->parameters->compareMode);
    glTexParameteri(self->currentTarget,GL_TEXTURE_COMPARE_FUNC, self->parameters->compareFunc);
    return G_SUCCESS;

}

gReturn loadParams( GTexture *self){

    if(self == NULL) return G_SELF_NULL;

    /**Filters*/
    glTexParameteri(self->currentTarget,GL_TEXTURE_MIN_FILTER, self->parameters->minFilter);
    glTexParameteri(self->currentTarget,GL_TEXTURE_MAG_FILTER, self->parameters->magFilter);
    /**Wrapping*/
    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_S, self->parameters->wrapS);
    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_T, self->parameters->wrapT);
    glTexParameteri(self->currentTarget,GL_TEXTURE_WRAP_R, self->parameters->wrapR);
    /**Priority*/
    glTexParameterf(self->currentTarget,GL_TEXTURE_PRIORITY, self->parameters->priority);
    /**LODs*/
    glTexParameterf(self->currentTarget,GL_TEXTURE_LOD_BIAS, self->parameters->lodBias);
    glTexParameterf(self->currentTarget,GL_TEXTURE_MIN_LOD, self->parameters->minLod);
    glTexParameterf(self->currentTarget,GL_TEXTURE_MAX_LOD, self->parameters->maxLod);
    /**Levels*/
    glTexParameteri(self->currentTarget,GL_TEXTURE_BASE_LEVEL, self->parameters->baseLevels);
    glTexParameteri(self->currentTarget,GL_TEXTURE_MAX_LEVEL, self->parameters->maxLevels);
    /**Depth Components*/
    glTexParameteri(self->currentTarget,GL_DEPTH_TEXTURE_MODE, self->parameters->depthMode);
    glTexParameteri(self->currentTarget,GL_TEXTURE_COMPARE_MODE, self->parameters->compareMode);
    glTexParameteri(self->currentTarget,GL_TEXTURE_COMPARE_FUNC, self->parameters->compareFunc);
    return G_SUCCESS;

}

/**These MAY have buggy behavior if you don't reset the texture bindings to
 the currently active texture image unit;  these functions leave the current
 texture image unit of the texture given active and the texture bound to
 that unit as its current target if it was not previously*/

gReturn addImage1D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData){
    if(self == NULL) return G_SELF_NULL;

    GImageParams *newParams = (GImageParams *)malloc(sizeof(GImageParams));

    if(newParams == NULL) return G_ALLOCATION_FAIL;

    newParams->imageLevel = level;
    newParams->glImageFormat = glImageFormat;
    newParams->width = width;
    newParams->height = 1;
    newParams->depth = 0;
    newParams->componentFormat = componentFormat;
    newParams->componentType = componentType;
    newParams->imageData = imageData;

    insertNext(newParams, self->imageParams);

    if(self->isBound == G_FALSE){
        glActiveTexture(self->currentUnit);
        glBindTexture(self->currentTarget, self->glID);
        self->isBound = G_TRUE;
    }

    glTexImage1D( self->currentTarget,
                  level,
                  glImageFormat,
                  width,
                  0,
                  componentFormat,
                  componentType,
                  (void *)imageData);

    return G_SUCCESS;

}

gReturn addImage2D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLsizei height,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData){
    if(self == NULL) return G_SELF_NULL;

    GImageParams *newParams = (GImageParams *)malloc(sizeof(GImageParams));

    if(newParams == NULL) return G_ALLOCATION_FAIL;

    newParams->imageLevel = level;
    newParams->glImageFormat = glImageFormat;
    newParams->width = width;
    newParams->height = height;
    newParams->depth = 0;
    newParams->componentFormat = componentFormat;
    newParams->componentType = componentType;
    newParams->imageData = imageData;

    insertNext(newParams, self->imageParams);

    if(self->isBound == G_FALSE){
        glActiveTexture(self->currentUnit);
        glBindTexture(self->currentTarget, self->glID);
        self->isBound = G_TRUE;
    }

    glTexImage2D( self->currentTarget,
                  level,
                  glImageFormat,
                  width,
                  height,
                  0,
                  componentFormat,
                  componentType,
                  (void *)imageData);

    return G_SUCCESS;

}

gReturn addImage3D( GTexture *self,
                    GLint level,
                    GLint glImageFormat,
                    GLsizei width,
                    GLsizei height,
                    GLsizei depth,
                    GLenum componentFormat,
                    GLenum componentType,
                    GDataPtr imageData){
    if(self == NULL) return G_SELF_NULL;

    GImageParams *newParams = (GImageParams *)malloc(sizeof(GImageParams));

    if(newParams == NULL) return G_ALLOCATION_FAIL;

    newParams->imageLevel = level;
    newParams->glImageFormat = glImageFormat;
    newParams->width = width;
    newParams->height = height;
    newParams->depth = depth;
    newParams->componentFormat = componentFormat;
    newParams->componentType = componentType;
    newParams->imageData = imageData;

    insertNext(newParams, self->imageParams);

    if(self->isBound == G_FALSE){
        glActiveTexture(self->currentUnit);
        glBindTexture(self->currentTarget, self->glID);
        self->isBound = G_TRUE;
    }

    glTexImage3D( self->currentTarget,
                  level,
                  glImageFormat,
                  width,
                  height,
                  depth,
                  0,
                  componentFormat,
                  componentType,
                  (void *)imageData);

    return G_SUCCESS;

}

GRenderbuffer *makeGRenderbuffer(GLenum storageFormat,
                                 GLsizei width,
                                 GLsizei height,
                                 GLsizei samples,
                                 GLenum attachmentPoint){

    GRenderbuffer *newRender = (GRenderbuffer *)malloc(sizeof(GRenderbuffer));

    if(newRender == NULL) return NULL;

    glGenRenderbuffers(1, &(newRender->glID));

    newRender->storageFormat = storageFormat;
    newRender->width = width;
    newRender->height = height;
    newRender->samples = samples;
    newRender->defaultAttachment = newRender->currentAttachment = attachmentPoint;

    return newRender;

}

gReturn loadGRenderbuffer(GRenderbuffer *self){
    if(self == NULL) return G_SELF_NULL;
    glRenderbufferStorage(GL_RENDERBUFFER, self->storageFormat, self->width, self->height);
    return G_SUCCESS;
}

gReturn deleteGRenderbuffer(GRenderbuffer **self){

    if(*self == NULL) return G_SELF_NULL;

    free(*self);
    *self = NULL;
    return G_SUCCESS;

}