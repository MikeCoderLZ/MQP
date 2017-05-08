#ifndef G_BUFFER_H_
#define G_BUFFER_H_

#include "GL/glew.h"
#include "./gSuite.h"
#include "../dataStruct/cirDList.h"

struct gBufferFormat{

    /**The attribute this format maps a buffer to*/
    const char *attributeName;

    /**Number of bytes of data in the array*/
    GLint nComponents;
    /**Data type of elements in buffer*/
    GLenum type;
    /**If the values should be normalized*/
    GLboolean normalized;
    /**The number of bytes in one chunk of data*/
    GLsizei stride;
    /**The offset into the buffer of the data*/
    GLuint offset;

};
typedef struct gBufferFormat GBufferFormat;

GBufferFormat *newGBufferFormat(void);
GBufferFormat *makeGBufferFormat(const char *attributeName,
                                 GLint nComponents,
                                 GLenum type,
                                 GLboolean normalized,
                                 GLuint offset);
int deleteGBufferFormat(GBufferFormat **self);

/**The default stride value is sizeof(type) * nElements.  That means no
 * skips.  So if you want to use your own stride in the buffer, use this.*/
int setStride(GBufferFormat *self, GLsizei stride);

struct gBuffer{

    /**OpenGL assigned buffer ID*/
    GLuint glID;

    /**The intended usage of this buffer interms of memory management*/
    GLuint glMemMode;

    /**Default OpenGL target this buffer binds to when used.*/
    GLenum defaultTarget;
    /**Currently used target*/
    GLenum currentTarget;

    /**Size of data (number of elements in the data array)*/
    GLsizei size;

    /**The actual data array*/
    GDataPtr data;

    /**Formatt structs for storing Attribute alignment info*/
    CirDList *formats;

};
typedef struct gBuffer GBuffer;

GBuffer* newGBuffer(void);
GBuffer* makeGBuffer(GLenum newTarget,
                     GLenum MemMode,
                     GLsizei size,
                     void* newData);
int deleteGBuffer(GBuffer**);

int addFormat(GBuffer *self, GBufferFormat *format);
GBufferFormat *getformat(GBuffer *self, const char *attributeName);

int changeTarget(GBuffer* self, GLenum newTarget);
int resetTarget(GBuffer* self);
int loadGBuffer(GBuffer* self);

int bindGBuffer(GBuffer* self);

/**
* This is intended for use when streaming to a buffer while it is
* being written to.  Since OpenGL halts when you write to an object
* that it is accessing, even if it is impossible for it to corrupt
* the draw calls, you need a way to write and read at the same time.
*
* For later.*/
struct gDoubleBuffer{

    GLuint glIDA;
    void *dataA;

    GLuint glIDB;
    void *dataB;

    GLsizei size;

};

#endif