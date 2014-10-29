// hw2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<gl/glut.h>

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

//Real numbers denoting the angles OR relative size of each object
GLfloat animation[10] = {0, 0, 0.5, 0, 0, 0};

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
	gluLookAt(0.0, 0.0, 5.0, 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0);

	//Set light sources
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Enable depth
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//First, a tea pot, rotate
	glPushMatrix();
	glTranslatef(-4, 2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);
	glRotatef(animation[0], 1.0f, 1.0f, 0.0f);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//Second, a cube, rotate
	glPushMatrix();
	glTranslatef(0, 2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGreen);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glRotatef(animation[1], 0.0f, 1.0f, 0.5f);
	glutSolidCube(1.5);
	glPopMatrix();
	
	//Third, a sphere, scale
	glPushMatrix();
	glTranslatef(4, 2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cBlue);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glutSolidSphere(animation[2], 50, 50);
	glPopMatrix();

	//Fourth, a cone, rotating
	glPushMatrix();
	glTranslatef(-4, -2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cYellow);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glRotatef(animation[3], -0.1f, -0.9f, 0.2f);
	glutSolidCone(0.8, 1.9, 50, 50);
	glPopMatrix();

	//Fourth, a cone, rotating
	glPushMatrix();
	glTranslatef(-4, -2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cYellow);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glRotatef(animation[3], -0.1f, -0.9f, 0.2f);
	glutSolidCone(0.8, 1.9, 50, 50);
	glPopMatrix();


	//Fifth, a torus, scale
	glPushMatrix();
	glTranslatef(0, -2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glRotatef(animation[4], 1, -1, 1);
	glutSolidTorus(0.65, 0.8, 50, 50);
	glPopMatrix();

	//Sixth, an Octahedron, rotate
	glPushMatrix();
	glTranslatef(4, -2, -7.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cPeach);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	glRotatef(animation[5], 0.8, 0.2, 0.6);
	glutSolidOctahedron();
	glPopMatrix();


	glutSwapBuffers();
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

}

void timer()
{
	animation[0] ++;
	animation[1] ++;
	animation[3] ++;
	animation[4] ++;
	animation[5] ++;
	glutPostRedisplay();
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**) argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Primitive Transformation");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutIdleFunc(timer);

	Init();

	glutMainLoop();

	return 0;
}
