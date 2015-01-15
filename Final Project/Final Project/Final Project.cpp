
// hw2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

//Real numbers to determine the materials
GLfloat material_ambient[] = {0.5f, 0.5f, 0.5f};
GLfloat material_diffuse[] = {0.10f, 0.10f, 0.10f};
GLfloat material_specular[] = {0.40f, 0.40f, 0.40f};
GLfloat material_shininess = 50.0f;

GLfloat cYellow[] = {1.0, 1.0, 0.2, 1.0};
GLfloat cPeach[] = {1.0, 0.937, 0.83};
GLfloat cGreen[] = {0.0, 1.0, 0.0, 1.0};
GLfloat cWhite[] = {1.0, 1.0, 1.0, 1.0};
GLfloat cBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat cGray[] = {0.6, 0.6, 0.6, 1.0};
GLfloat cRed[] = {1.0, 0.0, 0.0, 1.0};

//the last key pressed
unsigned lastKey = 'q';

GLuint LoadTexture(const char * filename)
{
	GLuint texture;
	int width, height;

	unsigned char *data;

	FILE *file;

	file = fopen(filename, "rb");

	if (file == NULL) return 0;
	width = 128;
	height = 128;
	data = (unsigned char *) malloc(width * height * 3);

	fread(data, width * height * 3, 1, file);
	fclose(file);

	for(int i = 0; i < width * height; i ++)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );	
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

void Init()
{
	//Init Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

	//Perspective Projection
	gluLookAt(30, -50, 60, 
              0, 0, 0, 
              -3, 5, 0);

	//Set light sources
	GLfloat lightpos0[] = {100, 100, 0, 0};
	
	GLfloat light0_position[] = {-100, 0, 0, 0};
	GLfloat light1_position[] = {100, 0, 0, 0};
	GLfloat light2_position[] = {0, 500, 0, 0};	
	GLfloat light_colors[] = {1, 1, 1, 1};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glPopMatrix();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_colors);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_colors);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_colors);
	
	//Enable depth
	glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width/(double)height, 1.0, 10000.0);
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
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGreen);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glRectf(10, 20, -10, -20);
	glPopMatrix(); 

	//Draw a floor
	const int BOUND = 1000;
	const int REPEAT = 200;
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 0, -22);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glBindTexture(GL_TEXTURE_2D, LoadTexture("floor.bmp"));
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);   
	glTexCoord2f(0.0, 0.0);
	glVertex3f(BOUND, BOUND, 0);			// Top Right Of The Quad (Top)
	glTexCoord2f(0.0, REPEAT);	
	glVertex3f(-BOUND, BOUND, 0);			// Top Left Of The Quad (Top)
	glTexCoord2f(REPEAT, REPEAT);	
	glVertex3f(-BOUND, -BOUND, 0);			// Bottom Left Of The Quad (Top)
	glTexCoord2f(REPEAT, 0.0);	
	glVertex3f(BOUND, -BOUND, 0);			// Bottom Right Of The Quad (Top)
	glEnd();					
	glPopMatrix();
	
	//Draw two cubes
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0, -10, -11);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGray);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glutSolidCube(22);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, -11);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGray);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glutSolidCube(22);
	glPopMatrix();  

	//Draw Goal
	glPushMatrix();
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glRectf(-4, -20, 4, -21);
	glPopMatrix(); 

	//Draw Goal
	glPushMatrix();
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glRectf(-4, 20, 4, 21);
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
