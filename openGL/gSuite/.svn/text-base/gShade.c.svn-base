#include <stdio.h>
#include <string.h>

#include "./gShade.h"
#include "../glsw/glsw.h"

/**
 * Allocate a new, blank GShader.  Fill fields with either 0 or NULL,
 * depending on context.
 */

GShader *newGShader(void){

    GShader *newShader = (GShader *)malloc(sizeof(GShader));

    if(newShader != NULL){

        newShader->glID = glCreateProgram();

        newShader->path = NULL;
        newShader->extension = NULL;
        /**newShader->incDirective = NULL;/**Removed pending GLSW fix*/
        newShader->hasGeometryShader = G_FALSE;

        newShader->vShaderKey = NULL;
        newShader->gShaderKey = NULL;
        newShader->fShaderKey = NULL;
//        newShader->includeKey = NULL;

        newShader->glVID = G_NULL;
        newShader->glGID = G_NULL;
        newShader->glFID = G_NULL;

        newShader->vShaderSrc = NULL;
        newShader->vLength = 0;
        newShader->gShaderSrc = NULL;
        newShader->gLength = 0;
        newShader->fShaderSrc = NULL;
        newShader->fLength = 0;
//        newShader->includeSrc = NULL;

        return newShader;
    }
    return NULL;
}

/**
 * Allocate a GShader.  Fill the fields with the information given.
 * hasGeometryShader will only be set to G_TRUE if a non-NULL pointer
 * is given for gKey.
 */

GShader *makeGShader(const char *newPath,
                     const char *newExtension,
                     /**const char* incDirective, /**removed pending GLSW fix*/
                     const char *vKey,
                     const char *gKey,
                     const char *fKey
                     /**,const char* varKey/** removed pending GLSW fix*/){

    GShader * newShader = (GShader *) malloc(sizeof(GShader));

    if(newShader != NULL){

        newShader->glID = glCreateProgram();

        newShader->path = newPath;
        newShader->extension = newExtension;
        /**newShader->incDirective = incDirective;/**Removed pending GLSW fix*/

        glswInit();

        /**Need to add a library function that allows us to save the
           previous path info so we can set it back afterwords*/
        glswSetPath(newShader->path, newShader->extension);
        /**This makes it so that, when shaders are loaded, the unoforms
        block is prepended to them*/

        /**Load the uniforms string first*/
//        newShader->includeKey = varKey;
//        newShader->includeSrc = glswGetShader(newShader->includeKey);
//        newShader->incLength = (int) strlen(newShader->includeSrc);
        
        /**Block removed pending GLSW fix*/
        /**printf("\n");
        printf(newShader->includeSrc);
        printf("\n");*/

        //glswSetPath(newShader->path, newShader->extension);
        //glswAddDirectiveToken(newShader->incDirective,newShader->includeSrc);//newShader->includeSrc);

        /**Now, load shader sources into the struct and OpenGL*/
        newShader->vShaderKey = vKey;
        newShader->vShaderSrc = glswGetShader(newShader->vShaderKey);
        newShader->vLength = (int) strlen(newShader->vShaderSrc);
        newShader->glVID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(newShader->glVID,
                        1,
                        &(newShader->vShaderSrc),
                        (const GLint*)&(newShader->vLength));

        /**Not every shader needs a geometry shader*/
        if(gKey != NULL){
            newShader->hasGeometryShader = G_TRUE;
            newShader->gShaderKey = gKey;
            newShader->gShaderSrc = glswGetShader(newShader->gShaderKey);
            newShader->gLength = (int) strlen(newShader->gShaderSrc);
            newShader->glGID = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(newShader->glGID,
                            1,
                            &(newShader->gShaderSrc),
                            (const GLint*)&(newShader->gLength));
        } else {
            newShader->hasGeometryShader = G_FALSE;
            newShader->gShaderKey = NULL;
            newShader->gShaderSrc = NULL;
            newShader->gLength = 0;
            newShader->glGID = G_NULL;
        }

        newShader->fShaderKey = fKey;
        newShader->fShaderSrc = glswGetShader(newShader->fShaderKey);
        newShader->fLength = (int) strlen(newShader->fShaderSrc);
        newShader->glFID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(newShader->glFID,
                        1,
                        &(newShader->fShaderSrc),
                        (const GLint*)&(newShader->fLength));

        glswShutdown();

        return newShader;
    }

    return NULL;
}

/**
 * Compile all currently attached shaders in the given GShader.
 */

int compileGShader(GShader* self){

    if(self != NULL){
        if(self->glVID != G_NULL
            && self->glFID != G_NULL){
            glCompileShader(self->glVID);
            glCompileShader(self->glFID);
        } else {
            return G_ID_ZERO;
        }
        if(self->hasGeometryShader){
            if(self->glGID != G_NULL){
                glCompileShader(self->glGID);
            } else {
                return G_ID_ZERO;
            }
        }
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

int linkGShader(GShader* self){

    if( self != NULL){
        if( self->glID != G_NULL){
            if(self->glVID != G_NULL && self->glFID != G_NULL){
                glAttachShader(self->glID, self->glVID);
                glAttachShader(self->glID, self->glFID);
            } else {
                return G_ID_ZERO;
            }

            if(self->glGID != G_NULL){
                glAttachShader(self->glID, self->glGID);
            }
            glLinkProgram(self->glID);
            return G_SUCCESS;
        } else {
            return G_SELF_ID_NULL;
        }
    }
    return G_SELF_NULL;
}

/**
 * Link the given buffer to the attribute of the given name in
 * the GShader given.  Return G_ILLEGAL_SPECIFIER if the given
 * attribute name does not exist in the GBuffer's list of formats.
 */

int alignAttribute(GShader *self,
                   GBuffer *buffer,
                   const char *attributeName){

    if(self != NULL){
        if(buffer != NULL){
            /**Loop through the formats list to find the format with an
            attribute name that matches the given one*/
            size_t formatsChecked = 0;
            size_t totalFormats = buffer->formats->size;

            /**If there are no formats in the list, return now rahter than waste time*/
            if(totalFormats == 0){
                return G_INDEX_OUT_OF_BOUNDS;
            }

            GBufferFormat *currentFormat = NULL;

            for(formatsChecked = 0; formatsChecked < totalFormats; formatsChecked++){
                currentFormat = (GBufferFormat *)retrieve(buffer->formats);
                if(strcmp(currentFormat->attributeName, attributeName) == 0){
                    break;
                } else {
                    advance(buffer->formats);
                }
            }

            /**currentFormat being equal to NULL means we found no matching format*/
            if(currentFormat == NULL){
                return G_ILLEGAL_SPECIFIER;
            }

            GLuint attributeLocation = glGetAttribLocation(self->glID, attributeName);

            glVertexAttribPointer(
                attributeLocation,
                currentFormat->nComponents,
                currentFormat->type,
                currentFormat->normalized,
                currentFormat->stride,
                (void *)(currentFormat->offset)
            );
            glEnableVertexAttribArray(attributeLocation);

            return G_SUCCESS;

        } else {
            return G_OBJECT_NULL;
        }
    }
    return G_SELF_NULL;

}

/**
 * Link program data to the uniform variable of the given name in
 * the given shader.  The data must be a single uniform, usch as a
 * a single float or vector.
 */
int alignUniform(GShader *self,
                   gEnum type,
                   void *data,
                   const char *name){
    if(self != NULL){
        if(self->glID != G_NULL){
            //printf("\n%d", type);
            GLuint uniform = glGetUniformLocation(self->glID, name);

            switch(type){
                case G_INT:
                    glUniform1i(uniform,
                                *((GLint *)data));
                    break;
                case G_INT2:
                    glUniform2i(uniform,
                                ((GLint *)data)[0],
                                ((GLint *)data)[1]);
                    break;
                case G_INT3:
                    glUniform3i(uniform,
                                ((GLint *)data)[0],
                                ((GLint *)data)[1],
                                ((GLint *)data)[2]);
                    break;
                case G_INT4:
                    glUniform4i(uniform,
                                ((GLint *)data)[0],
                                ((GLint *)data)[1],
                                ((GLint *)data)[2],
                                ((GLint *)data)[3]);
                    break;
                case G_FLOAT:
                    glUniform1f(uniform,
                                *((GLfloat *)data));
                    break;
                case G_FLOAT2:
                    glUniform2f(uniform,
                                ((GLfloat *)data)[0],
                                ((GLfloat *)data)[1]);
                    break;
                case G_FLOAT3:
                    glUniform3f(uniform,
                                ((GLfloat *)data)[0],
                                ((GLfloat *)data)[1],
                                ((GLfloat *)data)[2]);
                    break;
                case G_FLOAT4:
                    glUniform4f(uniform,
                                ((GLfloat *)data)[0],
                                ((GLfloat *)data)[1],
                                ((GLfloat *)data)[2],
                                ((GLfloat *)data)[3]);
                    break;
                case G_UINT:
                    glUniform1ui(uniform,
                                 *((GLuint *)data));
                    break;
                case G_UINT2:
                    glUniform2ui(uniform,
                                 ((GLuint *)data)[0],
                                 ((GLuint *)data)[1]);
                    break;
                case G_UINT3:
                    glUniform3ui(uniform,
                                 ((GLuint *)data)[0],
                                 ((GLuint *)data)[1],
                                 ((GLuint *)data)[2]);
                    break;
                case G_UINT4:
                    glUniform4ui(uniform,
                                 ((GLuint *)data)[0],
                                 ((GLuint *)data)[1],
                                 ((GLuint *)data)[2],
                                 ((GLuint *)data)[3]);
                    break;
                default:
                    /**Enum did not match any supported unem for this function*/
                    return G_ILLEGAL_SPECIFIER;
            }
            /**Found a match*/
            return G_SUCCESS;
        } else {
            return G_SELF_ID_NULL;
        }
    }
    return G_SELF_NULL;
}

/**
 * Link program data to the uniform variable of the given name in
 * the given shader.  The data must be an array of values, such as
 * floats or vectors.
 */
int alignUniformV(GShader *self,
                   gEnum type,
                   void *data,
                   GLsizei count,
                   const char *name){
    if(self != NULL){
        if(self->glID != G_NULL){
            GLuint uniform = glGetUniformLocation(self->glID, name);

            switch(type){
                case G_INT_V:
                    glUniform1iv(uniform,
                                 count,
                                 (GLint *)data);
                    break;
                case G_INT2_V:
                    glUniform2iv(uniform,
                                 count,
                                 (GLint *)data);
                    break;
                case G_INT3_V:
                    glUniform3iv(uniform,
                                 count,
                                 (GLint *)data);
                    break;
                case G_INT4_V:
                    glUniform4iv(uniform,
                                 count,
                                 (GLint *)data);
                    break;
                case G_FLOAT_V:
                    glUniform1fv(uniform,
                                 count,
                                 (GLfloat *)data);
                    break;
                case G_FLOAT2_V:
                    glUniform2fv(uniform,
                                 count,
                                 (GLfloat *)data);
                    break;
                case G_FLOAT3_V:
                    glUniform3fv(uniform,
                                 count,
                                 (GLfloat *)data);
                    break;
                case G_FLOAT4_V:
                    glUniform4fv(uniform,
                                 count,
                                 (GLfloat *)data);
                    break;
                case G_UINT_V:
                    glUniform1uiv(uniform,
                                  count,
                                  (GLuint *)data);
                    break;
                case G_UINT2_V:
                    glUniform2uiv(uniform,
                                  count,
                                  (GLuint *)data);
                    break;
                case G_UINT3_V:
                    glUniform3uiv(uniform,
                                  count,
                                  (GLuint *)data);
                    break;
                case G_UINT4_V:
                    glUniform4uiv(uniform,
                                  count,
                                  (GLuint *)data);
                    break;
                default:
                    return G_ILLEGAL_SPECIFIER;
            }
        return G_SUCCESS;
        } else {
            return G_SELF_ID_NULL;
        }
    }
    return G_SELF_NULL;    
}

/**
 * Link program data to the uniform variable of the given name in
 * the given shader.  The data must be an array of matrices.
 */
int alignUniformMat(GShader *self,
                    gEnum type,
                    const float *matrix,
                    GLsizei count,
                    GLboolean transpose,
                    const char *name){

    if(self != NULL){
        if(self->glID != G_NULL){
            GLuint uniform = glGetUniformLocation(self->glID, name);

            switch(type){
                case G_MAT2_V:
                    glUniformMatrix2fv(uniform,
                                       count,
                                       transpose,
                                       (GLfloat *)matrix);
                    break;
                case G_MAT3_V:
                    glUniformMatrix3fv(uniform,
                                       count,
                                       transpose,
                                       (GLfloat *)matrix);
                    break;
                case G_MAT4_V:
                    glUniformMatrix4fv(uniform,
                                       count,
                                       transpose,
                                       (GLfloat *)matrix);
                    break;
                case G_MAT2x3_V:
                    glUniformMatrix2x3fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                case G_MAT2x4_V:
                    glUniformMatrix2x4fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                case G_MAT3x2_V:
                    glUniformMatrix3x2fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                case G_MAT3x4_V:
                    glUniformMatrix3x4fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                case G_MAT4x2_V:
                    glUniformMatrix4x2fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                case G_MAT4x3_V:
                    glUniformMatrix4x3fv(uniform,
                                         count,
                                         transpose,
                                         (GLfloat *)matrix);
                    break;
                default:
                    return G_ILLEGAL_SPECIFIER;
            }
            return G_SUCCESS;
        } else {
            return G_SELF_ID_NULL;
        }
    }
    return G_SELF_NULL;
}
