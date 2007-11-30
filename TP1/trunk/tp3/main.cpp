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

//sacar
#include <cmath>
#include <iostream>
using namespace std;

// Declaraciones de variables
static int wancho; 
static int walto;

/*--------------------------------------------------------------------*/
void normalizar(int x, int y, Punto &pto){
	pto.x = (float)(x - (float)wancho/2)/(float)wancho*2;
	pto.y = -(float)(y - walto/2)/walto*2;
	pto.z = 0;
}

/// Para dibujar malla
/// Rota el punto p_in theta radianes sobre el eje ???? dando como resultado p_out
void rotarPunto(const double angulo, const Punto& p_in, Punto& p_out){
/*	
	//eje de revolucion x
	p_out.x = p_in.x;
	p_out.y = p_in.y*cos(theta) - p_in.z*sin(theta);
	p_out.z = p_in.y*sin(theta) + p_in.z*cos(theta);
*/
	//eje de revolucion y

	p_out.x = p_in.x*cos(angulo) - p_in.z*sin(angulo);
	p_out.y = p_in.y;
	p_out.z = p_in.x*sin(angulo) + p_in.z*cos(angulo);


	//eje de revolucion z
/*
	p_out.x = p_in.x*cos(theta) - p_in.y*sin(theta);
	p_out.y = p_in.x*sin(theta) + p_in.y*cos(theta);
	p_out.z = p_in.z;
*/
}

void solido(Punto* bPuntos, int n_points, int rot_pts)
{
	double ang, c;
	Punto p1, p2, p;

	c=3.14159/180.0; //grados a radianes
	
	int i, j;

	for (i=0; i< n_points; i++){

		p1.x = bPuntos[i].x; p1.y = bPuntos[i].y; p1.z = bPuntos[i].z;
		p2.x = bPuntos[i+1].x; p2.y = bPuntos[i+1].y; p2.z = bPuntos[i+1].z;

		glBegin(GL_QUAD_STRIP);
		for (j=0; j<=rot_pts;j++){
			ang=j*360.0*c/rot_pts; //angulo de la curva a calcular

			rotarPunto(ang, p1, p);
			glVertex3d(p.x, p.y, p.z);

			rotarPunto(ang, p2, p);
			glVertex3d(p.x, p.y, p.z);

		}
		glEnd();
	}

}
/*--------------------------------------------------------------------*/
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   wancho = w;
   walto = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
            1.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
   else
        glOrtho(1.0 * (GLfloat) w / (GLfloat) h,
            1.0 * (GLfloat) w / (GLfloat) h, -1.0, 1.0, -10.0, 10.0);
	
}




void init(void) 
{
	/// Incluir aquí todo lo que deba inicializare antes
	/// de entrar en el loop de OpenGL
}


void dibujarEjes()
{
	glBegin(GL_LINES);
		glVertex3d(-10,0,0);
		glVertex3d(10,0,0);
		glVertex3d(0,-10,0);
		glVertex3d(0,10,0);
		glVertex3d(0,0,-10);
		glVertex3d(0,0,10);
	glEnd();
}
void display(void)
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///
	
	/// Dibujo ejes
	glColor3ub(255,255,255);
	dibujarEjes();
	
	
/// Dibuja corte del modelo
	VistaCorteModelo::getInstancia()->dibujar();
		//VistaCorteModelo::getInstancia()->mostrarCurvaDiscretizada();



/// Para dibujar solido
	Curva* generatriz = VistaCorteModelo::getInstancia()->getCurvaGeneratriz();
	glPushMatrix();
		glTranslatef(0.5,1.0,0.0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		solido(generatriz->getBufferPtosDisc(), generatriz->getCantPtosDisc()-1, 20);
	glPopMatrix();

	///
  	glutSwapBuffers();
	///
}


void controlMouse(int button, int state, int x, int y){
	Punto pto;

	if (button == GLUT_LEFT_BUTTON){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto) {
		normalizar(x,y,pto);
		VistaCorteModelo::getInstancia()->guardarPunto(pto);
		glutPostRedisplay();
		}
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
		VistaCorteModelo::getInstancia()->destruir();
		exit (1);
		break;
	}
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (600, 500); 
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
