///
/// Sistemas Gráficos - 6671
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

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

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

void display()
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///

	int posicionX;
	int posicionY;

	int radMin;
	int radMax;

	int numRayos;
	
	Color colCentro;
	Color colRayos;

	// Se define cuantas estrellas dibujar.
	int cantEstrellas = rand() % 20 + 25; 

	Estrella * estrella;
	
	// Se dibuja una estrella en cada iteración.
	for(int i = 0; i<cantEstrellas; i++)
	{
		// se obtiene una posición aleatoria.
		posicionX = rand() % 1000;
		posicionY = rand() % 600;

		// Se obtiene un tamaño aleatorio.
		radMin = rand() % 20;
		radMax = rand() % 50 + radMin + 20;

		// Se define la cantidad de rayos de la estrella de forma aleatoria.
		numRayos = rand() % 10 + 10;

		// Se define un color aleatorio para el centro.
		colCentro.r = rand() % 255;
		colCentro.g = rand() % 255;
		colCentro.b = rand() % 255;

		// Se define un color aleatorio para los rayos.
		colRayos.r = rand()%255;
		colRayos.g = rand()%255;
		colRayos.b = rand()%255;

		// Se instancia la estrella y se la dibuja.
		estrella = new Estrella(posicionX,posicionY,radMin,radMax,numRayos,colCentro,colRayos);
		estrella->dibujar();
		delete estrella;
		
	}

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
   glutInitWindowSize (1000, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
	
   return 0;
}
