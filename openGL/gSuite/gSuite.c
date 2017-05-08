#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./gSuite.h"
#include "../glsw/glsw.h"
//#include "gSuite/gVectMath.h"

/**object names of 0 mean "no object" or NULL*/
int GSUITE_OK = -1;


/**Array of strings to translate gReturn values into error messages*/
const char** gReturnStrings;

char *gSuccess = "G_SUCCESS: No known errors.\n";
char *gSelfNull = "G_SELF_NULL: 'self' pointer of gSuite object was NULL; illegal access was not attempted by function.  Check calling function.\n";
char *gSelfIDNull = "G_SELF_ID_NULL: OpenGL object name ID of gSuite object 'self' was equal to G_NULL = 0; requested OpenGL object does not exist.  Check initializers.\n";
char *gObjectNull = "G_OBJECT_NULL: Object accessed from self or other object had zero pointer; check calling function.\n";
char *gIDZero = "G_ID_ZERO: OpenGL name ID passed or accessed from gSuite object was 0 in a illegal context; check intializers and error logs.\n";
char *gIndexOutOfBounds = "G_INDEX_OUT_OF_BOUNDS: Element index asked for is larger than the size of the array or list queried; check loops and function calls.\n";
char *gIndexNegative = "G_INDEX_NEGATIVE: Passed array element index was negative.  Arrays cannot have negative indices; this is not Python.  Check loops and calling function.\n";
char *gIllegalSpecifier = "G_ILLEGAL_SPECIFIER: A gSuite enumerated type was used in an illegal or inappropriate context; check calling function or check which fucntion you used.\n";
char *gAllocationFail = "G_ALLOCATION_FAIL: allocation of an internal data structure failed.";


int gSuiteInit(){

    gReturnStrings = (const char **)malloc( sizeof(char *) * G_N_RETURNS );

    gReturnStrings[G_SUCCESS] = gSuccess;
    gReturnStrings[G_SELF_NULL] = gSelfNull;
    gReturnStrings[G_SELF_ID_NULL] = gSelfIDNull;
    gReturnStrings[G_OBJECT_NULL] = gObjectNull;
    gReturnStrings[G_ID_ZERO] = gIDZero;
    gReturnStrings[G_INDEX_OUT_OF_BOUNDS] = gIndexOutOfBounds;
    gReturnStrings[G_INDEX_NEGATIVE] = gIndexNegative;
    gReturnStrings[G_ILLEGAL_SPECIFIER] = gIllegalSpecifier;
    gReturnStrings[G_ALLOCATION_FAIL] = gAllocationFail;


    GSUITE_OK = 0;

    return G_SUCCESS;

}

const char *getGSuiteReturnStr(gReturn returnCode){

    return gReturnStrings[returnCode];

}
