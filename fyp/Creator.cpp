#include "Header Files\Creator.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\matrix\src\Matrices.h"
#include "Dependencies\matrix\src\Vectors.h"
#include "Header Files\Builder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Poor man's approximation of PI
#define PI 3.1415926535898
// Degrees to radians
#define DTOR (PI / 180.0f)

using namespace std;

// WINDOW PROPERTIES
double dim = 1.0; // dimension of orthogonal box
char windowName[] = "Clouds";
int windowWidth = 1200;
int windowHeight = 600;

// Variables to move the display around
float xPlus = 0.0;
float yPlus = 0.0;
float zPlus = -2.0;

//  Various global state
int lr = 0;   // azimuth of view angle
int ud = 0; // elevation of view angle
int fov = 55; // field of view for perspective
int asp = 2;  // aspect ratio

int numMetas;
float density;
float timelight;
Vector3* Ccentres;
float* radii;
bool skyLight;


Creator::Creator(Vector3 centresMain[], int numMetasN, float radiiN[], float timeIn, float densityN, bool skyLightN) {
	Ccentres = centresMain;
	numMetas = numMetasN;
	radii = radiiN;
	timelight = timeIn;
	density = densityN;
	skyLight = skyLightN;
}

void run();

void Creator::work() {
	run();
}

void project() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// perspective
	gluPerspective(fov, asp, dim / 4, 14 * dim);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void reshape(int width, int height) {
	asp = (height>0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project();
}
void keyPress(unsigned char key, int x, int y) {
	// Exit on ESC 
	if (key == 27) exit(0);
	project();
	glutPostRedisplay();
}
void windowMenu(int value) {
	keyPress((unsigned char)value, 0, 0);
}

void display() {
	//  Clear the image
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);

	// Reset previous transforms
	glLoadIdentity();

	// POSITIONING
	// Coordinates
	glTranslatef(xPlus, yPlus, zPlus);
	// Rotation
	glRotatef(240, 1.0, 0.0, 0.0);

	Vector3 observer = { 0.0f, (float)sin(DTOR * 240), (float)cos(DTOR * 240) };
	Builder build = Builder(Ccentres, numMetas, radii, timelight, observer, density, skyLight);

	//  Flush and swap
	glFlush();
	glutSwapBuffers();
}

void run() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(windowName);
	//glutFullScreen();

	glutPostRedisplay();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPress);
	glutPostRedisplay();
	glutPostRedisplay();

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Mode [m]", 'm');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

Creator::~Creator()
{
}
