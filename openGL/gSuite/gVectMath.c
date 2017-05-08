
/**
 * Implementation for the vecMath module.  Incomplete.
 * */

#include <math.h>
#include "./gVectMath.h"
#include "./gSuite.h"


GVec2f newGVec2f(void){
    return (GVec2f)malloc(sizeof(GLfloat) * 2);
}
GVec3f newGVec3f(void){
    return (GVec3f)malloc(sizeof(GLfloat) * 3);
}
GVec4f newGVec4f(void){
    return (GVec4f)malloc(sizeof(GLfloat) * 4);
}

GVec2f wrapGVec2f(GLfloat x, GLfloat y){
    GVec2f vec = (GVec2f)malloc(sizeof(GLfloat) * 2);
    if(vec != NULL){
        vec[0] = x;
        vec[1] = y;
    }
    return vec;
}

GVec3f wrapGVec3f(GLfloat x, GLfloat y, GLfloat z){
    GVec3f vec = (GVec3f)malloc(sizeof(GLfloat) * 3);
    if(vec != NULL){
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }
    return vec;
}

GVec4f wrapGVec2f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    GVec4f vec = (GVec4f)malloc(sizeof(GLfloat) * 4);
    if(vec != NULL){
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
        vec[3] = w;
    }
    return vec;
}

gReturn delGVec2f(GVec2f *self){
    if(*self != NULL){
        free(*self);
        *self = NULL;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

gReturn delGVec3f(GVec3f *self){
    if(*self != NULL){
        free(*self);
        *self = NULL;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

gReturn delGVec4f(GVec3f *self){
    if(*self != NULL){
        free(*self);
        *self = NULL;
        return G_SUCCESS;
    }
    return G_SELF_NULL;
}

/**
static inline GLfloat getX(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[0];
    }
    return 0.0;
}
static inline GLfloat getY(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[1];
    }
    return 0.0;
}
static inline GLfloat getZ(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[2];
    }
    return 0.0;
}
static inline GLfloat getQ(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[3];
    }
    return 0.0;
}

static inline GLfloat getR(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[0];
    }
    return 0.0;
}
static inline GLfloat getS(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[1];
    }
    return 0.0;
}
static inline GLfloat getT(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[2];
    }
    return 0.0;
}

static inline GLfloat getU(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[0];
    }
    return 0.0;
}
static inline GLfloat getV(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[1];
    }
    return 0.0;
}

static inline GLfloat getW(GVector self){
    if(self != NULL){
        return ((GLfloat *)self)[2];
    }
    return 0.0;
}
*/

static inline GVec3f sub3(GVec3f aVec, GVec3f bVec){

    GVec3f outVec = newGVec3f();

    if(outVec == NULL) return NULL;

    ((GLfloat*)outVec)[0] = ((GLfloat*)aVec)[0] - ((GLfloat*)bVec)[0];
    ((GLfloat*)outVec)[1] = ((GLfloat*)aVec)[1] - ((GLfloat*)bVec)[1];
    ((GLfloat*)outVec)[2] = ((GLfloat*)aVec)[2] - ((GLfloat*)bVec)[2];

    return outVec;

}
static inline GVec2f norm2(GVec2f aVec){

    GLfloat x, y, invMag;

    if(aVec == NULL){
        return NULL;
    }

    GVec2f outVec = newGVec2f();

    if(outVec != NULL){

        /**Square the components*/
        x = aVec[0];
        y = aVec[1];

        x *= x;
        y *= y;

        /**Calculate amgnitude and do the division ahead of time*/
        invMag = 1 / sqrt(x + y);

        outVec[0] = aVec[0] * invMag;
        outVec[1] = aVec[1] * invMag;

        return outVec;
    }
    return NULL;
}

static inline GVec3f norm3(GVec3f aVec){

    GLfloat x, y, z, invMag;

    if(aVec == NULL){
        return NULL;
    }

    GVec3f outVec = newGVec3f();

    if(outVec != NULL){

        x = aVec[0];
        y = aVec[1];
        z = aVec[2];

        x *= x;
        y *= y;
        z *= z;

        invMag = 1 / sqrt(x + y + z);

        outVec[0] = aVec[0] * invMag;
        outVec[1] = aVec[1] * invMag;
        outVec[2] = aVec[2] * invMag;

        return outVec;
    }
    return NULL;
}

static inline GVec4f norm4(GVec4f aVec){

    GLfloat x, y, z, q, invMag;

    if(aVec == NULL){
        return NULL;
    }

    GVec3f outVec = newGVec3f();

    if(outVec != NULL){

        x = aVec[0];
        y = aVec[1];
        z = aVec[2];
        q = aVec[3];

        x *= x;
        y *= y;
        z *= z;
        q *= q;

        invMag = 1 / sqrt(x + y + z + q);

        outVec[0] = aVec[0] * invMag;
        outVec[1] = aVec[1] * invMag;
        outVec[2] = aVec[2] * invMag;
        outVec[3] = aVec[3] * invMag;

        return outVec;
    }
    return NULL;
}

/**These functions are in-place normalizers, that is, the vector given
has its values changed to be normalized*/
static inline gReturn normIP2(GVec2f aVec){

    GLfloat x, y, invMag;

    if(aVec != NULL){

        x = aVec[0];
        y = aVec[1];

        /**Square 'em*/
        x *= x;
        y *= y;

        /**Calculate magnitude and do the division once, ahead of time*/
        invMag = 1 / sqrt(x + y);

        aVec[0] *= invMag;
        aVec[1] *= invMag;

        return G_SUCCESS;
    } 
    return G_SELF_NULL;
}

static inline gReturn normIP3(GVec3f aVec){

    GLfloat x,y,z, invMag;

    if(aVec != NULL){
        x = aVec[0];
        y = aVec[1];
        z = aVec[2];

        x *= x;
        y *= y;
        z *= z;

        invMag = 1 / sqrt(x + y + z);

        aVec[0] *= invMag;
        aVec[1] *= invMag;
        aVec[2] *= invMag;

        return G_SUCCESS;
    } 
    return G_SELF_NULL;
}

static inline gReturn normIP4(GVec4f aVec){

    GLfloat x, y, z, q, invMag;

    if(aVec != NULL){
        x = aVec[0];
        y = aVec[1];
        z = aVec[2];
        q = aVec[3];

        x *= x;
        y *= y;
        z *= z;
        q *= q;

        invMag = 1 / sqrt(x + y + z + q);

        aVec[0] *= invMag;
        aVec[1] *= invMag;
        aVec[2] *= invMag;
        aVec[3] *= invMag;

        return G_SUCCESS;
    } 
    return G_SELF_NULL;
}

static inline GLfloat dot33f(GVec3f aVec, GVec3f bVec){

    return (((GLfloat*) aVec)[0] * ((GLfloat*) bVec)[0]) +
           (((GLfloat*) aVec)[1] * ((GLfloat*) bVec)[1]) +
           (((GLfloat*) aVec)[2] * ((GLfloat*) bVec)[2]);

}

static inline GVec3f cross3f(GVec3f aVec, GVec3f bVec){

    GLfloat ax, ay, az;
    GLfloat bx, by, bz;

    if(aVec == NULL){
        return NULL;
    }

    GVec3f outVec = newGVec3f();

    if(outVec != NULL){

        ax = aVec[0];
        ay = aVec[1];
        az = aVec[2];

        bx = bVec[0];
        by = bVec[1];
        bz = bVec[2];

        outVec[0] = (ay * bz) - (az * by); 
        outVec[1] = (az * bx) - (ax * bz);
        outVec[2] = (ax * by) - (ay * bx);
    }
    return outVec;
}

GMatf newGMatf(void){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        newMatrix->e = NULL;
        newMatrix->rows = 0;
        newMatrix->cols = 0;
        return newMatrix;

    }
    return NULL;
}

GMatf makeGMat44f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r, GLfloat e3c2r,
                   GLfloat e0c3r, GLfloat e1c3r, GLfloat e2c3r, GLfloat e3c3r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 16);

        if(elements != NULL){

            newMatrix->rows = 4;
            newMatrix->cols = 4;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;
            elements[3] = e0c3r;
            /**Row 1*/
            elements[4] = e1c0r;
            elements[5] = e1c1r;
            elements[6] = e1c2r;
            elements[7] = e1c3r;
            /**Row 2*/
            elements[8]  = e2c0r;
            elements[9]  = e2c1r;
            elements[10] = e2c2r;
            elements[11] = e2c3r;
            /**Row 3*/
            elements[12] = e3c0r;
            elements[13] = e3c1r;
            elements[14] = e3c2r;
            elements[15] = e3c3r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat44f( GVec4f col0,
                      GVec4f col1,
                      GVec4f col2,
                      GVec4f col3){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 16);

        if(elements != NULL){

            newMatrix->rows = 4;
            newMatrix->cols = 4;

            /**Column 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];
            elements[3] = ((GLfloat *)col0)[3];
            /**Column 1*/
            elements[4] = ((GLfloat *)col1)[0];
            elements[5] = ((GLfloat *)col1)[1];
            elements[6] = ((GLfloat *)col1)[2];
            elements[7] = ((GLfloat *)col1)[3];
            /**Column 2*/
            elements[8] = ((GLfloat *)col2)[0];
            elements[9] = ((GLfloat *)col2)[1];
            elements[10] = ((GLfloat *)col2)[2];
            elements[11] = ((GLfloat *)col2)[3];
            /**Column 3*/
            elements[12] = ((GLfloat *)col3)[0];
            elements[13] = ((GLfloat *)col3)[1];
            elements[14] = ((GLfloat *)col3)[2];
            elements[15] = ((GLfloat *)col3)[3];

            newMatrix->e = elements;

            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat44f( GVec4f row0,
                      GVec4f row1,
                      GVec4f row2,
                      GVec4f row3){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 16);

        if(elements != NULL){

            newMatrix->rows = 4;
            newMatrix->cols = 4;

            /**Column 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];
            elements[3] = ((GLfloat *)row3)[0];
            /**Column 1*/
            elements[4] = ((GLfloat *)row0)[1];
            elements[5] = ((GLfloat *)row1)[1];
            elements[6] = ((GLfloat *)row2)[1];
            elements[7] = ((GLfloat *)row3)[1];
            /**Column 2*/
            elements[8] = ((GLfloat *)row0)[2];
            elements[9] = ((GLfloat *)row1)[2];
            elements[10] = ((GLfloat *)row2)[2];
            elements[11] = ((GLfloat *)row3)[2];
            /**Column 3*/
            elements[12] = ((GLfloat *)row0)[3];
            elements[13] = ((GLfloat *)row1)[3];
            elements[14] = ((GLfloat *)row2)[3];
            elements[15] = ((GLfloat *)row3)[3];

            newMatrix->e = elements;

            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 4x3 memory layout
 *
 * +--+--+--+--+
 * | 0| 3| 6| 9|
 * +--+--+--+--+
 * | 1| 4| 7|10|
 * +--+--+--+--+
 * | 2| 5| 8|11|
 * +--+--+--+--+
 *
*/

GMatf makeGMat43f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r, GLfloat e3c2r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 3;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;
            /**Row 1*/
            elements[3] = e1c0r;
            elements[4] = e1c1r;
            elements[5] = e1c2r;
            /**Row 2*/
            elements[6]  = e2c0r;
            elements[7]  = e2c1r;
            elements[8] = e2c2r;
            /**Row 3*/
            elements[9] = e3c0r;
            elements[10] = e3c1r;
            elements[11] = e3c2r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat43f( GVec3f col0,
                      GVec3f col1,
                      GVec3f col2,
                      GVec3f col3){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 3;

            /**Row 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];
            /**Row 1*/
            elements[3] = ((GLfloat *)col1)[0];
            elements[4] = ((GLfloat *)col1)[1];
            elements[5] = ((GLfloat *)col1)[2];
            /**Row 2*/
            elements[6]  = ((GLfloat *)col2)[0];
            elements[7]  = ((GLfloat *)col2)[1];
            elements[8] = ((GLfloat *)col2)[2];
            /**Row 3*/
            elements[9] = ((GLfloat *)col3)[0];
            elements[10] = ((GLfloat *)col3)[1];
            elements[11] = ((GLfloat *)col3)[2];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat43f( GVec4f row0,
                      GVec4f row1,
                      GVec4f row2){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 3;

            /**Row 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];
            /**Row 1*/
            elements[3] = ((GLfloat *)row0)[1];
            elements[4] = ((GLfloat *)row1)[1];
            elements[5] = ((GLfloat *)row2)[1];
            /**Row 2*/
            elements[6]  = ((GLfloat *)row0)[2];
            elements[7]  = ((GLfloat *)row1)[2];
            elements[8] = ((GLfloat *)row2)[2];
            /**Row 3*/
            elements[9] = ((GLfloat *)row0)[3];
            elements[10] = ((GLfloat *)row1)[3];
            elements[11] = ((GLfloat *)row2)[3];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 4x2 memory layout
 *
 * +--+--+
 * | 0| 4|
 * +--+--+
 * | 1| 5|
 * +--+--+
 * | 2| 6|
 * +--+--+
 * | 3| 7|
 * +--+--+
 *
*/

GMatf makeGMat42f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            /**Row 1*/
            elements[2] = e1c0r;
            elements[3] = e1c1r;
            /**Row 2*/
            elements[4]  = e2c0r;
            elements[5]  = e2c1r;
            /**Row 3*/
            elements[6] = e3c0r;
            elements[7] = e3c1r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat42f( GVec2f col0,
                      GVec2f col1,
                      GVec2f col2,
                      GVec2f col3){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            /**Row 1*/
            elements[2] = ((GLfloat *)col1)[0];
            elements[3] = ((GLfloat *)col1)[1];
            /**Row 2*/
            elements[4]  = ((GLfloat *)col2)[0];
            elements[5]  = ((GLfloat *)col2)[1];
            /**Row 3*/
            elements[6] = ((GLfloat *)col3)[0];
            elements[7] = ((GLfloat *)col3)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat42f( GVec4f row0,
                      GVec4f row1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 4;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            /**Row 1*/
            elements[2] = ((GLfloat *)row0)[1];
            elements[3] = ((GLfloat *)row1)[1];
            /**Row 2*/
            elements[4]  = ((GLfloat *)row0)[2];
            elements[5]  = ((GLfloat *)row1)[2];
            /**Row 3*/
            elements[6] = ((GLfloat *)row0)[3];
            elements[7] = ((GLfloat *)row1)[3];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**3 column matrices*/

/**
 * 3x4 memory layout
 *
 * +--+--+--+
 * | 0| 4| 8|
 * +--+--+--+
 * | 1| 5| 9|
 * +--+--+--+
 * | 2| 6|10|
 * +--+--+--+
 * | 3| 7|11|
 * +--+--+--+
 *
*/

GMatf makeGMat34f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r,
                   GLfloat e0c3r, GLfloat e1c3r, GLfloat e2c3r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 4;
            
            /**Column 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;
            elements[3] = e0c3r;
            /**Column 1*/
            elements[4] = e1c0r;
            elements[5] = e1c1r;
            elements[6] = e1c2r;
            elements[7] = e1c3r;
            /**Column 2*/
            elements[8]  = e2c0r;
            elements[9]  = e2c1r;
            elements[10] = e2c2r;
            elements[11] = e2c3r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat34f( GVec4f col0,
                      GVec4f col1,
                      GVec4f col2){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 4;

            /**Column 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];
            elements[3] = ((GLfloat *)col0)[3];

            /**Column 1*/
            elements[4] = ((GLfloat *)col1)[0];
            elements[5] = ((GLfloat *)col1)[1];
            elements[6] = ((GLfloat *)col1)[2];
            elements[7] = ((GLfloat *)col1)[3];

            /**Column 2*/
            elements[8] = ((GLfloat *)col2)[0];
            elements[9] = ((GLfloat *)col2)[1];
            elements[10] = ((GLfloat *)col2)[2];
            elements[11] = ((GLfloat *)col2)[3];

            newMatrix->e = elements;

            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat34f( GVec3f row0,
                      GVec3f row1,
                      GVec3f row2,
                      GVec3f row3){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 12);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 4;

            /**Column 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];
            elements[3] = ((GLfloat *)row3)[0];

            /**Column 1*/
            elements[4] = ((GLfloat *)row0)[1];
            elements[5] = ((GLfloat *)row1)[1];
            elements[6] = ((GLfloat *)row2)[1];
            elements[7] = ((GLfloat *)row3)[1];
            

            /**Column 2*/
            elements[8] = ((GLfloat *)row0)[2];
            elements[9] = ((GLfloat *)row1)[2];
            elements[10] = ((GLfloat *)row2)[2];
            elements[11] = ((GLfloat *)row3)[2];

            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 3x3 memory layout
 *
 * +--+--+--+
 * | 0| 3| 6|
 * +--+--+--+
 * | 1| 4| 7|
 * +--+--+--+
 * | 2| 5| 8|
 * +--+--+--+
 *
*/

GMatf makeGMat33f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 9);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 3;
            
            /**Column 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;

            /**Column 1*/
            elements[3] = e1c0r;
            elements[4] = e1c1r;
            elements[5] = e1c2r;

            /**Column 2*/
            elements[6]  = e2c0r;
            elements[7]  = e2c1r;
            elements[8] = e2c2r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat33f( GVec3f col0,
                      GVec3f col1,
                      GVec3f col2){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 9);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 3;
            
            /**Column 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];

            /**Column 1*/
            elements[3] = ((GLfloat *)col1)[0];
            elements[4] = ((GLfloat *)col1)[1];
            elements[5] = ((GLfloat *)col1)[2];

            /**Column 2*/
            elements[6]  = ((GLfloat *)col2)[0];
            elements[7]  = ((GLfloat *)col2)[1];
            elements[8] = ((GLfloat *)col2)[2];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat33f( GVec3f row0,
                      GVec3f row1,
                      GVec3f row2){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 9);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 3;
            
            /**Column 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];

            /**Column 1*/
            elements[3] = ((GLfloat *)row0)[1];
            elements[4] = ((GLfloat *)row1)[1];
            elements[5] = ((GLfloat *)row2)[1];

            /**Column 2*/
            elements[6]  = ((GLfloat *)row0)[2];
            elements[7]  = ((GLfloat *)row1)[2];
            elements[8] = ((GLfloat *)row2)[2];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 3x2 memory layout
 *
 * +--+--+--+
 * | 0| 2| 4|
 * +--+--+--+
 * | 1| 3| 5|
 * +--+--+--+
 *
*/

GMatf makeGMat32f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 2;
            
            /**Column 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;

            /**Column 1*/
            elements[2] = e1c0r;
            elements[3] = e1c1r;

            /**Column 2*/
            elements[4]  = e2c0r;
            elements[5]  = e2c1r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat32f( GVec2f col0,
                      GVec2f col1,
                      GVec2f col2){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 2;
            
            /**Column 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];

            /**Column 1*/
            elements[2] = ((GLfloat *)col1)[0];
            elements[3] = ((GLfloat *)col1)[1];

            /**Column 2*/
            elements[4] = ((GLfloat *)col2)[0];
            elements[5] = ((GLfloat *)col2)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat32f( GVec3f row0,
                      GVec3f row1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 3;
            newMatrix->rows = 2;
            
            /**Column 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];

            /**Column 1*/
            elements[2] = ((GLfloat *)row0)[1];
            elements[3] = ((GLfloat *)row1)[1];

            /**Column 2*/
            elements[4] = ((GLfloat *)row0)[2];
            elements[5] = ((GLfloat *)row1)[2];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 2x4 memory layout
 *
 * +--+--+
 * | 0| 4|
 * +--+--+
 * | 1| 5|
 * +--+--+
 * | 2| 6|
 * +--+--+
 * | 3| 7|
 * +--+--+
 *
*/

GMatf makeGMat24f( GLfloat e0c0r, GLfloat e1c0r,
                   GLfloat e0c1r, GLfloat e1c1r,
                   GLfloat e0c2r, GLfloat e1c2r,
                   GLfloat e0c3r, GLfloat e1c3r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 4;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;
            elements[3] = e0c3r;
            /**Row 1*/
            elements[4] = e1c0r;
            elements[5] = e1c1r;
            elements[6] = e1c2r;
            elements[7] = e1c3r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat24f( GVec4f col0,
                      GVec4f col1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 4;

            /**Row 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];
            elements[3] = ((GLfloat *)col0)[3];
            /**Row 1*/
            elements[4] = ((GLfloat *)col1)[0];
            elements[5] = ((GLfloat *)col1)[1];
            elements[6] = ((GLfloat *)col1)[2];
            elements[7] = ((GLfloat *)col1)[3];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat24f( GVec2f row0,
                      GVec2f row1,
                      GVec2f row2,
                      GVec2f row3){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 8);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 4;

            /**Row 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];
            elements[3] = ((GLfloat *)row3)[0];
            /**Row 1*/
            elements[4] = ((GLfloat *)row0)[1];
            elements[5] = ((GLfloat *)row1)[1];
            elements[6] = ((GLfloat *)row2)[1];
            elements[7] = ((GLfloat *)row3)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 2x3 memory layout
 *
 * +--+--+
 * | 0| 3|
 * +--+--+
 * | 1| 4|
 * +--+--+
 * | 2| 5|
 * +--+--+
 *
*/

GMatf makeGMat23f( GLfloat e0c0r, GLfloat e1c0r,
                   GLfloat e0c1r, GLfloat e1c1r,
                   GLfloat e0c2r, GLfloat e1c2r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 3;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;
            elements[2] = e0c2r;

            /**Row 1*/
            elements[3] = e1c0r;
            elements[4] = e1c1r;
            elements[5] = e1c2r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat23f( GVec3f col0,
                      GVec3f col1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 3;

            /**Column 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];
            elements[2] = ((GLfloat *)col0)[2];

            /*Column 1*/
            elements[3] = ((GLfloat *)col1)[0];
            elements[4] = ((GLfloat *)col1)[1];
            elements[5] = ((GLfloat *)col1)[2];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat23f( GVec2f row0,
                      GVec2f row1,
                      GVec2f row2){

    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 6);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 3;

            /**Column 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];
            elements[2] = ((GLfloat *)row2)[0];

            /*Column 1*/
            elements[3] = ((GLfloat *)row0)[1];
            elements[4] = ((GLfloat *)row1)[1];
            elements[5] = ((GLfloat *)row2)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

/**
 * 2x2 memory Layout
 *
 * +--+--+
 * | 0| 2|
 * +--+--+
 * | 1| 3|
 * +--+--+
 *
*/


GMatf makeGMat22f( GLfloat e0c0r, GLfloat e1c0r,
                   GLfloat e0c1r, GLfloat e1c1r){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 4);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = e0c0r;
            elements[1] = e0c1r;

            /**Row 1*/
            elements[2] = e1c0r;
            elements[3] = e1c1r;

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeColGMat22f( GVec2f col0,
                      GVec2f col1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 4);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = ((GLfloat *)col0)[0];
            elements[1] = ((GLfloat *)col0)[1];

            /**Row 1*/
            elements[2] = ((GLfloat *)col1)[0];
            elements[3] = ((GLfloat *)col1)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf makeRowGMat22f( GVec2f row0,
                      GVec2f row1){


    GMatf newMatrix = (GMatf)malloc(sizeof(struct gMatf));

    if(newMatrix != NULL){

        GLfloat *elements = (GLfloat *)malloc(sizeof(GLfloat) * 4);

        if(elements != NULL){

            newMatrix->cols = 2;
            newMatrix->rows = 2;

            /**Row 0*/
            elements[0] = ((GLfloat *)row0)[0];
            elements[1] = ((GLfloat *)row1)[0];

            /**Row 1*/
            elements[2] = ((GLfloat *)row0)[1];
            elements[3] = ((GLfloat *)row1)[1];

            newMatrix->e = elements;
            
            return newMatrix;

        } else {
            /**The element array allocation failed, so free the matrix*/
            free(newMatrix);
        }
    }
    return NULL;
}

GMatf getIdentity( unsigned int size){
    
    size_t currentElement = 0;
    size_t nElements = 0;
    size_t diagonalOffset = 0;

    GLfloat *elements = NULL;
    
    GMatf idMat = NULL;

    if( size == 0 ) return NULL;

    idMat = (GMatf)malloc(sizeof(struct gMatf));

    if(idMat == NULL) return NULL;

    nElements = size * size;
    diagonalOffset = size + 1;

    elements = (GLfloat *)malloc(sizeof(GLfloat) * nElements);

    if( elements == NULL){
        free(idMat);
        return NULL;
    }

    for(currentElement = 0; currentElement < nElements; currentElement++){
        *elements = 0;

        /**If the current element is on the diagonal, change its value to 1*/
        if( currentElement % (diagonalOffset) == 0){
            *elements = 1;
        }

        elements++;
    }
    /**Reset the elements pointer to point to the begining of the array*/
    elements -= nElements;

    idMat->e = elements;
    idMat->cols = size;
    idMat->rows = size;

    return idMat;

}

GMatf addM(GMatf aMat, GMatf bMat){

    /**THe number of elements in the matrices*/
    size_t nElements = 0;
    /**Iterator variable for filling the elmeents of the output matrix*/
    size_t currentElement = 0;

    /**The output matrix*/
    GMatf newMat = NULL;

    /**The pointer to the element array for the new mat*/
    GLfloat *elements = NULL;
    /**Copies of element array pointers to speed up indirection*/
    GLfloat *eAMat = NULL;
    GLfloat *eBMat = NULL;

    /**If the matrices do not have the same dimensions, we can't add them*/
    if( aMat->cols != bMat->cols
        || aMat->rows != bMat->rows){
        return NULL;
    }

    newMat = (GMatf)malloc(sizeof(struct gMatf));

    /**Allocation failed*/
    if(newMat == NULL) return NULL;

    nElements = (aMat->cols) * (aMat->rows);

    elements = (GLfloat *)malloc(sizeof(GLfloat) * nElements );

    /**Allocation failed so free the previous allocation*/
    if(elements == NULL){
        free(newMat);
        return NULL;
    }

    newMat->cols = aMat->cols;
    newMat->rows = aMat->rows;

    eAMat = aMat->e;
    eBMat = bMat->e;

    /**Loop trough the corresponding elements of both matrices, add them, and
       set the corresponding element in the output element array to that value.
       Increment the pointers after each operation*/
    for( currentElement = 0; currentElement < nElements; currentElement++){
        *elements = *eAMat + *eBMat;
        elements++;
        eAMat++;
        eBMat++;
    }
    /**Reset the value of elements so it points to the first element again*/
    elements -= nElements;

    newMat->e = elements;

}

GMatf subM(GMatf aMat, GMatf bMat){

    /**THe number of elements in the matrices*/
    size_t nElements = 0;
    /**Iterator variable for filling the elmeents of the output matrix*/
    size_t currentElement = 0;

    /**The output matrix*/
    GMatf newMat = NULL;

    /**The pointer to the element array for the new mat*/
    GLfloat *elements = NULL;
    /**Copies of element array pointers to speed up indirection*/
    GLfloat *eAMat = NULL;
    GLfloat *eBMat = NULL;

    /**If the matrices do not have the same dimensions, we can't add them*/
    if( aMat->cols != bMat->cols
        || aMat->rows != bMat->rows){
        return NULL;
    }

    newMat = (GMatf)malloc(sizeof(struct gMatf));

    /**Allocation failed*/
    if(newMat == NULL) return NULL;

    /**Set the number of elements to the product of the dimensions of
       the matrices (since they have identical dimensions, use aMat only)*/
    nElements = (aMat->cols) * (aMat->rows);

    elements = (GLfloat *)malloc(sizeof(GLfloat) * nElements );

    /**Allocation failed so free the previous allocation*/
    if(elements == NULL){
        free(newMat);
        return NULL;
    }

    newMat->cols = aMat->cols;
    newMat->rows = aMat->rows;

    eAMat = aMat->e;
    eBMat = bMat->e;

    /**Loop trough the corresponding elements of both matrices, subtract them, and
       set the corresponding element in the output element array to that value.
       Increment the pointers after each operation*/
    for( currentElement = 0; currentElement < nElements; currentElement++){
        *elements = *eAMat - *eBMat;
        elements++;
        eAMat++;
        eBMat++;
    }
    /**Reset the value of elements so it points to the first element again*/
    elements -= nElements;

    newMat->e = elements;

}

GMatf multM(GMatf aMat, GMatf bMat){

    /**THe number of elements in the matrices*/
    size_t nElements = 0;

    unsigned int nColsB = 0;
    unsigned int nRowsA = 0;
    /**Iterator variable for filling the elmeents of the output matrix*/
    size_t currentElement = 0;

    /**The number of terms to sum for each element of the output matrix*/
    unsigned int nTerms = 0;

    unsigned int currentTerm = 0;
    /**Offsets into the arrays of aMat and bMat*/
    unsigned int colBOffset = 0;
    unsigned int rowAOffset = 0;


    /**The output matrix*/
    GMatf newMat = NULL;

    /**The pointer to the element array for the new matrix*/
    GLfloat *elements = NULL;
    /**Copies of element array pointers to speed up indirection*/
    GLfloat *eAMat = NULL;
    GLfloat *eBMat = NULL;

    /**If matrix A does not have the same number of cols as matrix B has
       rows, we can't multiply them*/
    if( aMat->cols != bMat->rows){
        return NULL;
    }

    newMat = (GMatf)malloc(sizeof(struct gMatf));

    /**Allocation failed*/
    if(newMat == NULL) return NULL;

    nElements = (aMat->cols) * (bMat->rows);

    nTerms = aMat->cols;
    nColsB = bMat->cols;
    nRowsA = aMat->rows;

    elements = (GLfloat *)malloc(sizeof(GLfloat) * nElements );

    /**Allocation failed so free the previous allocation*/
    if(elements == NULL){
        free(newMat);
        return NULL;
    }

    newMat->cols = nColsB;
    newMat->rows = nRowsA;

    eAMat = aMat->e;
    eBMat = bMat->e;

    /**Loop through the elements of the output matrix and calculate the
       value of that element*/
    for( currentElement = 0; currentElement < nElements; currentElement++){

        *elements = 0;

        /**the offset into aMat's elements is the modulus of the current element
           in the output array and the number of rows in aMat*/
        rowAOffset = currentElement % nRowsA;
        /**The offset into bMat's array is the integral part of the quotient
           of the current element in the output array and the number of columns
           in bMat, all times the number of terms to sum (which is the number of
           rows in bMat*/
        colBOffset = (currentElement / nColsB) * nTerms;

        for(currentTerm = 0; currentTerm < nTerms; currentTerm++){

            *elements += (eAMat[rowAOffset + (currentTerm * nRowsA)])
                        *(eBMat[colBOffset + currentTerm]);

        }
        elements++;
    }
    /**Reset the value of elements so it points to the first element again*/
    elements -= nElements;

    newMat->e = elements;

}

GLfloat *getMatElements(GMatf self){

    return self->e;

}

gReturn deleteGMatf(GMatf *self){

    free((*self)->e);
    free(*self);
    *self = NULL;
    return G_SUCCESS;

}