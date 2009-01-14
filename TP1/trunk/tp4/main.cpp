///
/// Sistemas Gráficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include <list>
#include <vector>
#include "VistaCorteModelo.h"
#include "LSolidos.h"
#include "Iluminacion.h"
#include "Solido.h"
#include "Material.h"
#include "textura.h"

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

#include <iostream>
#define INSTANCE true
#define SHOOT false

// Declaraciones de variables
static int wancho; 
static int walto;
static bool modo_click=true;
static bool click_timeout=true;

// Variables
//Solido* solido2;
//bool funcionando=false;
std::list<Solido*> lsolid;
VistaCorteModelo vcm;
Iluminacion iluminacion;
Material material;

static const int cortes = 20;
int pasos = 4;

/*--------------------------------------------------------------------*/
// Realiza el cambio de coordenadas
void normalizar(int x, int y, Punto &pto){	
	pto.x = (float)(x - (float)wancho*3/4)/(float)wancho*4;
	pto.y = (float)(walto*5/6 - y)/walto*6;
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

void dibujarEjes(){

	glBegin(GL_LINES);
		glVertex3d(-10,-0.333,0);
		glVertex3d(10,-0.333,0);
		glVertex3d(0,-0.333,0);
		glVertex3d(0,-10,0);
	glEnd();
}
/*--------------------------------------------------------------------*/
///Dibuja tablero
void tablero(bool borde){
	int largo = 8, ancho = 6;
	double lado = 0.25;
	Color c1 = {100, 100, 100}, c2 = {150, 150, 150};
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3ub(255,255,255);

	for (int j = 0; j < largo; j++){
		for (int i = 0; i < ancho; i++){
			glBegin(GL_QUADS);
				if ((i + j) % 2 == 0)
					glColor3ub(c1.r, c1.g, c1.b);
				else glColor3ub(c2.r, c2.g, c2.b);

				glVertex3d(i*lado, j*lado, 0.0);
				glVertex3d((i+1)*lado, j*lado, 0.0);
				glVertex3d((i+1)*lado, (j+1)*lado, 0.0);
				glVertex3d(i*lado, (j+1)*lado, 0.0);
			glEnd();
		}
	}

	if (borde){
		
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture[0] );

		glColor3f(1.0,0.0,1.0);
			glBegin(GL_QUADS);	
				glTexCoord3d(0.0,0.0,0.0); glVertex3d(0.0, 0.0, 0.0);
				glTexCoord3d(0.0,largo*lado, 0.0); glVertex3d(0.0, largo*lado, 0.0);
				glTexCoord3d(0.0,largo*lado, 0.5); glVertex3d(0.0, largo*lado, 0.5);
				glTexCoord3d(0.0, 0.0, 0.5); glVertex3d(0.0, 0.0, 0.5);
			glEnd();

	
		glBindTexture( GL_TEXTURE_2D, texture[0] );
		glColor3f(1.0,0.0,1.0);
			glBegin(GL_QUADS);	
				glVertex3d(0.0, largo*lado, 0.0);
				glVertex3d(ancho*lado, largo*lado, 0.0);
				glVertex3d(ancho*lado, largo*lado, 0.5);
				glVertex3d(0.0, largo*lado, 0.5);	
			glEnd();

		glBindTexture( GL_TEXTURE_2D, texture[0] );
		glColor3f(1.0,0.0,1.0);
			glBegin(GL_QUADS);	
				glVertex3d(lado*ancho, 0.0, 0.0);
				glVertex3d(ancho*lado, largo*lado, 0.0);
				glVertex3d(ancho*lado, largo*lado, 0.5);
				glVertex3d(lado*ancho, 0.0, 0.5);		
			glEnd();
		glDisable( GL_TEXTURE_2D );
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
	glEnable(GL_DEPTH_TEST);
}


void display(void)
{
	///
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
   	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
    glLoadIdentity();
	///
	
	std::list<Solido*>::iterator ite;

	glViewport(0,0,wancho,walto);
	glDisable(GL_LIGHTING);

/// Dibujo ejes
	glColor3ub(255,255,255);
	dibujarEjes();

///Viewport para el solido de revolucion
	viewport(wancho/2, 0, wancho/2, walto*1/3);
	vcm.setCantPasos(pasos);
	vcm.dibujar();

///Viewport para el pinball
	viewport(0, walto*1/3, wancho, walto*2/3);

	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
				gluPerspective( 45 ,		// Ángulo de visión
				(float)walto/(float)wancho, // Razón entre el largo y el ancho, para calcular la perspectiva
				1,					    // Cuan cerca se puede ver
				2000);	
				
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		gluLookAt(0.0,0.0,3.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
		
		glPushMatrix();
			glTranslatef (-0.75, -0.7, 0.0);
			glRotatef((GLfloat) -60, 1.0, 0.0, 0.0);
			tablero(true);
		glPopMatrix();


	material.primero();
	for (ite=lsolid.begin();ite!=lsolid.end();ite++){
		material.sigMaterial();
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		(*ite)->setCantCortes(cortes);
		
		glPushMatrix();
			glRotatef((GLfloat) 60, 1.0, 0.0, 0.0);
			iluminacion.luces();
			glPushMatrix();

				material.material();
				glScalef(0.3,0.3,0.3);
				(*ite)->dibujar_solido(wancho,walto);
			glPopMatrix();
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);

///Viewport vista superior del tablero
	viewport(0, 0, wancho/2, walto*1/3);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(0.0,0.0,0.5, 
				      0.0,0.0,0.0, 
				      -1.0,0.0,0.0);

			glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				    glTranslatef (-0.75, -1.0, 0.0);
					tablero(false);
				glPopMatrix();
		
		Curva* generatriz2 = vcm.getCurvaGeneratriz();
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		material.primero();
			glScalef(0.3,0.3,0.3);
			glRotatef((GLfloat) 90, 1.0, 0.0, 0.0);
			//solido.dibujar_solido(generatriz2->getBufferPtosDisc(), generatriz2->getCantPtosDisc(),
			//			  wancho, walto);

			for (ite=lsolid.begin();ite!=lsolid.end();ite++){
				material.sigMaterial();
				material.material();
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				(*ite)->setCantCortes(cortes);
				(*ite)->dibujar_solido(wancho,walto);
			}
		glPopMatrix();
		glPopMatrix();
		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	///
  	glutSwapBuffers();
	///

}

void funcionTimer(int numero){
	click_timeout=true;
	//funcionando=true;
}

void controlMouse(int button, int state, int x, int y){
	Punto pto;
	float posx, posy;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if ( x >= wancho/2 && x <= wancho && y >= walto*2/3 && y < walto) {
		/// Para agregar punto en el viewport 3
			normalizar(x,y,pto);
			vcm.guardarPunto(pto);
			glutPostRedisplay();
		}
		else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto 
				  && iluminacion.getCantLuces() <= 7)
			{
			//para detectar doble click
			if (click_timeout){
				click_timeout=false;
				glutTimerFunc(300,funcionTimer, 1);
				return;
			}
			//material.sigMaterial();
			std::cout<<"x,y"<<x<<","<<y<<std::endl;
			posx = (float)(x - wancho/4)/wancho*4;
			posy = (float)(walto*5/6 - y)/walto*6;
			std::cout<<"posx,posy"<<posx<<","<<posy<<std::endl;
			/*if (iluminacion.agregarLuz(posx, posy))*/
			if (modo_click==INSTANCE) {
				int cantPuntos=vcm.getCurvaGeneratriz()->getCantPtosDisc();
				if (cantPuntos>=2){
					Punto* nuevo_punto;
					Punto* vPuntos =new Punto[cantPuntos];
					vPuntos=vcm.getCurvaGeneratriz()->getBufferPtosDisc();
					std::vector<Punto*> vec;
					for (int i=0;i <cantPuntos; i++){
						nuevo_punto=new Punto(vPuntos[i]);
						vec.push_back(nuevo_punto);
					}
					//Solido* solido=new Solido(x,y,vec);
					Solido* solido=new Solido(posx,posy,vec);
					//solido2=solido;
					lsolid.push_back(solido);
					vcm.limpiarVista();
				}
			}
			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto){ 
			vcm.limpiarVista();	
			glutPostRedisplay();
		}
		/*else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto ){
			iluminacion.eliminarFuentes();
			glutPostRedisplay();
		}*/
	}

}

void controlMovimientoMouse(int x, int y){
	/*
	std::cout<<"posicion:"<<x<<","<<y<<std::endl;
	float posx,posy;
	posx = (float)(x - wancho/4)/wancho*4;
	posy = (float)(walto*5/6 - y)/walto*6;
	if (funcionando){
		solido2->setPosicion(posx,posy,0);
		glutPostRedisplay();
	}
	*/
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
				vcm.destruir();
				exit (1);
				break;

	case 'v':
	case 'V':	
				//Cambia modo a modo sombreado/alambre
				Solido::cambiarVista();
				break;

	case 'm':
	case 'M':
				material.sigMaterial();
				break;
	case 'p':
	case 'P':
				vcm.limpiarVista();
				break;
	case 'c':
	case 'C': //Cambia la interpretacion de los clicks en el viewport 2
			  //instanciacion de solidos o disparo de pelota
			  //true: solidos   |    false: disparo
			{
				if (modo_click==SHOOT) {
					modo_click=INSTANCE;
					std::cout<<"Se paso a modo INSTANCE"<<std::endl;
					break;
				}
				if (modo_click==INSTANCE){
					modo_click=SHOOT;
					std::cout<<"Se paso a modo SHOOT"<<std::endl;
					break;
				}
			}
	}

	glutPostRedisplay();
}

/*-----------------------------------------------------------------------------*/
void inicializarLista(){
	//RegSolido* reg = new RegSolido(0, 0, 0, NULL);
	//lSolidos.lista.push_back(reg);	
}

void uso(){
	std::cout<<"Presione t...Para cambiar textura "<<std::endl;
	std::cout<<"Presione l...Para eliminar todas las luces"<<std::endl;
	std::cout<<"Presione p...Para eliminar todos los puntos de control"<<std::endl;
	std::cout<<"Presione c...Para cambiar a modo disparo/instanciacion"<<std::endl;
	std::cout<<"Presione v...Para cambiar a vista sombreada/alambre"<<std::endl;
}

int main(int argc, char** argv)
{
   inicializarLista();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (600, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();

   // Carga las Texturas
   LoadTextures();

   glutMouseFunc(controlMouse);
   glutPassiveMotionFunc(controlMovimientoMouse);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   uso();
   glutMainLoop();
   return 0;
}
