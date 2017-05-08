#include "./gLookCamera.h"

GLookCamera *newGLookCamera(void){

    GLookCamera *newCamera = (GLookCamera *)malloc(sizeof(GLookCamera));

    if(newCamera == NULL) return NULL;

    GLfloat *location = (GLfloat *)malloc(sizeof(GLfloat) * 3);

    if(location == NULL){
        free(newCamera);
        return NULL;
    }

    GLfloat *lookAt = (GLfloat *)malloc(sizeof(GLfloat) * 3);

    if(lookAt == NULL){
        free(newCamera);
        free(location);
        return NULL;
    }

    GLfloat *upVector = (GLfloat *)malloc(sizeof(GLfloat) * 3);

    if(upVector == NULL){
        free(newCamera);
        free(location);
        free(lookAt);
        return NULL;
    }

    location[0] = 0;
    location[1] = 0;
    location[2] = 0;

    lookAt[0] = 0;
    lookAt[1] = 0;
    lookAt[2] = 1.0;

    upVector[0] = 0;
    upVector[1] = 1.0;
    upVector[2] = 0;

    newCamera->location = (GVec3f) location;
    newCamera->lookAt = (GVec3f) lookAt;
    newCamera->upVector = (GVec3f) upVector;
    newCamera->nearPlane = 0.01f;
    newCamera->farPlane = 10.0f;
    newCamera->left = -1.0f;
    newCamera->right = 1.0f;
    newCamera->bottom = -1.0f;
    newCamera->top = 1.0f;


    return newCamera;

}

GLookCamera *makeGLookCamera(GVec3f location,
                            GVec3f lookAt,
                            GVec3f upVector,
                            GLfloat nearPlane, GLfloat farPlane,
                            GLfloat left, GLfloat right,
                            GLfloat bottom, GLfloat top){

    GLookCamera *newCamera = (GLookCamera *)malloc(sizeof(GLookCamera));

    if(newCamera == NULL) return NULL;

    newCamera->location = location;
    newCamera->lookAt   = lookAt;
    newCamera->upVector = upVector;
    newCamera->nearPlane = nearPlane;
    newCamera->farPlane = farPlane;

    newCamera->left = left;
    newCamera->right = right;

    newCamera->bottom = bottom;
    newCamera->top = top;


    return newCamera;

}

GMatf getCameraTransform(GLookCamera *self){

    /**The translations vector is the negative of the camera's position*/
    /**GVec3f translation = wrapGVec3f( -((GLfloat*)self->location)[0],
                                     -((GLfloat*)self->location)[1],
                                     -((GLfloat*)self->location)[2]);*/

    /**This part I am a little stuck on, so we are gonna fudge it for now*/
    /**

    GVec3f lookVector = normIP3(sub3f(self->lookAt, self->location));

    static const GVec3f defaultLook = wrapGVec3f( 0.0f, 0.0f, 1.0f);

    GVec3f lookRotAxis = cross3f(lookVector, defaultLook);

    GLfloat lookRotDot = dot33f(lookVector, defaultLook);

    */

    /**An identity matrix*/

   return getIdentity(4);
}

GMatf getCameraPerspective(GLookCamera *self){
    /**A simple perspective projection/translation matrix*/
    GLfloat twoNear = 2 * self->nearPlane;

    GLfloat rMinusL = self->right - self->left;
    GLfloat tMinusB = self->top - self->bottom;
    GLfloat fMinusN = self->farPlane - self->nearPlane;

    GLfloat rPlusL = self->right + self->left;
    GLfloat tPlusB = self->top + self->bottom;
    GLfloat fPlusN = self->farPlane + self->nearPlane;

    return makeGMat44f(twoNear/rMinusL, 0.0, rPlusL/rMinusL, 0.0,
                       0.0, twoNear/tMinusB, tPlusB/tMinusB, 0.0,
                       0.0, 0.0, fPlusN/fMinusN, -(twoNear*(self->farPlane))/fMinusN,
                       0.0, 0.0, 1.0, 0.0);
    /**return getIdentity(4);*/
}