
#ifndef G_LOOK_CAMERA_H
#define G_LOOK_CAMERA_H
#include "./gSuite.h"
#include "./gVectMath.h"

struct gLookCamera{
    
    GVec3f location;
    GVec3f lookAt;
    GVec3f upVector;

    GLfloat nearPlane;
    GLfloat farPlane;

    GLfloat left;
    GLfloat right;

    GLfloat bottom;
    GLfloat top;

};

typedef struct gLookCamera GLookCamera;

GLookCamera *newGLookCamera(void);
GLookCamera *makeGLookCamera(GVec3f location,
                            GVec3f lookAt,
                            GVec3f upVector,
                            GLfloat nearPlane, GLfloat farPlane,
                            GLfloat left, GLfloat right,
                            GLfloat bottom, GLfloat top);

/**Returns the transformation matrix to camera space*/
GMatf getCameraTransform(GLookCamera *self);
/**Returns the perspective transform matrix*/
GMatf getCameraPerspective(GLookCamera *self);
#endif