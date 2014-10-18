#include "stdafx.h"
 
#include<gl/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void mglVertex3f(float x, float y, float z)
{
	glVertex3f(x / 10, y / 10, z / 10);
}

void renderScene(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glLoadIdentity();
 
	glBegin(GL_LINE_LOOP);

	mglVertex3f(1, 4, 0);
	mglVertex3f(4, 4, 0);
	mglVertex3f(5, 1, 0);
	mglVertex3f(6, 4, 0);
	mglVertex3f(9, 4, 0);
	mglVertex3f(6.5, 6, 0);
	mglVertex3f(7.5, 9, 0);
	mglVertex3f(5, 7, 0);
	mglVertex3f(2.5, 9, 0);
	mglVertex3f(3.5, 6, 0);

	glEnd();
	glutSwapBuffers();

}

void keyPressed (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

int _tmain(int argc, _TCHAR* argv[]) 
{
 
	glutInit(&argc, (char**) argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 
	glutInitWindowPosition(100,100);
 
	glutInitWindowSize(320,320);
 
	glutCreateWindow("Hello OpenGL");

	glutKeyboardFunc(keyPressed);
 
	glutDisplayFunc(renderScene);
 
	glutMainLoop();
 
	return 0;
}
