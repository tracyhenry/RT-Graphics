
// hw2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

//Real numbers to determine the materials
GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
GLfloat material_diffuse[] = {0.10f, 0.10f, 0.10f};
GLfloat material_specular[] = {0.40f, 0.40f, 0.40f};
GLfloat material_shininess = 25.0f;

GLfloat cYellow[] = {1.0, 1.0, 0.2, 1.0};
GLfloat cPeach[] = {1.0, 0.937, 0.83};
GLfloat cGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
GLfloat cWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
GLfloat cBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat cRed[] = {1.0, 0.0, 0.0, 1.0};


//the last key pressed
unsigned lastKey = 'q';

void Init()
{
	//Init Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

	//Perspective Projection
	gluLookAt(0.0, -50.0, 50.0, 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0);

	//Set light sources
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Enable depth
	glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width/(double)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed (unsigned char key, int x, int y)
{
	if (key == 27) 
		exit(0);
	lastKey = key;
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw a rectangle
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGreen);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);
	glRectf(10.0f, 20.0f, -10.0f, -20.0f);	
	glPopMatrix();

	glutSwapBuffers();
}


int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**) argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("实时图形大作业 - 陶文博 2011011244");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyPressed);
//	glutTimerFunc(10, timer, 0);

	Init();

	glutMainLoop();

	return 0;
}
