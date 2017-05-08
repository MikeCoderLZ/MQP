/*
 * vecMath.h
 *
 * Defines API for vector math that we may need to do outside of OpenGL,
 * mainly within World Control.
 *
 * Don't attempt to compile this until it is completely implemented.
 *
 *  Created on: Sep 28, 2010
 *      Author: Mike Oliver
 */

#ifndef VECMATH_H_
#define VECMATH_H_

#include "GL/glew.h"
#include "GL/wglew.h"
//#include "glxew.h"
//#include "GL/wglext.h"
#include "GL/gl.h"
//#include "GL/glu.h"
#include "GL/freeglut.h"

#include "./gSuite.h"

#include <math.h>

/** -----CONSTANTS----- */

const float G_PI = 3.1415926535897932384626433832795f;
const float G_PI2 = G_PI / 2.0;
const float G_PI4 = G_PI / 4.0;
const float G_PI8 = G_PI / 8.0;

const float G_PI_INV = (1.0/G_PI);
const float G_PI2_INV = 1.0/(2.0*G_PI);
const float G_PI4_INV = 1.0/(4.0*G_PI);
const float G_PI8_INV = 1.0/(8.0*G_PI);

const float G_PHI = 1.6180339887498948482045868343656f;
const float G_PH2 = G_PHI / 2.0;
const float G_PH4 = G_PHI / 4.0;
const float G_PH8 = G_PHI / 8.0;

const float G_PHI_INV = 1.0/G_PHI;
const float G_PHI2_INV = 1.0/(2.0*G_PHI) ;
const float G_PHI4_INV = 1.0/(4.0*G_PHI);
const float G_PHI8_INV = 1.0/(8.0*G_PHI);

const float G_E = 2.7182818284590452353602874713526f;
const float G_E2 = (G_E / 2.0);
const float G_E4 = (G_E / 4.0);
const float G_E8 = (G_E / 8.0);

const float G_E_INV = (1.0/G_E);
const float G_E2_INV = (1.0/(2.0*G_E)) ;
const float G_E4_INV = (1.0/(4.0*G_E));
const float G_E8_INV = (1.0/(8.0*G_E));

const float G_IN_RADS = 1.0f;
const float G_IN_DERGEES = G_PI / 180.0;
const float G_IN_GRADIANS = G_PI / 200.0;


/** -----VECTORS----- **/

/**
 * All vectors are stored in <x,y,z,w> order, that is, element 0
 * is x, element 1 is y.
 *
 * For speed, these are implemented with typedefs.  THIS CAN BE VERY DANGEROUS.
 * For example:
 *
 * typedef GLFloat* GVec3f;
 * static inline GVec3f *newGVec3f();
 *
 * A GVec3f is an array of 3 GLfloats, but there is no struct wrapper, and the
 * code assumes you have allocated a 3 element array properly with newGVec3f(),
 * which is actually an inline that expands to a malloc(sizeof(GLfloat) * 3).
 *
 * Again, be CAREFUL here; in the interests of the fewest pointer expansions
 * and function calls on these objects which need to be as fast as possible,
 * we opted for a system that is dangerous int he wrong hands.
 *
 * You have been warned.
 *
 * */

typedef GLfloat * GVec2f;
typedef GLfloat * GVec3f;
typedef GLfloat * GVec4f;

GVec2f newGVec2f(void);
GVec2f newGVec3f(void);
GVec2f newGVec4f(void);

GVec2f wrapGVec2f( GLfloat x, GLfloat y );
GVec3f wrapGVec3f( GLfloat x, GLfloat y, GLfloat z );
GVec4f wrapGVec4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );

gReturn delGVec2f(GVec2f *self);
gReturn delGVec3f(GVec3f *self);
gReturn delGVec4f(GVec4f *self);

/**More rope to hang yourself with; these functions assume you passed a pointer
 * to an allocated array that has that element.  Illegal access violation WILL
 * happen if you pass a GVec2f to getW().
 *
 * The get<S,T,P,Q>() functions are the same as the corresponding
 * <X,Y,Z,W> set, only they are for texture coordinates (OpenGL uses
 * S,T,R,Q for texture coordinates).
 */

static inline GLfloat get2X(GVec2f self);
static inline GLfloat get3X(GVec3f self);
static inline GLfloat get4X(GVec4f self);
static inline GLfloat get2Y(GVec2f self);
static inline GLfloat get3Y(GVec3f self);
static inline GLfloat get4Y(GVec4f self);
static inline GLfloat get3Z(GVec3f self);
static inline GLfloat get4Z(GVec4f self);
static inline GLfloat getW(GVec4f self);

static inline GLfloat get2S(GVec2f self);
static inline GLfloat get3S(GVec3f self);
static inline GLfloat get4S(GVec4f self);
static inline GLfloat get2T(GVec2f self);
static inline GLfloat get3T(GVec3f self);
static inline GLfloat get4T(GVec4f self);
static inline GLfloat get3P(GVec3f self);
static inline GLfloat get4P(GVec4f self);
static inline GLfloat getQ(GVec4f self);

static inline GLfloat get2R(GVec2f self);
static inline GLfloat get3R(GVec3f self);
static inline GLfloat get4R(GVec4f self);
static inline GLfloat get2G(GVec2f self);
static inline GLfloat get3G(GVec3f self);
static inline GLfloat get4G(GVec4f self);
static inline GLfloat get3B(GVec3f self);
static inline GLfloat get4B(GVec4f self);
static inline GLfloat getA(GVec4f self);

static inline gReturn set2X(GVec2f self, GLfloat xCoord);
static inline gReturn set3X(GVec3f self, GLfloat xCoord);
static inline gReturn set4X(GVec4f self, GLfloat xCoord);
static inline gReturn set2Y(GVec2f self, GLfloat yCoord);
static inline gReturn set3Y(GVec3f self, GLfloat yCoord);
static inline gReturn set4Y(GVec4f self, GLfloat yCoord);
static inline gReturn set3Z(GVec3f self, GLfloat zCoord);
static inline gReturn set4Z(GVec4f self, GLfloat zCoord);
static inline gReturn setW(GVec4f self, GLfloat wCoord);

static inline gReturn set2S(GVec2f self, GLfloat sCoord);
static inline gReturn set3S(GVec3f self, GLfloat sCoord);
static inline gReturn set4S(GVec4f self, GLfloat sCoord);
static inline gReturn set2T(GVec2f self, GLfloat tCoord);
static inline gReturn set3T(GVec3f self, GLfloat tCoord);
static inline gReturn set4T(GVec4f self, GLfloat tCoord);
static inline gReturn set3P(GVec3f self, GLfloat pCoord);
static inline gReturn set4P(GVec4f self, GLfloat pCoord);
static inline gReturn setQ(GVec4f self, GLfloat qCoord);

static inline gReturn set2R(GVec2f self, GLfloat red);
static inline gReturn set3R(GVec3f self, GLfloat red);
static inline gReturn set4R(GVec4f self, GLfloat red);
static inline gReturn set2G(GVec2f self, GLfloat green);
static inline gReturn set3G(GVec3f self, GLfloat green);
static inline gReturn set4G(GVec4f self, GLfloat green);
static inline gReturn set3B(GVec3f self, GLfloat blue);
static inline gReturn set4B(GVec4f self, GLfloat blue);
static inline gReturn setA(GVec4f self, GLfloat alpha);


static inline GVec3f sub3(GVec3f aVec, GVec3f bVec);

/**
 * These are all inlines because inline functions may be faster for
 * this sort of thing.  static inline tells MinGW that it may make the
 * determination whether or not to substitute the function into the code.
 * The definitions are over in vecMath.c, so I hope that that works.
 */

static inline GVec2f norm2(GVec2f aVec);
static inline GVec3f norm3(GVec2f aVec);
static inline GVec4f norm4(GVec2f aVec);

static inline gReturn normIP2(GVec2f aVec);
static inline gReturn normIP3(GVec2f aVec);
static inline gReturn normIP4(GVec2f aVec);

static inline GLfloat dot33f(GVec3f aVec, GVec3f bVec);

static inline GVec3f cross3f(GVec3f aVec, GVec3f bVec);

/**
 * OpenGL matrices are laid out as a sixteen element array, which
 * wraps likes this:
 *
 * +--+--+--+--+
 * | 0| 4| 8|12|
 * +--+--+--+--+
 * | 1| 5| 9|13|
 * +--+--+--+--+
 * | 2| 6|10|14|
 * +--+--+--+--+
 * | 3| 7|11|15|
 * +--+--+--+--+
 *
 * For programmatic consistency, we'll do the same.  Unfortunately,
 * common mathematical notation implies the transpose of this
 * packing scheme.  For that reason, parameter names always
 * specify rows or columns.
 * 
 */

struct gMatf{
    GLfloat* e;
    unsigned int cols;
    unsigned int rows;
};
typedef struct gMatf* GMatf;

GMatf newGMatf(void);

/**We suggest you layout your calls like this, too, since the values
 * map to the matrix exactly as shown.*/

GMatf makeGMat44f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r, GLfloat e3c2r,
                   GLfloat e0c3r, GLfloat e1c3r, GLfloat e2c3r, GLfloat e3c3r);
GMatf makeRowGMat44f( GVec4f row0,
                      GVec4f row1,
                      GVec4f row2,
                      GVec4f row3);
GMatf makeColGMat44f( GVec4f col0,
                      GVec4f col1,
                      GVec4f col2,
                      GVec4f col3);

GMatf makeGMat43f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r, GLfloat e3c2r);
GMatf makeRowGMat43f( GVec4f row0,
                      GVec4f row1,
                      GVec4f row2);
GMatf makeColGMat43f( GVec3f col0,
                      GVec3f col1,
                      GVec3f col2);

GMatf makeGMat42f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r, GLfloat e3c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r, GLfloat e3c1r);
GMatf makeRowGMat42f( GVec4f row0,
                      GVec4f row1);
GMatf makeColGMat42f( GVec2f col0,
                      GVec2f col1,
                      GVec2f col2,
                      GVec2f col3);

GMatf makeGMat34f(GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r,
                   GLfloat e0c3r, GLfloat e1c3r, GLfloat e2c3r);
GMatf makeRowGMat34f( GVec3f row0,
                      GVec3f row1,
                      GVec3f row2,
                      GVec3f row3);
GMatf makeColGMat34f( GVec4f col0,
                      GVec4f col1,
                      GVec4f col2);

GMatf makeGMat33f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r);
GMatf makeRowGMat33f( GVec3f row0,
                      GVec3f row1,
                      GVec3f row2);
GMatf makeColGMat33f( GVec3f row0,
                      GVec3f row1,
                      GVec3f row2);

GMatf makeGMat32f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r);
GMatf makeRowGMat32f( GVec3f row0,
                      GVec3f row1);
GMatf makeColGMat32f( GVec2f col0,
                      GVec2f col1,
                      GVec2f col2);

GMatf makeGMat24f( GLfloat e0c0r, GLfloat e1c0r,
                   GLfloat e0c1r, GLfloat e1c1r,
                   GLfloat e0c2r, GLfloat e1c2r,
                   GLfloat e0c3r, GLfloat e1c3r);
GMatf makeRowGMat24f( GVec2f row0,
                      GVec2f row1,
                      GVec2f row2,
                      GVec2f row3);
GMatf makeColGMat24f( GVec4f col0,
                      GVec4f col1);

GMatf makeGMat23f( GLfloat e0c0r, GLfloat e1c0r, GLfloat e2c0r,
                   GLfloat e0c1r, GLfloat e1c1r, GLfloat e2c1r,
                   GLfloat e0c2r, GLfloat e1c2r, GLfloat e2c2r);
GMatf makeRowGMat23f( GVec2f row0,
                      GVec2f row1,
                      GVec2f row2);
GMatf makeColGMat23f( GVec3f col0,
                      GVec3f col1);

GMatf makeGMat22f( GLfloat e0c0r, GLfloat e1c0r,
                   GLfloat e0c1r, GLfloat e1c1r);
GMatf makeRowGMat22f( GVec2f row0,
                      GVec2f row1);
GMatf makeColGMat22f( GVec2f col0,
                      GVec2f col1);

GMatf makeGMatf( GLfloat *elements,
                 unsigned int rows,
                 unsigned int cols);

GLfloat *getMatElements(GMatf self);
/**
GMatf wrapRowGMatf( GVector *rowElements,
                     unsigned int rows,
                     unsigned int cols);
GMatf wrapColGMatf( GVector *colElements,
                     unsigned int rows,
                     unsigned int cols);
                     */

GMatf getIdentity( unsigned int size);

GMatf addM(GMatf aMat, GMatf bMat);
GMatf subM(GMatf aMat, GMatf bMat);

GMatf multM(GMatf aMat, GMatf bMat);
/**Not implementing this right now; it is of limited use anyway*/
//GMatf divM(GMatf aMat, GMatf bMat);

gReturn deleteGMatf(GMatf *self);

#endif /* VECMATH_H_ */
