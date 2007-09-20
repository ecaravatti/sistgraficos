///
/// Sistemas Gráficos - 6671
/// 2do cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include "Segmento.h"
#include <stdlib.h>

char caption[]="Sistema Gráficos - 66.71 - 2007c2";



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

	// Poner aca los puntos a dibujar
	Punto p1 = *new Punto (200,400);
	Punto p2 = *new Punto (4,200);

	Segmento* seg = new Segmento(p1,p2);


	glBegin(GL_POINTS);
		glVertex2i(100,100);
		glVertex2i(200,100);
		glVertex2i(200,200);
		glVertex2i(100,200);

		seg->dibujarDDA();
	glEnd();

	delete seg;




	///
  	glutSwapBuffers();
	///
}





void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b: // Escape
		exit (1);
		break;
	}
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (300, 300); 
   glutInitWindowPosition (500, 300);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
