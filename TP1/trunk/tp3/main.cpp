///
/// Sistemas Gráficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include "VistaCorteModelo.h"

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

#include <iostream>
using namespace std;

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}




void init(void) 
{
	/// Incluir aquí todo lo que deba inicializare antes
	/// de entrar en el loop de OpenGL
}



void display(void)
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///

	glColor3ub(255,255,255);
	glBegin(GL_LINES);
		glVertex2i(wancho/2, 0);
		glVertex2i(wancho/2, walto);

		glVertex2i(0, walto/2);
		glVertex2i(wancho, walto/2);
	glEnd();

	VistaCorteModelo::getInstancia()->dibujar();
	///
  	glutSwapBuffers();
	///
}


void controlMouse(int button, int state, int x, int y){
	Punto pto;

	if (button == GLUT_LEFT_BUTTON){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto) {
		pto.x = x;
		pto.y = y;
		pto.z = 1;
		VistaCorteModelo::getInstancia()->guardarPunto(pto);
		cout<<"coordenadax "<<x<<endl;
		cout<<"coordenaday "<<y<<endl;
		glutPostRedisplay();
		}
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
		exit (1);
		break;
	}
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (wancho, walto); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();
   glutMouseFunc(controlMouse);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
