#include <stdlib.h>

#include "./gDeferredBuffer.h"

GDefLayer *makeGDefLayer( gDefLayerEnum name,
                          GTexture *baseTexture,
                          GLint level,
                          GLint layer,
                          GLsizei samples){

    if(baseTexture != NULL){

        GDefLayer *newLayer = (GDefLayer *)malloc(sizeof(GDefLayer));

        if(newLayer == NULL) return NULL;
            
        size_t nImages = baseTexture->imageParams->size;
        size_t imagesChecked = 0;

        GImageParams *currentImage = NULL;

        for(imagesChecked = 0; imagesChecked< nImages; imagesChecked++){
            currentImage = (GImageParams *)retrieve(baseTexture->imageParams);
            if(currentImage->imageLevel == level){
                break;
            }
            advance(baseTexture->imageParams);
        }

        if( currentImage == NULL){
            free(newLayer);
            return NULL;        
        }

        GRenderbuffer *newRenderbuffer = makeGRenderbuffer(currentImage->glImageFormat,
                                                          currentImage->width,
                                                          currentImage->height,
                                                          currentImage->samples,
                                                          baseTexture->currentAttachment);

        if(newRenderbuffer == NULL){
            free(newLayer);
            return NULL;
        }

        newLayer->name = name;
        newLayer->texture = baseTexture;
        newLayer->level = level;
        newLayer->layer = layer;
        newLayer->renderbuffer = newRenderbuffer;

        return newLayer;

    }

    return NULL;
}

GDefBuffer *newGDefBuffer(void){

    GDefBuffer *newDefBuffer = (GDefBuffer *)malloc(sizeof(GDefBuffer));

    if(newDefBuffer == NULL) return NULL;

    GLuint newFramebuffer;
    glGenFramebuffers( 1, &newFramebuffer);

    if(newFramebuffer == 0){
        free(newDefBuffer);
        return NULL;
    }

    CirDList *newLayerList = newCirDList();

    if(newLayerList == NULL){
        free(newDefBuffer);
        glDeleteFramebuffers(1, &newFramebuffer);
        return NULL;
    }

    newDefBuffer->glFramebufferID = newFramebuffer;
    newDefBuffer->defLayers = newLayerList;

    newDefBuffer->defaultTarget = GL_FRAMEBUFFER;
    newDefBuffer->currentTarget = GL_FRAMEBUFFER;
    newDefBuffer->isBound = G_FALSE;

    //newDefBuffer->deferredShader = NULL;

    return newDefBuffer;

}

GDefBuffer *makeGDefBuffer(GLenum defaultTarget/**,
                           GShader *deferredShader*/){

    GDefBuffer *newDefBuffer = (GDefBuffer *)malloc(sizeof(GDefBuffer));

    if(newDefBuffer == NULL) return NULL;

    GLuint newFramebuffer;
    glGenFramebuffers( 1, &newFramebuffer);

    if(newFramebuffer == 0){
        free(newDefBuffer);
        return NULL;
    }

    CirDList *newLayerList = newCirDList();

    if(newLayerList == NULL){
        free(newDefBuffer);
        glDeleteFramebuffers(1, &newFramebuffer);
        return NULL;
    }

    newDefBuffer->glFramebufferID = newFramebuffer;
    newDefBuffer->defLayers = newLayerList;

    newDefBuffer->defaultTarget = defaultTarget;
    newDefBuffer->currentTarget = defaultTarget;
    newDefBuffer->isBound = G_FALSE;

    /**newDefBuffer->deferredShader;*/

    return newDefBuffer;

}

gReturn setGDefBufferTarget(GDefBuffer *self,
                            GLenum target){

    if(self != NULL){
        self->currentTarget = target;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

gReturn resetGDefBufferTarget(GDefBuffer *self){

    if(self != NULL){
        self->currentTarget = self->defaultTarget;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

gReturn bindGDefBuffer(GDefBuffer *self){

    if(self != NULL){
        glBindFramebuffer(self->currentTarget, self->glFramebufferID);
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

/**gReturn setDeferredShader(GDefBuffer *self,
                          GShader *deferredShader){

    if(self == NULL) return G_SELF_NULL;
    if(deferredShader == NULL) return G_OBJECT_NULL;

    self->deferredShader = deferredShader;

    return G_SUCCESS;

}*/

gReturn addDefLayer( GDefBuffer *self,
                     GDefLayer *defLayer){

    if(self != NULL){
        if(defLayer == NULL){
            return G_OBJECT_NULL;
        }
        insertNext(defLayer, self->defLayers);
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

GTexture *getTexture( GDefBuffer *self,
                     gDefLayerEnum name){

    if(self != NULL){
        size_t nLayers = self->defLayers->size;
        size_t currentLayer = 0;

        GDefLayer *theLayer = NULL;

        for(currentLayer = 0; currentLayer < nLayers; currentLayer++){
            theLayer = (GDefLayer *)retrieve(self->defLayers);
            if(theLayer->name == name){
                break;
            }
            advance(self->defLayers);
        }

        if(theLayer == NULL){
            return NULL;
        }

        return theLayer->texture;
    }
    
    return NULL;
}