/*
 * compileTest.c
 *
 *  Created on: Sep 26, 2010
 *      Author: Mike Oliver
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "GL/glew.h"
#include "GL/wglew.h"
//#include "GL/glxew.h"
#include "GL/freeglut.h"
#include "./obj/obj_parser.h"
#include "./gSuite/gShade.h"
//#include "./gSuite/gDiffFramework.h"
#include "./gSuite/gBuffer.h"
#include "./gSuite/gLookCamera.h"
#include "./glsw/glsw.h"
#include "./gSuite/gDeferredBuffer.h"

void display(void);

static const GLfloat vertexBufferData[] = {
    -0.5f, -0.5f, 1.0f,
     0.5f, -0.5f, 1.0f,
    -0.5f,  0.5f, 1.0f,
     0.5f,  0.5f, 1.0f,
     0.0f,  0.0f,  2.0f
};

static const GLfloat colorBufferData[] = {
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

static const GLushort elementBufferData[] = {
    0, 2, 4,
    1, 0, 4,
    3, 1, 4,
    2, 3, 4
};

GShader *basicShader = NULL;
GBuffer *vertexBuffer = NULL;
GBuffer *colorBuffer = NULL;
GBuffer *elementBuffer = NULL;
GDefBuffer *defBuffer = NULL;
GLookCamera *camera = NULL;

/**  THis functionality need sto be thrown over into gShade

    This code specifically is from Joe'S blog*/
static void show_info_log(
    GLuint object,
    PFNGLGETSHADERIVPROC glGet__iv,
    PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
)
{
    GLint log_length;
    char *log;

    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    log = (char*)malloc(sizeof(char) * log_length);
    glGet__InfoLog(object, log_length, NULL, log);
    fprintf(stderr, "%s", log);
    free(log);

    return;
}

int main(int argc, char **argv){
	/**GLUT setup boiler plate*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Photo-realistic Shaders: mark 2");

/**Glew needs to be initialized so it can tell us what
     * we have to work with; won't bother for now.*/
    GLenum glStatus = glewInit();

    if(glStatus != GLEW_OK){
        printf("Crap\n");
    }

    //###################
	//# Main glut functions
	//###################
    //glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_NORMALIZE);
    //glShadeModel(GL_SMOOTH);

	/**Display is an admittedly stupid function right now*/
	glutDisplayFunc(&display);

    /**Intitialize framebuffer for deferred shading*/

    defBuffer = makeGDefBuffer(GL_FRAMEBUFFER);

    GTexture *testTexture = newGTexture(GL_TEXTURE_2D, GL_TEXTURE0);

    //setWrapping(testTexture, 

    /**Initialize buffers*/

    vertexBuffer = makeGBuffer(GL_ARRAY_BUFFER,
                               GL_STATIC_DRAW,
                               sizeof(vertexBufferData),
                               (GDataPtr) vertexBufferData);

    printf("%d\n",sizeof(vertexBufferData));
    printf("%f\n", vertexBufferData[1]);

    addFormat(vertexBuffer, makeGBufferFormat("position",
                                            3,
                                            GL_FLOAT,
                                            GL_FALSE,
                                            0));

    colorBuffer = makeGBuffer(GL_ARRAY_BUFFER,
                             GL_STATIC_DRAW,
                             sizeof(colorBufferData),
                             (GDataPtr) colorBufferData);

    printf("%d\n",sizeof(colorBufferData));
    printf("%f\n", colorBufferData[1]);

    addFormat(colorBuffer, makeGBufferFormat("vertColor",
                                            3,
                                            GL_FLOAT,
                                            GL_FALSE,
                                            0));

    elementBuffer = makeGBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                    GL_STATIC_DRAW,
                                    sizeof(elementBufferData),
                                    (GDataPtr)elementBufferData);

    printf("%d\n",sizeof(elementBufferData));
    printf("%d\n", elementBufferData[1]);

    loadGBuffer(vertexBuffer);
    loadGBuffer(colorBuffer);
    loadGBuffer(elementBuffer);

    basicShader = makeGShader("./shaders/",
                             ".glsl",
                             "defShader.Vertex",
                             NULL,
                             "defShader.Fragment");
    compileGShader(basicShader);
    linkGShader(basicShader);

    int programOk = 1;

    glGetProgramiv(basicShader->glID, GL_LINK_STATUS, &programOk);

    if (!programOk) {
        fprintf(stderr, "Failed to link shader program:\n");
        show_info_log(basicShader->glID, glGetProgramiv, glGetProgramInfoLog);
    }

    camera = makeGLookCamera(wrapGVec3f(0.0, 0.0, 0.0),
                             wrapGVec3f(0.0, 0.0, 0.0),
                             wrapGVec3f(0.0, 0.0, 0.0),
                             0.5, 10.0,
                             -1.0, 1.0,
                             -1.0, 1.0);

    GMatf perspective = getCameraPerspective(camera);

    printf("%f ", perspective->e[0]);
    printf("%f ", perspective->e[4]);
    printf("%f ", perspective->e[8]);
    printf("%f\n", perspective->e[12]);

    printf("%f ", perspective->e[1]);
    printf("%f ", perspective->e[5]);
    printf("%f ", perspective->e[9]);
    printf("%f\n", perspective->e[13]);

    printf("%f ", perspective->e[2]);
    printf("%f ", perspective->e[6]);
    printf("%f ", perspective->e[10]);
    printf("%f\n", perspective->e[14]);

    printf("%f ", perspective->e[3]);
    printf("%f ", perspective->e[7]);
    printf("%f ", perspective->e[11]);
    printf("%f\n", perspective->e[15]);


    //start the infinite loop
	glutMainLoop();

    return 0;
}

void display(void){
    glUseProgram(basicShader->glID);
    //glClearColor(1.f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();

    bindGBuffer(vertexBuffer);
    alignAttribute(basicShader,vertexBuffer,"position");
    bindGBuffer(colorBuffer);
    alignAttribute(basicShader,colorBuffer,"vertColor");

    GMatf cameraPerspective = getCameraPerspective(camera);
    
    GLfloat *perspectiveElements = getMatElements(cameraPerspective);

    alignUniformMat(basicShader,
                    G_MAT4_V,
                    (float *) perspectiveElements,
                    1, GL_FALSE,
                    "perspective");

    bindGBuffer(elementBuffer);
    glDrawElements(
        GL_TRIANGLES,
        12,
        GL_UNSIGNED_SHORT,
        (void*)0
    );
    

    glDisableVertexAttribArray(glGetAttribLocation(basicShader->glID,"position"));

    glutSwapBuffers();

    deleteGMatf(&cameraPerspective);
    //glFlush();

}