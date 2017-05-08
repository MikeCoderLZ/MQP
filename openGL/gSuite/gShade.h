#ifndef G_SHADE_H_
#define G_SHADE_H_

#include "GL/glew.h"
#include "./gSuite.h"
#include "./gBuffer.h"

/**
 * gShade.h defines the object GShader, which encapsulates all the
 * functionality of OpenGL Programs, Vertex Shaders, Geometry
 * Shaders, and Fragment Shaders.  All you need to do to tell a
 * GShader where to get it's source is to give it the path, file,
 * and effects key for the shader file.  We are using GLSW internally
 * here, so the suntax is a little different from the rest of GSuite.
 */

struct gShader{

    /**The OpenGl assigned index of this shader program*/
    GLuint glID;

    /**GLSW relevent info for loading the source file*/
    const char *path;
    const char *extension;
    /**The string in the file to replace with the uniforms block*/
    /**Deprecated pending correction of GLSW library directive checking*/
    //const char* incDirective;

    /**Self explanatory*/
    int hasGeometryShader;

    /**The OpenGL shader IDs and the GLSW effect keys*/
    GLuint glVID;
    const char *vShaderKey;
    GLuint glGID;
    const char *gShaderKey;
    GLuint glFID;
    const char *fShaderKey;

//    const char* includeKey;

    /**Source code itself*/
    const char *vShaderSrc;
    int vLength;
    const char *gShaderSrc;
    int gLength;
    const char *fShaderSrc;
    int fLength;
//    const char* includeSrc;
//    int incLength;

};
typedef struct gShader GShader;

/**Allocate a new gShader with default fields from <0,NULL>*/
GShader *newGShader(void);
GShader *makeGShader(const char *newPath,
                     const char *newExtension,
                     /**const char* incDirective, /**removed pending GLSW correction*/
                     const char *vKey,
                     const char *gKey,
                     const char *fKey
                     /**,const char* varKey /**removed pending GLSW fix*/);

/**Removed due to complete uselessness of such a function*/
//GShader* wrapGShader(GVShader*, GGShader*, GFShader*);

int deleteGShader(GShader **self);

/**Compiles all currently loaded sub-shaders in the GShader*/
int compileGShader(GShader *self);

/**Links compiled shaders together; only returns G_SUCCESS if all shaders
have been compiled*/
int linkGShader(GShader *self);

/**Link a buffer to the GShader*/
int alignAttribute(GShader *self, GBuffer *buffer, const char *attributeName);

/**Link single uniform variable to program data.*/
int alignUniform(GShader* self,
                      gEnum type,
                      void *data,
                      const char *name);

/**Link array of variables to a uniform variable.*/
int alignUniformV(GShader* self,
                      gEnum type,
                      void **data,
                      GLsizei count,
                      const char *name);

/**Link matrix data to uniform variable.*/
int alignUniformMat(GShader *self,
                    gEnum type,
                    const float *matrix,
                    GLsizei count,
                    GLboolean transpose,
                    const char *name);

#endif