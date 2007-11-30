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
static const int cantCortes = 40;

//*-------------------------------------------------------------------*/
const GLfloat esmeraldaAmb[4] = {0.0215f,0.1745f,0.0215f,0.55f};
const GLfloat esmeraldaDif[4] = {0.07568f,0.61424f,0.07568f,0.55f};
const GLfloat esmeraldaSpe[4] = {0.633f,0.727811f,0.633f,0.55};
GLfloat esmeraldaShi = 76.8f;
/*--------------------------------------------------------------------*/
void normalizar(int x, int y, Punto &pto){	
	pto.x = (float)(x - (float)wancho*3/4)/(float)wancho*4;
	pto.y = (float)(walto*3/4 - y)/walto*4;
	pto.z = 0;
}

/// Para dibujar malla
/// Rota el punto p_in theta radianes sobre el eje ???? dando como resultado p_out
void rotarPunto(const double angulo, const Punto& p_in, Punto& p_out){

	//eje de revolucion y
	p_out.x = p_in.x*cos(angulo) - p_in.z*sin(angulo);
	p_out.y = p_in.y;
	p_out.z = p_in.x*sin(angulo) + p_in.z*cos(angulo);

}

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

void initVistaPerspecticaSombreada(){
   viewport(0, walto/2, wancho/2, walto/2);

	GLfloat ambientlight[] =	{0.5f ,0.5f ,0.5f ,1.0f};
	GLfloat difuselight[] =		{1.0f ,1.0f ,1.0f ,1.0f};
	GLfloat specularlight[] =	{1.0f ,1.0f ,1.0f ,1.0f};
	GLfloat lightposition[] =	{20.0f,100.0f,10.0f,1.0f};
	
	//Se setean los parametros
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,difuselight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularlight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightposition);

	//glEnable(GL_DEPTH_TEST);	//Test de profundidad
	glEnable(GL_LIGHTING);	    //se activa la iluminacion
	glEnable(GL_LIGHT0);	    //se activa la luz 0 que previamente se habia seteado
	
	glEnable(GL_COLOR_MATERIAL);	//Se activa lo materiales de color
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  //Se desean de tipo ambiente y difusión (tambien incluyen specular

	
   glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldaAmb);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldaDif);
   glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldaSpe);
   glMaterialf(GL_FRONT, GL_SHININESS, esmeraldaShi);
	
}

//Para obtener el vector normal con norma = 1
void Normaliza(Punto& normal){
 float norm;

 norm = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
 normal.x = normal.x / norm;
 normal.y = normal.y / norm;
 normal.z = normal.z / norm;
}

//Calcula el producto vectorial de dos vectores
void calcularNormal(const Punto &v1, const Punto &v2, const Punto &v3, Punto& normal){
 float Qx, Qy, Qz, Px, Py, Pz;

 Px = v2.x-v1.x;
 Py = v2.y-v1.y;
 Pz = v2.z-v1.z;
 Qx = v3.x-v1.x;
 Qy = v3.y-v1.y;
 Qz = v3.z-v1.z;
 normal.x = Py*Qz - Pz*Qy;
 normal.y = Pz*Qx - Px*Qz;
 normal.z = Px*Qy - Py*Qx;
 Normaliza(normal);
}

void solido(Punto* bPuntos, int nPuntos, int cantCortes)
{
	double ang, c; 
	Punto p1, p2, p;
	int i, j;

	c=3.14159/180.0; //grados a radianes
	
	

	Punto r1,r2,r3,r4, normal;

		for (i=0; i< nPuntos - 1; i++){

		p1.x = (bPuntos[i].x + 1)/2; p1.y = bPuntos[i].y; p1.z = bPuntos[i].z;
		p2.x = (bPuntos[i+1].x + 1)/2; p2.y = bPuntos[i+1].y; p2.z = bPuntos[i+1].z;

		
		for (j=0; j<=cantCortes-1;j++){

		ang=j*360.0*c/cantCortes; //angulo de la curva a calcular
		rotarPunto(ang, p1, r1);
		rotarPunto(ang, p2, r2);

		ang=(j+1)*360.0*c/cantCortes;
		rotarPunto(ang, p1, r3);
		rotarPunto(ang, p2, r4);

		viewport(wancho/2, walto/2, wancho/2, walto/2);
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_QUADS);
			glVertex3d(r1.x, r1.y, r1.z);
			glVertex3d(r2.x, r2.y, r2.z);
			glVertex3d(r4.x, r4.y, r4.z);
			glVertex3d(r3.x, r3.y, r3.z);
		glEnd();
		

		//Normales
		initVistaPerspecticaSombreada();
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);
			calcularNormal(r1, r2, r3, normal);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(r1.x, r1.y, r1.z);
			glVertex3f(r2.x, r2.y, r2.z);
			glVertex3f(r3.x, r3.y, r3.z);

			calcularNormal(r4, r3, r2, normal);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(r2.x, r2.y, r2.z);
			glVertex3f(r3.x, r3.y, r3.z);
			glVertex3f(r4.x, r4.y, r4.z);
			
		glEnd();
		}
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
	
	glViewport(0,0,wancho,walto);
	glDisable(GL_LIGHTING);

/// Dibujo ejes
	glColor3ub(255,255,255);
	dibujarEjes();
	
	
/// Dibuja corte del modelo
	viewport(wancho/2,0,wancho/2,walto/2);
	VistaCorteModelo::getInstancia()->dibujar();


/// Para dibujar solido
	Curva* generatriz = VistaCorteModelo::getInstancia()->getCurvaGeneratriz();
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		solido(generatriz->getBufferPtosDisc(), generatriz->getCantPtosDisc(), cantCortes);

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
