 #include "stdafx.h"
 
 #include<gl/glut.h>
 
 //#include<gl/glu.h>����//glut.h�Զ�������glu.h �� gl.h
 
 //#include<gl/gl.h>
 
  
 
 void renderScene(void)
 
 {
 
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
          glLoadIdentity();
 
          glBegin(GL_TRIANGLES);
 
          glVertex3f(-0.5,-0.5,0.0);
 
          glVertex3f(0.5,0.0,0.0);
 
          glVertex3f(0.0,0.5,0.0);
 
          glEnd();
 
          glutSwapBuffers();
 
 }
 
  
 
 int _tmain(int argc, _TCHAR* argv[])
 
 {
 
          glutInit(&argc, (char**) argv);
 
          glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 
          glutInitWindowPosition(100,100);
 
          glutInitWindowSize(320,320);
 
          glutCreateWindow("Hello OpenGL");
 
          glutDisplayFunc(renderScene);
 
          glutMainLoop();//enters the GLUT event processing loop.
 
          return 0;
 
 }
