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
#include "./gSuite/gDiffFramework.h"
#include "./gSuite/gBuffer.h"
#include "./gSuite/gLookCamera.h"
#include "./glsw/glsw.h"


//Temp Camera and mouse global variables.
char keyModifiers;
float fXRot = 15;
float fYRot = 32;
float fZRot = 0;
int xLast = -1;
int yLast = -1;
int xIncr = 0;
int yIncr = 0;
float fScale = 0.78;

GShader* normShade;

int dumbRender(GRenderCfg*, void*);
int dumbPaint(GLayerCfg*, void*);
void display();
void drawModel();

void mouse(int, int, int, int);//captures mouse clicks
void movement(int,int);//captures mouse movement on screen
void reshape(int, int);
void idle(void);
void drawgimbal(void);

obj_scene_data* model;
GRenderCfg* mainRenderer;

int main( int argc, char** argv){


	//const GLchar* vShader = "./shaders/smoothshade.vert";
    
    model = (obj_scene_data*) malloc(sizeof(obj_scene_data));
	char modelName[] = "./leaf.obj";
	parse_obj_scene(model, modelName);
	printf(strerror(errno));

	/**GLUT setup boiler plate*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Photo-realistic Shaders: mark 1");

/**Glew needs to be initialized so it can tell us what
     * we have to work with; won't bother for now.*/
    GLenum glStatus = glewInit();

    if(glStatus != GLEW_OK){
        printf("Crap\n");
    }

    mainRenderer = newGRenderCfg(1);

    GLfloat testFloats[] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

	GBuffer* aBuff = makeGBuffer(
        GL_ARRAY_BUFFER,
        GL_DYNAMIC_DRAW,
        6,
        testFloats
    );

    GBufferFormat *newFormat = makeGBufferFormat(
                                    "test",
                                    1,
                                    GL_FLOAT,
                                    GL_FALSE,
                                    0
                                );

    addFormat(aBuff, newFormat);

    //printf("%d\n", ((GBufferFormat *)retrieve(aBuff->formats))->size);
//    glswSetPath("./shaders/", ".glsl");
    
    GShader* shadeProgram = makeGShader ("./shaders/",
                                          ".glsl",
                                          "uniformtest.Vertex",
                                          NULL,
                                          "uniformtest.Fragment");

    normShade = makeGShader ("./shaders/",
                                          ".glsl",
                                          "normalShade.Vertex",
                                          NULL,
                                          "normalShade.Fragment");
    //printf(shadeProgram->includeSrc);
    //printf(shadeProgram->vShaderSrc);
    //printf(shadeProgram->fShaderSrc);

    compileGShader(shadeProgram);
    linkGShader(shadeProgram);
    compileGShader(normShade);
    linkGShader(normShade);

	GLayerCfg* aLayer = wrapGLayerCfg(&dumbPaint, aBuff, shadeProgram);
    setBufferN(mainRenderer, 1, aLayer);
    mainRenderer->render = &dumbRender;

	//###################
	//# Main glut functions
	//###################
    glClearColor(0.f, 0.1f, 0.2f, 1.f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

	/**Display is an admittedly stupid function right now*/
	glutDisplayFunc(&display);
    glutReshapeFunc(reshape);
    glutMotionFunc(movement);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);

    //start the infinite loop
	glutMainLoop();

	delete_obj_data(model);
    deleteGLayerCfg(mainRenderer->bufferCfgs);
    deleteGRenderCfg(&mainRenderer);
    glswShutdown();
	return 0;
}

int dumbPaint(GLayerCfg* aBuffer, void* nothing){

    glUseProgram(aBuffer->shadeProgram->glID);
    
        /** The big test of the uniform allignment */
    GLfloat* testColor = (GLfloat*)malloc(sizeof(GLfloat) * 3);
    
    testColor[0] = 1.0f;
    testColor[1] = 0.5f;
    testColor[2] = 1.0f;

    alignUniform(aBuffer->shadeProgram, G_FLOAT3, testColor, "DiffuseColor");

    GLfloat* testLight = (GLfloat*)malloc(sizeof(GLfloat) * 3);
    
    testLight[0] = 2.0f;
    testLight[1] = 4.f;
    testLight[2] = 2.0f;

    alignUniform(aBuffer->shadeProgram, G_FLOAT3, testLight, "worldLightPosition");


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//////////////////////////////
	//Display Matrix Calculations
	
    glLoadIdentity();
/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double winHt = 1.0; // half-height of world window
	int WIDTH=500;
	int HEIGHT = WIDTH;

	gluPerspective(80,1,.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt( .5*fScale, 2*fScale, .5*fScale,   .1, 1, .1,    0.0, 1.0, 0.0 );
    //*/
    glPushMatrix();
    //glTranslatef(0.0, -1.0, 0.0);

	glRotatef(fYRot, 1,0,0);
    glRotatef(fXRot, 0,1,0);
    glRotatef(fZRot, 0,0,1);
    glScalef(fScale, fScale, fScale);
    
    //glutSolidSphere(0.5, 8, 4);
    
    drawModel();

    glUseProgram(aBuffer->shadeProgram->glID);
    glPushMatrix();
    glTranslatef(-2,0,1.);
    glutSolidSphere(.7,32,16);
    glTranslatef(4,0,0);
    glutSolidSphere(.7,32,16);
    glTranslatef(-2,0,-2.5);
    glutSolidSphere(.7,32,16);

    glPopMatrix();

    glUseProgram(normShade->glID);
    glScalef(.5, .5, .5);
    drawgimbal();

    glPopMatrix();

    glFlush();
    return 0;
    
    //double* cameraPos = model->vertex_list[model->camera->camera_pos_index]->e;
    //  glTranslatef(cameraPos[2], cameraPos[0], cameraPos[1]);
}

int dumbRender(GRenderCfg* self, void* nothing){

    self->bufferCfgs[0]->paint(self->bufferCfgs[0], NULL);
    return 0;

}

void idle(void){
    glutPostRedisplay();
    //glutSetWindowTitle("");
}

void display(void){

    dumbRender(mainRenderer, NULL);
    return;

}

//*  
void reshape(int W, int H){
    float vp = 1.0f;
    float aspect = (float) W / (float) H;
    
    glViewport(0, 0, W, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80,aspect,.1,100);
	gluLookAt( 0, 0.7, 2.1,   0.0, -0.9, 0.1,    0.0, 1.0, 0.0 );
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    /*
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, W, H);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-vp, vp, -vp / aspect, vp / aspect, 3, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);*/
}//*/

/////////////////
void mouse(int button, int state, int x, int y){
    keyModifiers = glutGetModifiers();

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xLast = -1;
        yLast = -1;
        printf("\nX = %f",fXRot);
        printf(" Y = %f",fYRot);
        printf(" Z = %f",fZRot);
        printf(" S = %f\n",fScale);
    }

}

void movement(int x, int y){
    if ((xLast != -1) || (yLast != -1))
    {
        xIncr = x - xLast;
        yIncr = y - yLast;
        if (keyModifiers & GLUT_ACTIVE_CTRL)
        {
            if (xLast != -1)
            {
                fZRot += xIncr;
                fScale += (yIncr)* 0.005f;
            }
        }
        else
        {
            if (xLast != -1)
            {
                fXRot += xIncr;
                fYRot += yIncr;
            }
        }
    }

    xLast = x;
    yLast = y;
}

void drawModel(){

    obj_face** faces = model->face_list;

	int thisFace = 0;
	GLfloat x,y,z,nx,ny,nz;
    int ix=0, iz=2;//temp for switching x/z

    //Works for both triangulated and regular models
    int v=model->face_list[0]->vertex_count;
    switch(v){
    case 3:
        glBegin(GL_TRIANGLES);
        break;
    case 4:
        glBegin(GL_QUADS);
        break;
    default:
        break;

    }

	for(thisFace = 0; thisFace < model->face_count; thisFace++){
		for(int i=0;i<v;i++){
	        x = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[ix];
	        y = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[1];
	        z = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[iz];

	        nx = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[ix];
	        ny = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[1];
	        nz = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[iz];
            
	        glVertex3f(x,y,z);
            glNormal3f(nx,ny,nz);
            
	    }
        
	}
	glEnd();

    glUseProgram(normShade->glID);

    //print vertex normals
	for(thisFace = 0; thisFace < model->face_count; thisFace++){
		for(int i=0;i<3;i++){
            
	        x = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[ix];
	        y = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[1];
	        z = model->vertex_list[faces[thisFace]->vertex_index[i]]->e[2];

	        nx = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[ix];
	        ny = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[1];
	        nz = model->vertex_normal_list[faces[thisFace]->normal_index[i]]->e[iz];

            glBegin(GL_LINES);
                glVertex3f(x, y, z);
                glVertex3f(x+nx/4, y+ny/4, z+nz/4);
            glEnd();
	    }
	}
	

	return;

}



//draw an xyz gimbal
void drawgimbal(){
    
    //draw y axis: sphere
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0,1,0);
    //glScalef(.1,.1,.1);
    glutSolidSphere(0.1, 8, 4);
    glPopMatrix();

    //draw x axis: cube
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(1,0,0);
    //glScalef(.1,.1,.1);
    glutSolidCube(0.15);
    glPopMatrix();

    //draw z axis: cone
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0,0,1);
    //glScalef(.1,.1,.1);
    glutSolidCone(.1,.3,4,1);
    glPopMatrix();




}