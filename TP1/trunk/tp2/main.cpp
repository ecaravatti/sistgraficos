///
/// Sistemas Gr�ficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include "curva.h"
#include <iostream>
#include "Declaraciones.h"
#include "GeneradorPtos.h"
#include <cmath>
#include "Estrella.h"

using namespace std;

#define RAD 57.2957795135

char caption[]="Sistema Gr�ficos - 66.71 - 2007c1";

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}


void init(void) 
{
	/// Incluir aqu� todo lo que deba inicializare antes
	/// de entrar en el loop de OpenGL
}

void display()
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///
/*
/// primer curva
	GeneradorPtos gp(1);
	gp.generarPtos();
	Punto *ptro = gp.getPuntos();
	cout<<"Primera Curva"<<endl;
	for (int i = 0; i < 4; i++){
		cout<<ptro[i].x<<" "<<ptro[i].y<<endl;
	}
	Color color0 = {255,0,0};
	Color color1 = {0,0,255};
	//se tienen q copiar los ptos 
	Curva c1(ptro, GeneradorPtos::res, 4, 20,color0, color1,1);
	glTranslatef(0, 50, 0);
	c1.dibujarBSpline();
	glBegin(GL_LINE_STRIP);
		glVertex2i(0,0);
		glVertex2i(GeneradorPtos::res, GeneradorPtos::res*0.125);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2i(0,0);
		glVertex2i(GeneradorPtos::res, -GeneradorPtos::res*0.125);
	glEnd();

	
/// segunda curva
	GeneradorPtos gp2(3);
	gp2.generarPtos();
	Punto *ptro2 = gp2.getPuntos();
	cout<<"Segunda Curva"<<endl;
	for (int j = 0; j < 10; j++){
		cout<<ptro2[j].x<<" "<<ptro2[j].y<<endl;
	}
	Color color2 = {205,92,92};
	Color color3 = {139,0,0};
	//se tienen q copiar los ptos 
	Curva c2(ptro2, GeneradorPtos::res, 10,20,color2, color3,1.5);
	glTranslatef(0, 50, 0);
	c2.dibujarBSpline();
*/

// Tercera curva
/*	GeneradorPtos gp3(5);
	gp3.generarPtos();
	Punto *ptro3 = gp3.getPuntos();
	cout<<"Segunda Curva"<<endl;
	for (int k = 0; k < 16; k++){
		cout<<ptro3[k].x<<" "<<ptro3[k].y<<endl;
	}
	Color color4 = {173, 255, 47};
	Color color5 = {0, 128, 128};
	//se tienen q copiar los ptos 
	Curva c3(ptro3, GeneradorPtos::res, 16, 20,color4, color5,2.0);
	glTranslatef(0, 50, 0);
	c3.dibujarBSpline();
	glBegin(GL_LINE_STRIP);
		glVertex2i(0,0);
		glVertex2i(GeneradorPtos::res, GeneradorPtos::res*0.125);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2i(0,0);
		glVertex2i(GeneradorPtos::res, -GeneradorPtos::res*0.125);
	glEnd();	
*/

/// Dibujar Estrella
/// No tiene en cuenta radio max
	Color color0 = {255,0,0};
	Color color1 = {0,0,255};
	Estrella e1(200, 200, 25, 100, 15, color0, color1);
	e1.dibujar();
	
	///
  	glutSwapBuffers();
	///
	
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
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
	
   return 0;
}
