//Carlos Ayala 
//Hector Flores
//Diego Ramirez
#include <stdio.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include "../header/Camera.h"
#include "../header/misc.h"
#include "../header/World.h"
#include "../header/Spacecraft.h"
#include "Function.h"

int mouseCoords[2], mouseMotionType = 0;
Camera sceneCam, lightCam;
Camera *draggedCamera, *currentCamera;
long frames, time_,timebase=0;
float fps = 0.0;
char bufferFPS[11];
World* worlds;
Spacecraft* spacecraft;
GLfloat*	global_ambient;
float angle;

void displayText(int x, int y, char *txt);

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{
		glColor3f(0.1, 0.1 ,0.4);
		drawSkybox(1000.0);
	}
	glPopMatrix();
	currentCamera->setView();

	spacecraft->draw();

	for(int i=0;i<9;i++){
		if(i!=9){
			worlds[i].draw();
		}
	}

	sceneCam.draw();
	displayText(5,20,bufferFPS);

	glutSwapBuffers ();
}

void idle (void)
{
	frames++;
	time_=glutGet(GLUT_ELAPSED_TIME);
	if (time_ - timebase > 1000) {
		fps = frames*1000.0f/(time_-timebase);
		sprintf(bufferFPS,"FPS:%4.2f\n",fps);
		timebase = time_;
		frames = 0;
	}

	for (int i = 0; i<9; i++) {
		worlds[i].update();
	}
	
	glutPostRedisplay();
}

void init(void)
{

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	sceneCam.setPos(82.479195f, 251.148621f, -534.879395f);
	sceneCam.setDirVec(-0.145343f, -0.328069f, 0.933399f);
	sceneCam.setPivot(0.000000, 0.000000, 0.000000);
	sceneCam.fov = 45;
	sceneCam.near_plane = 1;
	sceneCam.far_plane = 2048;
	lightCam.setPos(337.310303f, 36.482025f, -31.505600f);
	lightCam.setDirVec(-0.999485f, 0.000000f, 0.032080f);
	lightCam.setPivot(0.000000, 0.000000, 0.000000);
	lightCam.fov = 45;
	lightCam.near_plane = 1;
	lightCam.far_plane = 10000;
	currentCamera = &lightCam;

	glClearColor(0.2, 0.2, 0.2, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat diffusel0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientl0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusel0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularl0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	global_ambient = new GLfloat[4];
	global_ambient[0] = 1.0f;
	global_ambient[1] = 1.0f;
	global_ambient[2] = 1.0f;
	global_ambient[3] = 1.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	worlds = new World[10];

	glPushMatrix();
	{
		for (int i = 0; i < 10; i++) {
			worlds[i].assign(i);
		}
	}
	glPopMatrix();

	spacecraft = new Spacecraft();
	initskybox();
	
	float tmp[3];
	lightCam.getSum(tmp);
	spacecraft->updatePos(tmp);
}

void mouse( int button, int state, int x, int y)
{
	int mods;
	mouseCoords[0] = x;
	mouseCoords[1] = y;

	if(state == GLUT_DOWN){
		if(button == GLUT_LEFT_BUTTON){
			draggedCamera = &sceneCam;
		} else if(button == GLUT_RIGHT_BUTTON){
			draggedCamera = &lightCam;
		} else {
			draggedCamera = 0;
		}
		mods = glutGetModifiers();
		if(mods & GLUT_ACTIVE_SHIFT){
			mouseMotionType = 2;
		} else if(mods & GLUT_ACTIVE_ALT){
			mouseMotionType = 3;
		} else if(mods & GLUT_ACTIVE_CTRL){
			mouseMotionType = 4;
		} else {
			mouseMotionType = 1;
		}
	} else {
		if(button == GLUT_LEFT_BUTTON)
			mouseMotionType = 0;
	}
}

void motion(int x, int y)
{
	if(!draggedCamera) return;
	if(mouseMotionType == 4) {
		//Type 4: Zoom
		draggedCamera->moveForward((mouseCoords[1] - y) * 0.05); // zTrans += (mouseCoords[1] - y) * 0.02;
		draggedCamera->rotate((mouseCoords[0] - x) * 0.2, 0, 1, 0);
		mouseCoords[0] = x;
		mouseCoords[1] = y;
	} else if(mouseMotionType == 2) {
		// Type 2: Translation on X / Y
		draggedCamera->rotate((mouseCoords[1] - y) * 0.1, 1, 0, 0); // xTrans += (x - mouseCoords[0]) * 0.02;
		draggedCamera->rotate((x - mouseCoords[0]) * 0.1, 0, 0, 1); // yTrans += (mouseCoords[1] - y) * 0.02;
		mouseCoords[0] = x;
		mouseCoords[1] = y;
	} else if(mouseMotionType == 3) {
		// Type 3: Tilt
		draggedCamera->moveUp((mouseCoords[1] - y) * 0.05);   // yTrans += (y - mouseCoords[1]) * 0.02;
		draggedCamera->moveLeft((mouseCoords[0] - x) * 0.05); // xTrans += (mouseCoords[0] - x) * 0.02;

		mouseCoords[0] = x;
		mouseCoords[1] = y;
	} else if(mouseMotionType == 1) {
		// Type 1: Rotate scene
		draggedCamera->moveAround((mouseCoords[1] - y) * 0.1, 1, 0, 0);   // yTrans += (y - mouseCoords[1]) * 0.02;
		draggedCamera->moveAround((mouseCoords[0] - x) * 0.1, 0, 1, 0); // xTrans += (mouseCoords[0] - x) * 0.02;

		mouseCoords[0] = x;
		mouseCoords[1] = y;
	}
}

void keys (unsigned char key, int x, int y)
{

	float tmp[3];

	switch (key)
	{
		case 'c':
			if(currentCamera == &sceneCam)
				currentCamera = &lightCam;
			else
				currentCamera = &sceneCam;
			break;
		case 'w':
			lightCam.moveForward(10);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 's':
			lightCam.moveBackward(10);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'a':
			lightCam.moveLeft(1);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'd':
			lightCam.moveRight(1);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		//Planets
		case 'N':
			lightCam.setPos(-38.195210,-8.573028,4523.293457);
			lightCam.setDirVec(0.033034,-0.000000,-0.999454);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'U':
			lightCam.setPos(-98.420212,-8.573028,2884.414551);
			lightCam.setDirVec(0.067873,-0.000000,-0.997694);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'J':
			lightCam.setPos(-51.212345,-8.572891,1455.189941);
			lightCam.setDirVec(0.033013,0.000000,-0.999455);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'S':
			lightCam.setPos(-30.083939,-6.972890,815.540222);
			lightCam.setDirVec(0.033013,0.000000,-0.999455);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'M':
			lightCam.setPos(-11.926809,-1.172894,265.839752);
			lightCam.setDirVec(0.033013,0.000000,-0.999455);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'E':
			lightCam.setPos(-8.955643,-6.672890,175.888779);
			lightCam.setDirVec(0.033013,0.000000,-0.999455);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'V':
			lightCam.setPos(-7.304993,-6.672890,125.916016);
			lightCam.setDirVec(0.033013,0.000000,-0.999455);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
		case 'm':
			lightCam.setPos(-5.654343,-6.672890,75.943253);
			lightCam.setDirVec(0.067873,0.000000,-0.997694);
			lightCam.setPivot(0.000000,0.000000,0.000000);
			lightCam.getSum(tmp);
			spacecraft->updatePos(tmp);
			break;
	}
}

void special(int key, int x, int y) {

	float tmp[3];

	switch (key)
	{
	case GLUT_KEY_UP:
		lightCam.moveUp(1.0f);
		lightCam.getSum(tmp);
		spacecraft->updatePos(tmp);
		break;
	case GLUT_KEY_DOWN:
		lightCam.moveDown(1.0f);
		lightCam.getSum(tmp);
		spacecraft->updatePos(tmp);
		break;
	case GLUT_KEY_LEFT:
		lightCam.rotate(2, 0, 1, 0);   // yTrans += (y - mouseCoords[1]) * 0.02;
		spacecraft->update(20);
		break;
	case GLUT_KEY_RIGHT:
		lightCam.rotate(-2, 0, 1, 0);   // yTrans += (y - mouseCoords[1]) * 0.02;
		spacecraft->update(20);
		break;
	}
}

void reshape (int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w/h, 0.01f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	currentCamera->setView();
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Solar System");
	glutReshapeFunc (reshape);
	init ();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keys);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutIdleFunc (idle);
	glutMainLoop();
	killskybox();
	return 0;   /* ANSI C requires main to return int. */
}

void displayText(int x, int y, char *txt) {
	GLboolean lighting;
	GLint viewportCoords[4];
	glColor3f(1.0,0.0,0.0);
	glGetBooleanv(GL_LIGHTING, &lighting);
	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	if(lighting) glDisable( GL_LIGHTING );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0.0, viewportCoords[2], 0.0, viewportCoords[3]);
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2i( x, viewportCoords[3]-y );


	while (*txt) {glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *txt ); txt++;}
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );

	if(lighting) glEnable( GL_LIGHTING );
}
