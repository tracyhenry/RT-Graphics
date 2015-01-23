#include "stdafx.h"
#include <Windows.h>
#include <gl/glut.h>
#include <iostream>
#include <ctime>
using namespace std;


class Camera 
{
	double theta, dTheta, pi;

public:
	Camera(): theta(270), dTheta(2), pi(3.14159265354) {}
	double getX() 
	{
		return 50 * cos(theta / 180 * pi);
	}
	
	double getY() 
	{
		return 50 * sin(theta / 180 * pi);
	}

	double getZ() 
	{
		return 60;
	}
	
	void moveLeft() 
	{
		theta += dTheta;
		if (theta >= 360)
			theta -= 360;
	}

	void moveRight() 
	{
		theta -= dTheta;
		if (theta < 0)
			theta += 360;
	}
};



//Real numbers to determine the materials
GLfloat material_ambient[] = {0.2, 0.2, 0.2};
GLfloat material_diffuse[] = {0.4, 0.4, 0.4};
GLfloat material_specular[] = {0.4, 0.4, 0.4};
GLfloat material_shininess = 50.0f;

GLfloat cYellow[] = {1.0, 1.0, 0.2, 1.0};
GLfloat cPurple[] = {0.8, 0, 0.8};
GLfloat cBlack[] = {0.1, 0.1, 0.1};
GLfloat cPeach[] = {1.0, 0.937, 0.83};
GLfloat cGreen[] = {0.0, 1.0, 0.0, 1.0};
GLfloat cWhite[] = {1.0, 1.0, 1.0, 1.0};
GLfloat cBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat cGray[] = {0.6, 0.6, 0.6, 1.0};
GLfloat cRed[] = {1.0, 0.0, 0.0, 1.0};

//the last key pressed
unsigned lastKey = 'q';

//Variables for tracking objects
GLfloat puckx, pucky, mx1, my1, mx2, my2;
GLfloat vx, vy, tmp;
GLUquadric *quad = gluNewQuadric();
GLUquadric *quad1 = gluNewQuadric();
GLUquadric *quad2 = gluNewQuadric();
GLuint floorTexture;
Camera camera;
int mousex, mousey;
int isEnded, win;


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
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

void Init()
{
	srand(time(0));

	//Init Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
		
	//Enable depth
	glEnable(GL_DEPTH_TEST);

	//Init texture
	floorTexture = LoadTexture("floor.bmp");

	//Init positions
	puckx = pucky = 0;
	mx1 = 0, my1 = -10;
	mx2 = 0, my2 = 10;
	vx = (rand() % 100) / 100.0;
	vy = -sqrt(1 - vx * vx);
	isEnded = 0; win = -1;
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width/(double)height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 27) 
		exit(0);
	lastKey = key;
}

void special(int key, int, int)
{	
	if (key == GLUT_KEY_LEFT)
		camera.moveLeft();
	else if (key == GLUT_KEY_RIGHT)
		camera.moveRight();
	glutPostRedisplay();
}

void onMouseMove(int x, int y)
{
	mousex = x;
	mousey = y;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
            0, 0, 0,
            -camera.getX(), -camera.getY(), 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	GLfloat light0_position[] = {10, 10, 10, 1};
	GLfloat light1_position[] = {100, 0, 10, 1};
	GLfloat light2_position[] = {-100, 0, 10, 1};
	GLfloat light_colors[] = {0.4, 0.4, 0.4};

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_colors);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_colors);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_colors);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_colors);

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
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);   
	glTexCoord2f(0.0, 0.0);
	glVertex3f(BOUND, BOUND, 0);
	glTexCoord2f(0.0, REPEAT);	
	glVertex3f(-BOUND, BOUND, 0);
	glTexCoord2f(REPEAT, REPEAT);	
	glVertex3f(-BOUND, -BOUND, 0);
	glTexCoord2f(REPEAT, 0.0);	
	glVertex3f(BOUND, -BOUND, 0);
	glEnd();					
	glPopMatrix();
	
	//Draw two cubes
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0, -10, -11);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGray);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);
	glutSolidCube(22);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, -11);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cGray);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);
	glutSolidCube(22);
	glPopMatrix();  

	//Draw Six Rectangles
	glPushMatrix();
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cBlue);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);	
	glRectf(-11, -20, -4, -21);
	glRectf(4, -20, 11, -21);
	glRectf(-4, 20, -11, 21);
	glRectf(4, 20, 11, 21);
	glRectf(-11, -20, -10, 20);
	glRectf(11, -20, 10, 20);
	glPopMatrix(); 

	//Draw Goal 1
	glPushMatrix();
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glRectf(-4, -20, 4, -21);
	glPopMatrix(); 

	//Draw Goal 2
	glPushMatrix();
	glTranslatef(0, 0, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	glRectf(-4, 20, 4, 21);
	glPopMatrix(); 

	//Draw a puck
	glPushMatrix();
	glTranslatef(puckx, pucky, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	gluCylinder(quad, 1, 1, 1, 15, 15);
	glTranslatef(0, 0, 1e-2 + 1);
	gluDisk(quad, 0, 1, 15, 15);
	glPopMatrix(); 

	//Draw mallet 1
	glPushMatrix();
	glTranslatef(mx1, my1, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cBlue);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	gluCylinder(quad1, 1.5, 1.5, 1, 15, 15);
	glTranslatef(0, 0, 1e-2 + 1);
	gluDisk(quad1, 0, 1.5, 15, 15);
	glPopMatrix(); 

	//Draw mallet 1
	glPushMatrix();
	glTranslatef(mx2, my2, 1e-2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cPurple);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
	gluCylinder(quad2, 1.5, 1.5, 1, 15, 15);
	glTranslatef(0, 0, 1e-2 + 1);
	gluDisk(quad2, 0, 1.5, 15, 15);
	glPopMatrix(); 


	//Game is over
	if (isEnded)
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cRed);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.2);	
		glRasterPos2f(-4.5, 0);
		string wins = "You Won!";
		string lose = "You Lost!";
		if (win == 1)
		{
			for (int i = 0; i < wins.size(); i ++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, wins[i]);
		}
		else 
			for (int i = 0; i < lose.size(); i ++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lose[i]);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void timer(int value)
{
	//If either side win, we don't do any changes
	if (isEnded) 
	{
		//If user pressed 'ENTER', we should restart the game 
		if (lastKey == 13)
		{
			lastKey = 'x';    //a meaningless value
			isEnded = 0;
			win = -1;
			puckx = pucky = 0;
			vx = (rand() % 100) / 100.0;
			vy = -sqrt(1 - vx * vx);
		}
		glutPostRedisplay();
		glutTimerFunc(10, timer, 0);
		return ;
	}

	lastKey = 'x';
	//check puck's collision with goal 1
	if (pucky + vy >= 18.9 && fabs(puckx) <= 3.5)
	{
		isEnded = 1;
		win = 1;
		puckx += vx, pucky += vy;
		glutPostRedisplay();
		glutTimerFunc(10, timer, 0);
		return ;
	}

	//check puck's collision with goal 2
	if (pucky + vy <= -18.9 && fabs(puckx) <= 3.5)
	{
		isEnded = 1;
		win = 0;
		puckx += vx, pucky += vy;
		glutPostRedisplay();
		glutTimerFunc(10, timer, 0);
		return ;
	}

	//Move AI's mallet according to a simple AI
	if (rand() % 100 <= 40)
		tmp = 0;
	else tmp = 0.3;
	if (mx2 < puckx) 
		mx2 += tmp; else mx2 -= tmp;
	if (rand() % 100 <= 5)
		if (mx2 > 0) mx2 -= tmp * 3;
		else mx2 += tmp * 3;

	//Check puck's collision with wall
	if (puckx + vx <= -9 || puckx  + vx >= 9)
		vx *= -1;
	if (pucky + vy <= -19 || pucky + vy >= 19)
		vy *= -1;
	if (fabs(vx) <= 1e-2)
		vx += (rand() % 200 - 100) / 200.0;
	//Check puck's collision with AI's mallet
	if ((puckx - mx2) * (puckx - mx2) + (pucky - my2) * (pucky - my2) < 2.5 * 2.5)
	{
		vx = puckx - mx2;
		vy = pucky - my2;
		tmp = sqrt(vx * vx + vy * vy);
		vx /= tmp, vy /= tmp;
	}

	//Check puck's collision with user's mallet
	if ((puckx - mx1) * (puckx - mx1) + (pucky - my1) * (pucky - my1) < 2.5 * 2.5)
	{
		vx = puckx - mx1;
		vy = pucky - my1;
		tmp = sqrt(vx * vx + vy * vy);
		vx /= tmp, vy /= tmp;
	}

	puckx += vx / 3.0, pucky += vy / 3.0;
	if (puckx > 10) puckx = 9;
	if (puckx < -10) puckx = -9;
	if (pucky > 20) pucky = 19;
	if (pucky < -20) pucky = -19;

	//Move user's mallet according to mouse
	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
 
	winX = (float) mousex;   
    winY = (float) viewport[3] - (float) mousey;	
    glReadPixels(winX, (int) winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ); 
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//If this point is really on the plane z = 0
	if (fabs(posZ) <= 0.05 || fabs(posZ - 1) <= 0.05)
	{
		//If this point is within user's half court
		if (-8.5 <= posX && posX <= 8.5)
			if (-18.5 <= posY && posY <= -4)
				mx1 = posX, my1 = posY;
	}

	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}


int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**) argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("实时图形大作业 - 陶文博 & 黄景畦");

	Init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutTimerFunc(10, timer, 0);
	glutKeyboardFunc(keyPressed);
	glutPassiveMotionFunc(onMouseMove);

	
	glutMainLoop();

	return 0;
}
