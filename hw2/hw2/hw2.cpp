// hw2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<gl/glut.h>

GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
GLfloat material_diffuse[] = {0.90f, 0.90f, 0.90f};
GLfloat material_specular[] = {0.90f, 0.90f, 0.90f};
GLfloat material_shininess = 25.0f;
GLfloat angle;

void Init()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

	gluLookAt(0.0, 0.0, 5.0, 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(angle, 1.0f, 1.0f, 0.0f);
	glutSolidTeapot(1.05f);
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

void timer(int value)
{
	angle ++;
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
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
	glutTimerFunc(10, timer, 0);

	Init();

	glutMainLoop();

	return 0;
}
