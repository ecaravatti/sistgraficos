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
#include "Iluminacion.h"
#include "Solido.h"
#include "Material.h"
#include "textura.h"
#include "Pelota.h"

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

#include <iostream>
#define INSTANCE true
#define SHOOT false


// Declaraciones de variables
static Velocidad vel;
static float ro=2.0,tita=3*PI/2.0,fi=PI/3;
static int wancho; 
static int walto;
static GLfloat fSizes[2];

static bool draw_vect_vel=false;
static bool modo_click=true;
static bool click_timeout=true;

std::list<Solido*> lsolid;
VistaCorteModelo* vcm=VistaCorteModelo::getInstance();
static const int cortes = 20;
int pasos = 4;

/*******************************************************************************************/
// Realiza el cambio de coordenadas
void normalizar(int x, int y, Punto &pto){	
	pto.x = (float)(x - (float)wancho*3/4)/(float)wancho*4;
	pto.y = (float)(walto*5/6 - y)/walto*6;
	pto.z = 0;
}
/*******************************************************************************************/
//chequea q el nuevo solido se encuentre dentro del perimetro
bool dentroPerimetro(float centro_x,float centro_y,float radio){
	if ( centro_x<=0 || centro_x >=7.5 || centro_y<=0 || centro_y>=10 )
		return false;
	if ( centro_x<=radio || (7.5 - centro_x)<=radio )
		return false;
	if ( centro_y<=radio || (10 - centro_y)<=radio )
		return false;

	return true;
}
/*******************************************************************************************/
//chequea q el click se encuentre dentro del perimetro para definir disparos
bool dentroPerimetro(float posx,float posy){
	if ( posx<=0 || posx >=7.5 || posy<=0 || posy>=10 )
		return false;
	return true;
}
/*******************************************************************************************/
bool superponeSolidos(float centro_x,float centro_y,float radio){
	std::list<Solido*>::iterator itSolid;
	Punto centro(centro_x,centro_y,0);
	for (itSolid=lsolid.begin(); itSolid!=lsolid.end(); itSolid++){
		if (centro.distancia((*itSolid)->getPosicion()) <= (radio + (*itSolid)->getDiametro()/2)) 
			return true;
	}
	return false;
}	
/*******************************************************************************************/
void keyboard(unsigned char key, int x, int y){

	switch (key)
	{
	case 0x1b:
				vcm->destruir();
				exit (1);
				break;

	case 'v':
	case 'V':	
				//Cambia modo a modo sombreado/alambre
				Solido::cambiarVista();
				break;

	case 'p':
	case 'P':
				vcm->limpiarVista();
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
/*******************************************************************************************/
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
/******************************************************************************************/
void dibujarEjes(){

	glBegin(GL_LINES);
		glVertex3d(-10,-0.333,0);
		glVertex3d(10,-0.333,0);
		glVertex3d(0,-0.333,0);
		glVertex3d(0,-10,0);
	glEnd();
}
/*****************************************************************************************/
///Dibuja tablero
void tablero(bool borde){
	int largo = 8, ancho = 6;
	double lado = 0.25;
	Color c1 = {100, 100, 100}, c2 = {150, 150, 150};
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glColor3ub(255,255,255);

	if (borde){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	for (int j = 0; j < largo; j++){
		for (int i = 0; i < ancho; i++){
			glBegin(GL_QUADS);
				if ((i + j) % 2 == 0)
					//glColor3ub(c1.r, c1.g, c1.b);
					glColor4ub(c1.r, c1.g, c1.b,200);
				else //glColor3ub(c2.r, c2.g, c2.b); 
					glColor4ub(c2.r, c2.g, c2.b,200);
				
				glVertex3d(i*lado, j*lado, 0.0);
				glVertex3d((i+1)*lado, j*lado, 0.0);
				glVertex3d((i+1)*lado, (j+1)*lado, 0.0);
				glVertex3d(i*lado, (j+1)*lado, 0.0);
			glEnd();
		}
	}

	if (borde){
		glBegin(GL_QUADS);
			glColor4ub(0,0,0,255);

			glVertex3d(-5.0,0.0,0.0);
			glVertex3d(5.0,0.0,0.0);
			glVertex3d(5.0,-5.0,0.0);
			glVertex3d(-5.0,-5.0,0.0);

			glVertex3d(1.5,2.0,0.0);
			glVertex3d(5.0,2.0,0.0);
			glVertex3d(5.0,0.0,0.0);
			glVertex3d(1.5,0.0,0.0);

			glVertex3d(-5.0,0.0,0.0);
			glVertex3d(-5.0,2.0,0.0);
			glVertex3d(0.0,2.0,0.0);
			glVertex3d(0.0,0.0,0.0);

			glVertex3d(-5.0,2.0,0.0);
			glVertex3d(5.0,2.0,0.0);
			glVertex3d(5.0,7.0,0.0);
			glVertex3d(-5.0,7.0,0.0);
		glEnd();

		Textura::getInstance()->activar();
		Textura::getInstance()->setTex(0);

		//glEnable( GL_TEXTURE_2D );
		//glBindTexture( GL_TEXTURE_2D, texture[0] );
		//glEnable(GL_TEXTURE_GEN_S);
		//glEnable(GL_TEXTURE_GEN_T);

		glColor4f(1.0,1.0,1.0,1.0);
			glBegin(GL_QUADS);	
				glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
				glTexCoord2d(1.0, 0.0); glVertex3d(0.0, largo*lado, 0.0);
				glTexCoord2d(1.0, 1.0); glVertex3d(0.0, largo*lado, 0.25);
				glTexCoord2d(0.0, 1.0); glVertex3d(0.0, 0.0, 0.25);
			glEnd();

			glBegin(GL_QUADS);	
				glTexCoord2d(0.0, 0.0);glVertex3d(0.0, largo*lado, 0.0);
				glTexCoord2d(1.0, 0.0);glVertex3d(ancho*lado, largo*lado, 0.0);
				glTexCoord2d(1.0, 1.0);glVertex3d(ancho*lado, largo*lado, 0.25);
				glTexCoord2d(0.0, 1.0);glVertex3d(0.0, largo*lado, 0.25);	
			glEnd();

			glBegin(GL_QUADS);	
				glTexCoord2d(0.0, 0.0);glVertex3d(lado*ancho, 0.0, 0.0);
				glTexCoord2d(1.0, 0.0);glVertex3d(ancho*lado, largo*lado, 0.0);
				glTexCoord2d(1.0, 1.0);glVertex3d(ancho*lado, largo*lado, 0.25);
				glTexCoord2d(0.0, 1.0);glVertex3d(lado*ancho, 0.0, 0.25);		
			glEnd();
		glDisable( GL_TEXTURE_2D );
	}
}
/*****************************************************************************************/
void drawWorld(){
	std::list<Solido*>::iterator ite;
	int i=0;
	glPushMatrix();

		glScalef(0.2,0.2,0.2);
		for (ite=lsolid.begin();ite!=lsolid.end();ite++){
			(*ite)->dibujar();
		}

		Pelota::getInstance()->dibujar_pelota();

	glPopMatrix();

}
/*****************************************************************************************/
void drawUnderworld(){
	std::list<Solido*>::iterator ite;
	int i=0;
	glPushMatrix();

		glScalef(1.0f, -1.0f, 1.0f);
		glRotatef((GLfloat) 180, 1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);

		for (ite=lsolid.begin();ite!=lsolid.end();ite++){
			(*ite)->dibujar();
		}

		Pelota::getInstance()->dibujar_pelota();
		

	glPopMatrix();
}
/*****************************************************************************************/
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
/*****************************************************************************************/
void init(void) 
{
	/// Incluir aquí todo lo que deba inicializare antes
	/// de entrar en el loop de OpenGL
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);    // Smooth out points	
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Si todo funca bien activar
	//glEnable(GL_LINE_SMOOTH);     // Smooth out lines
	//glEnable(GL_POLYGON_SMOOTH);  // Smooth out polygon edges

	//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

}
/*****************************************************************************************/
void timerClick(int numero){
	click_timeout=true;
}
/*****************************************************************************************/
void display(void)
{
	GLfloat fCurrSize;
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
	vcm->setCantPasos(pasos);
	vcm->dibujar();

///Viewport para el pinball
	viewport(0, walto*1/3, wancho, walto*2/3);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		gluPerspective( 45 ,// Ángulo de visión
		2.0, // Antes: (float)walto/(float)wancho |||| Razón entre el largo y el ancho, para calcular la perspectiva 
		0.001,	 // Cuan cerca se puede ver
		2000);	
				
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		/**********Vista horizontal Z=0 (Z clasico)**********/
		/*gluLookAt(0.0,-3.0,0.0, 0.0,0.0,0.0, 0.0,0.0,1.0);*/
		/*glTranslatef (-0.75, -0.7, 0.0);				    */
	    /****************************************************/

		gluLookAt(ro * cos(tita) * sin(fi) + 0.75f
				 ,ro * sin(fi) * sin(tita) + 1.0f
				 ,ro * cos(fi)
				 ,0.75
				 ,1.0
				 ,0.0
				 ,0.0
				 ,0.0
				 ,1.0
				 );

		Iluminacion::getInstance()->luces();

		drawUnderworld();
		
		Iluminacion::getInstance()->apagar_luces();

		tablero(true);

		Iluminacion::getInstance()->luces();

		drawWorld();

		Iluminacion::getInstance()->apagar_luces();

	glPopMatrix();

///Viewport vista superior del tablero

	viewport(0, 0, wancho/2, walto*1/3);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(-1.5,1.5,1.0,-1.0,10,-10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glLoadIdentity();
		gluLookAt(0.75,1.0,-3.0, 0.75,1.0,0.0, 1.0,0.0,0.0);

		/*****Punto posicionamiento*****/
		/**********Solo debug***********/
		/*							   */
		/*glColor3ub(130,170,200);     */
		/*glBegin(GL_POINTS);		   */
		/*	glVertex3d(0.75, 1.0, 0.5);*/
		/*glEnd();					   */
		/*******************************/


		tablero(false);
		
		Iluminacion::getInstance()->luces();

		drawWorld();
		
		Iluminacion::getInstance()->apagar_luces();

			if(draw_vect_vel){
				glPushMatrix();
				glScalef(0.2,0.2,0.2);
				glColor3ub(255,0,0);
				fCurrSize = fSizes[0];
				glLineWidth(fCurrSize+1.0f);
				glBegin(GL_LINES);
				glVertex3f(Pelota::getInstance()->getPosX(),Pelota::getInstance()->getPosY(), 0.3f);
					glVertex3f(vel.getVelX(),vel.getVelY(),0.3f);
				glEnd();
				glLineWidth(fCurrSize);
				glPopMatrix();
			}
		

	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopMatrix();
	///
  	glutSwapBuffers();
	///

}
/*****************************************************************************************/
void inicializarLista(){	
}
/*****************************************************************************************/
void comandos()
{
	std::cout<<"Presione t...Para cambiar textura "<<std::endl;
	std::cout<<"Presione l...Para eliminar todas las luces"<<std::endl;
	std::cout<<"Presione p...Para eliminar todos los puntos de control"<<std::endl;
	std::cout<<"Presione c...Para cambiar a modo disparo/instanciacion"<<std::endl;
	std::cout<<"Presione v...Para cambiar a vista sombreada/alambre"<<std::endl;
}
/*****************************************************************************************/
void timerVectVel(int numero){
	draw_vect_vel=false;
	vel.setVelX(vel.getVelX()-Pelota::getInstance()->getPosX());
	vel.setVelY(vel.getVelY()-Pelota::getInstance()->getPosY());
	Pelota::getInstance()->setVelocidadInicial(vel);
}
/*****************************************************************************************/
void controlMouse(int button, int state, int x, int y){
	Punto pto;
	float posx, posy;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if ( x >= wancho/2 && x <= wancho && y >= walto*2/3 && y < walto) {
		/// Para agregar punto en el viewport 3
			normalizar(x,y,pto);
			vcm->guardarPunto(pto);
			glutPostRedisplay();
		}
		else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto )
			{
			//para detectar doble click
			if (click_timeout){
				click_timeout=false;
				glutTimerFunc(300,timerClick, 1);
				return;
			}

			posy=(float)(x-67)*(float)(10.0f/265.0f);
			posx=(float)(y-423)*(float)(7.5f/151.0f);

			if (modo_click==INSTANCE) {
				int cantPuntos=vcm->getCurvaGeneratriz()->getCantPtosDisc();
				if (cantPuntos>=2){
					Punto* nuevo_punto;
					Punto* vPuntos =new Punto[cantPuntos];
					vPuntos=vcm->getCurvaGeneratriz()->getBufferPtosDisc();
					std::vector<Punto*> vec;
					for (int i=0;i <cantPuntos; i++){
						nuevo_punto=new Punto(vPuntos[i]);
						vec.push_back(nuevo_punto);
					}
				
					float radio= Solido::calcularDiametro(vec)/2.0f;
					
					if (dentroPerimetro(posx,posy,radio) && !superponeSolidos(posx,posy,radio)){
						Solido* solido=new Solido(posx,posy,vec,Material::getInstance()->getSigMat(),Textura::getInstance()->getSigTex());
						solido->setCantCortes(cortes);
						lsolid.push_back(solido);
						Pelota::getInstance()->cargarSolido(solido);
						vcm->limpiarVista();
					}
					else std::cout<<"Ubicacion no valida"<<std::endl;
				}
			}
			if (modo_click==SHOOT && dentroPerimetro(posx,posy)){
				draw_vect_vel=true;
				vel.setVelX(posx);
				vel.setVelY(posy);
				glutTimerFunc(500,timerVectVel, 1);
			}

					
			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if ( x >= wancho/2 && x <= wancho && y >= walto/2 && y < walto){ 
			vcm->limpiarVista();	
			glutPostRedisplay();
		}

	}

}

/*****************************************************************************************/
void controlMovimientoMouse(int x, int y){
	
	if (y>=2 && y<=395 && x>=1 && x<=798){//dentro del vp1
		fi=y/(394*2/PI);
		tita=(x-1)*((float) PI /398.5)+PI/2;
		glutPostRedisplay();
	}
}

/*****************************************************************************************/
void onIdleFunc(int valor){
	Pelota::getInstance()->mover();
	glutPostRedisplay();
	glutTimerFunc(50,onIdleFunc, 1);
}
/*****************************************************************************************/
void cleaner(){
	std::list<Solido*>::iterator it;

	for ( it = lsolid.begin() ; it != lsolid.end(); it++ )
  		delete (*it);

}

int main(int argc, char** argv)
{
   inicializarLista();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   //glutInitWindowSize (600, 500);
   //glutInitWindowSize (600, 599); //ultimo modo funcionando
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();

   // Carga las Texturas
   //LoadTextures();
   Textura::getInstance()->cargarTexturas();

   glutMouseFunc(controlMouse);
   glutMotionFunc(controlMovimientoMouse);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   atexit(&cleaner);
   glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
   comandos();
   glutTimerFunc(600,onIdleFunc, 1);
   glutMainLoop();
   return 0;
}
