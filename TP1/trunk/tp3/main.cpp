///
/// Sistemas Gráficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include "VistaCorteModelo.h"
#include "Iluminacion.h"
#include "Solido.h"

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

#include <iostream>


// Declaraciones de variables
static int wancho; 
static int walto;

//angulos de rotacion
float alpha = 0, beta = 0;
static int x0_rot, y0_rot;

// Variables
VistaCorteModelo vcm;
Iluminacion iluminacion;
Solido solido;
static const int cortes = 20;
int pasos = 4;

/*--------------------------------------------------------------------*/
// Realiza el cambio de coordenadas
void normalizar(int x, int y, Punto &pto){	
	pto.x = (float)(x - (float)wancho*3/4)/(float)wancho*4;
	pto.y = (float)(walto*3/4 - y)/walto*4;
	pto.z = 0;
}

/*--------------------------------------------------------------------*/
// Configura un viewport
void viewport(int posx, int posy, int w, int h){
	glViewport (posx, posy, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	
	if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
            1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
	else
        glOrtho(1.0 * (GLfloat) w / (GLfloat) h,
            1.0 * (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	
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
	glEnable(GL_DEPTH_TEST);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///
	
	glViewport(0,0,wancho,walto);
	glDisable(GL_LIGHTING);

/// Dibujo ejes
	glColor3ub(255,255,255);
	dibujarEjes();
	
	
/// Dibuja corte del modelo
	viewport(wancho/2,0,wancho/2,walto/2);
	vcm.setCantPasos(pasos);
	vcm.dibujar();


/// Para dibujar solido
	Curva* generatriz = vcm.getCurvaGeneratriz();
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		solido.setCantCortes(cortes);
		solido.setIluminacion(&iluminacion);
		solido.setAngulo(alpha, beta);
		solido.solido(generatriz->getBufferPtosDisc(), generatriz->getCantPtosDisc(),
					  wancho, walto);

	viewport(0, 0, wancho/2, walto/2);
	iluminacion.mostrarLuces();
	///
  	glutSwapBuffers();
	///
}


void controlMouse(int button, int state, int x, int y){
	Punto pto;
	float posx, posy;

	if (button == GLUT_LEFT_BUTTON){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto) {
			normalizar(x,y,pto);
			vcm.guardarPunto(pto);
			glutPostRedisplay();
		}
		else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto 
				  && iluminacion.getCantLuces() <= 7){
			posx = (float)(x - wancho/4)/wancho*4;
			posy = (float)(walto*3/4 - y)/walto*4;

			if (iluminacion.agregarLuz(posx, posy))
											glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto){ 
			vcm.limpiarVista();	
			glutPostRedisplay();
		}
		else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto ){
			iluminacion.eliminarFuentes();
			glutPostRedisplay();
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (y <= walto/2 && y >= 0){
			x0_rot = x;
			y0_rot = y;
		}
	}
}

void controlMovimientoMouse(int x, int y){
	if ( y <= walto/2 && y >= 0){
		alpha = (alpha + (y - y0_rot));
		beta = (beta + (x - x0_rot));
		x0_rot = x; y0_rot = y;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
				vcm.destruir();
				exit (1);
				break;
	case 't':
	case 'T':
				if (iluminacion.getMaterial() == Iluminacion:: PLASTICO) 
					iluminacion.setMaterial(Iluminacion:: DIFUSO);
				else 
					iluminacion.setMaterial(Iluminacion:: PLASTICO);
				break;
	case 'l':
	case 'L':
				iluminacion.eliminarFuentes();
				break;
	case 'p':
	case 'P':
				vcm.limpiarVista();
				break;
	}

	glutPostRedisplay();
}

void uso(){
	std::cout<<"Presione t...Para cambiar textura "<<std::endl;
	std::cout<<"Presione l...Para eliminar todas las luces"<<std::endl;
	std::cout<<"Presione p...Para eliminar todos los puntos de control"<<std::endl;
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
   glutMotionFunc(controlMovimientoMouse);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   uso();
   glutMainLoop();
   return 0;
}
