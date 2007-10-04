///
/// Sistemas Gráficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include "Segmento.h"

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

	//Vertical
	Segmento seg1(new Vertice(200,0), new Vertice(200, 400));
	//Horizontal
	Segmento seg2(new Vertice(0,200), new Vertice(400, 200));
	//pendiente abs(m) < 1
	Segmento seg3(new Vertice(200,200), new Vertice(400,280));
	//pendiente abs(m) == 1
	Segmento seg4(new Vertice(200,200), new Vertice(400,400));
	//pendiente abs(m) > 1 (2.5)
	Segmento seg5(new Vertice(200,200), new Vertice(280,400));
	glBegin(GL_POINTS);
		seg1.dibujarBresenham();
		seg2.dibujarBresenham();
		seg3.dibujarBresenham();
		seg4.dibujarBresenham();
		seg5.dibujarBresenham();
	glEnd();



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
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
