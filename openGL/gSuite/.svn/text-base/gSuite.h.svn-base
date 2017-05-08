/*
 * gSuite.h
 *
 *  Created on: Sep 28, 2010
 *      Author (so farPlane): Mike Oliver
 *
 * This is the central header for GSuite.  All other modules include
 * it, and most depend on the constants herein defined.
 *
 * -- GSuite Return and Error system --
 *
 * Any function in GSuite that does not return an object returns an
 * integer of type:
 *
 * `typedef const unsigned int gReturn;'
 *
 * There are a number of defined gReturn values, meant to express
 * the results of a given function call.  These will be extended
 * whenever there is need for a new return status.
 *
 * For functions which do need to return an object or data, we
 * will be implementing a debug mode activated by defining
 * G_DEBUG_MODE on compilation.  Some maner of debugging log will
 * be added to the code which allows all GSuite functions to print
 * return status info before actually returning. The nature of this
 * data will be the context sensitive information that a generic
 * debugger cannot provide.  For now, this functionality is on the
 * table.
 *
 * Each gReturn value is mapped to a status message upon execution
 * of `gSuiteInit(void);'.  If you need to print out a message
 * corresponding to a given function's return status, use
 * `getGSuiteReturnStr( gReturn code);' to retrieve the massage.
 * DO NOT access the data defined in GSuite.c which maps these
 * strings directly.
 *
 * -- Enums --
 *
 * Another major type defined in this header is:
 *
 * `typedef const unsigned int gEnum;'
 *
 * gEnums provide similar functionality to GLenums.  They are used
 * as flags to be passed to functions to tell them exactly what to
 * do, often in the presence of a `(void *)' parameter.  These are
 * included, rather simply use the GLenums for this purpose, GSuite
 * has its own so GSuite:
 *
 * 1) does not infringe on the OpenGL namespace
 * 2) can define some of its own useful enums that make the API
 *    easier to use.
 *
 * Overall, these quasi-enums are here because the actual `enum'
 * construct of C really doesn't like being defined in a header
 * which is included multiple times and having its values used
 * in a case statement.  You can't make it const AND have it
 * included into multiple object files at the same time. The
 * functionality ends up the same.
 *
 * -- gBool --
 *
 * gBool is simply a typedefed integer:
 *
 * `typedef int gBool;'
 *
 * This is included as the programmer's convention and for clarity.
 * Along with it are the constants G_TRUE = 1 and G_FALSE = 0.  Again,
 * these are for clarity and convenience.  They also the make code more
 * readible.
 */

#include "GL/glew.h"
#include "GL/wglew.h"
//#include "glxew.h"
//#include "GL/wglext.h"
#include "GL/gl.h"
//#include "GL/glu.h"
#include "GL/freeglut.h"

#ifndef GSUITE_H_
#define GSUITE_H_

/** This value is set on initialization over in gSuite.c, so
 *  it is an extern */
extern int GSUITE_OK;

/**object names of 0 mean "no object" or NULL*/
const unsigned int G_NULL = 0;

/**
 * This makes it so you must cast (void *) to this type in order to
 * use any function in the API that uses a generic pointer.
 * That is, you must remind yourself that _you_ know what you're doing.*/
typedef void * GDataPtr;

typedef int gBool;

const gBool G_FALSE = 0;
const gBool G_TRUE = 1;

typedef const unsigned int gReturn;

gReturn G_SUCCESS = 0;
gReturn G_SELF_NULL = 1;
gReturn G_SELF_ID_NULL = 2;
gReturn G_OBJECT_NULL = 3;
gReturn G_ID_ZERO = 4;
gReturn G_INDEX_OUT_OF_BOUNDS = 5;
gReturn G_INDEX_NEGATIVE = 6;
gReturn G_ILLEGAL_SPECIFIER = 7;
gReturn G_ILLEGAL_OPERATION = 8;
gReturn G_ALLOCATION_FAIL = 9;


const unsigned int G_N_RETURNS = 10;


/**This "enum" is used to tell alignUniform(...) what GL function to use;
   later I'll make it smart enough to do that on its own given the source*/
typedef const unsigned int gEnum;

gEnum G_INT = 0;
gEnum G_INT2 = 1;
gEnum G_INT3 = 2;
gEnum G_INT4 = 3;
gEnum G_FLOAT = 4;
gEnum G_FLOAT2 = 5;
gEnum G_FLOAT3 = 6;
gEnum G_FLOAT4 = 7;
gEnum G_INT_V = 8;
gEnum G_INT2_V = 9;
gEnum G_INT3_V = 10;
gEnum G_INT4_V = 11;
gEnum G_FLOAT_V = 12;
gEnum G_FLOAT2_V = 13;
gEnum G_FLOAT3_V = 14;
gEnum G_FLOAT4_V = 15;
gEnum G_UINT = 16;
gEnum G_UINT2 = 17;
gEnum G_UINT3 = 18;
gEnum G_UINT4 = 19;
gEnum G_UINT_V = 20;
gEnum G_UINT2_V = 21;
gEnum G_UINT3_V = 22;
gEnum G_UINT4_V = 23;
gEnum G_MAT2_V = 24;
gEnum G_MAT3_V = 25;
gEnum G_MAT4_V = 26;
gEnum G_MAT2x3_V = 27;
gEnum G_MAT2x4_V = 28;
gEnum G_MAT3x2_V = 29;
gEnum G_MAT3x4_V = 30;
gEnum G_MAT4x2_V = 31;
gEnum G_MAT4x3_V = 32;

/**glUniformi(...) is used to align textures to GLSL samplers, so
   for API ease this is here, even though it works the same as
   G_INT*/
gEnum G_TEX_UNIT = 33;

const unsigned int G_N_TYPES = 34;

/**Initializes gSuite stuff.  Right now, this is the G_RETRUN_STR_.
 * This is done
 * in-function so we ensure proper alignment of error messages*/
int gSuiteInit(void);

const char *getGSuiteReturnStr(gReturn returnCode);


#endif /* GSUITE_H_ */
