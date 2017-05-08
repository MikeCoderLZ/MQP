#include "./gBuffer.h"
#include <stdio.h>

GBufferFormat *newGBufferFormat(void){

    GBufferFormat *newBufferFormat = (GBufferFormat *)malloc(sizeof(GBufferFormat));

    if(newBufferFormat != NULL){

        newBufferFormat->attributeName = NULL;
        newBufferFormat->nComponents = 0;
        newBufferFormat->type = GL_FLOAT;
        newBufferFormat->normalized = GL_FALSE;
        newBufferFormat->offset = 0;
        return newBufferFormat;

    }
    return NULL;
}

GBufferFormat *makeGBufferFormat(const char *attributeName,
                                 GLint nComponents,
                                 GLenum type,
                                 GLboolean normalized,
                                 GLuint offset){

    GBufferFormat *newBufferFormat = (GBufferFormat *)malloc(sizeof(GBufferFormat));
    
    if(newBufferFormat != NULL){
        newBufferFormat->attributeName = attributeName;
        newBufferFormat->nComponents = nComponents;
        newBufferFormat->type = type;
        newBufferFormat->normalized = normalized;

        /**Because you've been so good, we'll figure out the stride for you!*/
        GLsizei stride = 0;

        switch(type){
            case GL_FLOAT:
                stride = (GLsizei)(sizeof(GLfloat) * nComponents);
                break;
            case GL_INT:
                stride = (GLsizei)(sizeof(GLint) * nComponents);
                break;
            case GL_UNSIGNED_INT:
                stride = (GLsizei)(sizeof(GLuint) * nComponents);
                break;
            case GL_DOUBLE:
                stride = (GLsizei)(sizeof(GLdouble) * 2 * nComponents);
                break;
            case GL_BYTE:
                stride = (GLsizei)(sizeof(GLbyte) * nComponents);
                break;
            case GL_UNSIGNED_BYTE:
                stride = (GLsizei)(sizeof(GLubyte) * nComponents);
                break;
            case GL_SHORT:
                stride = (GLsizei)(sizeof(GLshort) * nComponents);
                break;
            case GL_UNSIGNED_SHORT:
                stride = (GLsizei)(sizeof(GLushort) * nComponents);
                break;
            case GL_2_BYTES:
                stride = (GLsizei)(sizeof(GLbyte) * 2 * nComponents);
                break;
            case GL_3_BYTES:
                stride = (GLsizei)(sizeof(GLbyte) * 3 * nComponents);
                break;
            case GL_4_BYTES:
                stride = (GLsizei)(sizeof(GLbyte) * 4 * nComponents);
                break;
            default:
                free(newBufferFormat);
                return NULL;
        }
        newBufferFormat->stride = stride;  
        newBufferFormat->offset = offset;

        //printf("%d\n",stride);

        return newBufferFormat;
    }
    return NULL;
}

int deleteGBufferFormat(GBufferFormat **self){

    if(*self != NULL){
        /**The field attributeName is NOT freed, because it is const.
         * thos technically constitues a memory leak, but I am unsure
         of how to deal with it right now.*/
        free(*self);
        *self = NULL;
        return G_SUCCESS;
    }
    return G_SELF_NULL;        
}

int setStride(GBufferFormat *self, GLsizei stride){

    if(self != NULL){
        self->stride = stride;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

GBuffer* newGBuffer(void){

    GBuffer* newBuffer = (GBuffer*)malloc(sizeof(GBuffer));

    if(newBuffer == NULL){
        return NULL;
    }

    CirDList *newList = newCirDList();

    if(newList == NULL){
        free(newBuffer);
        return NULL;
    }
    // Initialize OpenGL ID
    glGenBuffers(1, &(newBuffer->glID));
    // Fill fields with defaults (0, NULL, or ARRAY_BUFFER)
    newBuffer->glMemMode = GL_DYNAMIC_COPY;
    newBuffer->defaultTarget = GL_ARRAY_BUFFER;
    newBuffer->size = 0;
    newBuffer->data = NULL;
    newBuffer->formats = newCirDList();

    return newBuffer;
}

GBuffer* makeGBuffer(GLenum newTarget,
                     GLenum memMode,
                     GLsizei newSize,
                     void* newData){

   GBuffer* newBuffer = (GBuffer*)malloc(sizeof(GBuffer));

    if(newBuffer == NULL){
        return NULL;
    }

    CirDList *newList = newCirDList();

    if(newList == NULL){
        free(newBuffer);
        return NULL;
    }

    // Initialize OpenGL ID
    glGenBuffers(1, &(newBuffer->glID));
    // Fill fields
    newBuffer->glMemMode = memMode;
    newBuffer->defaultTarget = newTarget;
    newBuffer->currentTarget = newTarget;
    newBuffer->size = newSize;
    newBuffer->data = newData;
    newBuffer->formats = newList;

    return newBuffer;
}

int deleteGBuffer(GBuffer** self){

    glDeleteBuffers(1, &((*self)->glID));
    free(*self);
    *self = NULL;
    return 0;
}

int addFormat(GBuffer *self, GBufferFormat *format){

    if(self != NULL){
        if(format != NULL){
            insertNext((void *)format, self->formats);
            retreat(self->formats);
            return G_SUCCESS;
        } else {
            return G_OBJECT_NULL;
        }

    }
    return G_SELF_NULL;
}

int changeTarget(GBuffer* self, GLenum newTarget){

    if(self != NULL){
        self->currentTarget = newTarget;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

int resetTarget(GBuffer* self){

    if(self != NULL){
        self->currentTarget = self->defaultTarget;
        return G_SUCCESS;
    }

    return G_SELF_NULL;

}

int loadGBuffer(GBuffer* self){

    if(self != NULL){
        glBindBuffer(self->currentTarget, self->glID);
        glBufferData(self->currentTarget, self->size, self->data, self->glMemMode);
        return G_SUCCESS;
    }
    return G_SELF_NULL;

}

int bindGBuffer(GBuffer* self){
    if(self != NULL){
        glBindBuffer(self->currentTarget, self->glID);
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}
