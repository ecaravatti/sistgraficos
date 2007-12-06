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
static const int PLASTICO = 0;
static const int DIFUSO = 1;
static int material = 0; 

//luces
static int nroLuz = 0;
GLfloat posicion_luz[8][4];
GLenum luces[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
				   GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

//angulos de rotacion
float alpha = 0, beta = 0;
static int x0_rot, y0_rot;
//*-------------------------------------------------------------------*/
// Plastico rojo
const GLfloat plasticoAmb[3] = {0.0, 0.0, 0.0};
const GLfloat plasticoDif[3] = {0.5, 0.0, 0.0};
const GLfloat plasticoSpe[3] = {0.7, 0.6, 0.6};
GLfloat plasticoShi = 32.0;

// Material difuso
const GLfloat difusionAmb[4] = {0.0f,0.0f,0.0f,1.0f};
const GLfloat difusionDif[4] = {0.5f,0.0f,0.0f,1.0f};
const GLfloat difusionSpe[4] = {0.0f,0.0f,0.0f,1.0f};
GLfloat difusionShi = 1.0f;
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

/*----------------------------------------------------------------------*/
// Funciones para dibujar solidos
/*----------------------------------------------------------------------*/

/* 
 *  Para dibujar malla.
 *  Rota el punto p_in theta radianes sobre el eje Y dando como resultado p_out
 */
void rotarPunto(const double angulo, const Punto& p_in, Punto& p_out){

	//eje de revolucion y
	p_out.x = p_in.x*cos(angulo) - p_in.z*sin(angulo);
	p_out.y = p_in.y;
	p_out.z = p_in.x*sin(angulo) + p_in.z*cos(angulo);
}



void initVistaPerspecticaSombreada(int material){

	GLfloat ambientlight[] =	{0.75f ,0.75f ,0.75f ,1.0f};
	GLfloat difuselight[] =		{1.0f ,1.0f ,1.0f ,1.0f};
	GLfloat specularlight[] =	{1.0f ,1.0f ,1.0f ,1.0f};
	GLfloat lightposition[] =	{0.0f,0.0f,10.0f,0.0f};
	

	
	glEnable(GL_LIGHTING);	    //se activa la iluminacion

	for (int i = 0; i < nroLuz; i++){
		glEnable(luces[i]);
		glLightfv(luces[i],GL_AMBIENT,ambientlight);
		glLightfv(luces[i],GL_DIFFUSE,difuselight);
		glLightfv(luces[i],GL_SPECULAR,specularlight);
		glLightfv(luces[i],GL_POSITION,posicion_luz[i]);
	}
	
	glEnable(GL_COLOR_MATERIAL);	//Se activa lo materiales de color
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  //Se desean de tipo ambiente y difusión (tambien incluyen specular

	if (material == PLASTICO){
		glMaterialfv(GL_FRONT, GL_AMBIENT, plasticoAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, plasticoDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, plasticoSpe);
		glMaterialf(GL_FRONT, GL_SHININESS, plasticoShi);
	}
	else{
		glMaterialfv(GL_FRONT, GL_AMBIENT, difusionAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, difusionDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, difusionSpe);
		glMaterialf(GL_FRONT, GL_SHININESS, difusionShi);
	}
}

/// Para "desactivar" todas las fuentes de luz
void eliminarFuentes(){
	for (int i = 0; i < nroLuz; i++)
		glDisable(luces[i]);
		
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

void vistaAlambres(const Punto& r1, const Punto& r2, const Punto& r3,
				   const Punto& r4){
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_QUADS);
			glVertex3d(r1.x, r1.y, r1.z);
			glVertex3d(r2.x, r2.y, r2.z);
			glVertex3d(r4.x, r4.y, r4.z);
			glVertex3d(r3.x, r3.y, r3.z);
		glEnd();
}

void vistaSombreada(const Punto& r1, const Punto& r2, const Punto& r3,
					const Punto& r4){
	Punto normal;

	initVistaPerspecticaSombreada(material);
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

// Dibuja los solidos 
void solido(Punto* bPuntos, int nPuntos, int cantCortes)
{
	double ang, c; 
	Punto p1, p2;
	int i, j;

	c=3.14159/180.0; //grados a radianes
	
	

	Punto r1,r2,r3,r4;

		for (i=0; i< nPuntos - 1 ; i++){

		p1.x = (bPuntos[i].x + 1)/2; p1.y = bPuntos[i].y; p1.z = bPuntos[i].z;
		p2.x = (bPuntos[i+1].x + 1)/2; p2.y = bPuntos[i+1].y; p2.z = bPuntos[i+1].z;

		
		for (j=0; j<=cantCortes-1;j++){

		ang=j*360.0*c/cantCortes; //angulo de la curva a calcular
		rotarPunto(ang, p1, r1);
		rotarPunto(ang, p2, r2);

		ang=(j+1)*360.0*c/cantCortes;
		rotarPunto(ang, p1, r3);
		rotarPunto(ang, p2, r4);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

			glRotatef(alpha, 1.0f, 0.0f, 0.0f);
			glRotatef(beta, 0.0f, 1.0f, 0.0f);
		/// Vista de alambres
			viewport(wancho/2, walto/2, wancho/2, walto/2);
			vistaAlambres(r1, r2, r3, r4);

		//Vista Perspectiva Sombreada
			viewport(0, walto/2, wancho/2, walto/2);
			vistaSombreada(r1, r2, r3, r4);
		glPopMatrix();

		/// Vista de luces
		viewport(0, 0, wancho/2, walto/2);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			gluLookAt(0.5,1.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0);
			glOrtho(-2.0, 2.0, -2.0 , 2.0, -1.0, 1.0);
			vistaSombreada(r1, r2, r3, r4);
		glPopMatrix();
					
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
	nroLuz = 2;
	posicion_luz[0][0] = 0.66;
	posicion_luz[0][1] = 0.416;
	posicion_luz[0][2] = 0.0;
	posicion_luz[0][3] = 1.0;
	posicion_luz[1][0] = -0.65333;
	posicion_luz[1][1] = 0.424;
	posicion_luz[1][2] = 0.0;
	posicion_luz[1][3] = 1.0;
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

void mostrarLuces(){
	//
	glDisable(GL_LIGHTING);
	//
	viewport(0, 0, wancho/2, walto/2);
	glPointSize(3.0);
	glColor3ub(255,255,255);
	glBegin(GL_POINTS);
	for (int i = 0; i < nroLuz; i++){
		glVertex3f(posicion_luz[i][0],posicion_luz[i][1],posicion_luz[i][2]);
		
	}
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

	mostrarLuces();

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
			VistaCorteModelo::getInstancia()->guardarPunto(pto);
			glutPostRedisplay();
		}
		else if ( x >= 0 && x <= wancho/2 && y >= walto/2 && y < walto 
				  && nroLuz <= 7){
			posx = (float)(x - wancho/4)/wancho*4;
			posy = (float)(walto*3/4 - y)/walto*4;

			if (posx != posicion_luz[nroLuz-1][0] && posy != posicion_luz[nroLuz-1][1]){
			posicion_luz[nroLuz][0] = posx; 
			posicion_luz[nroLuz][1] = posy;
			posicion_luz[nroLuz][2] = 0.0;
			posicion_luz[nroLuz][3] = 1.0;
			nroLuz++;
			glutPostRedisplay();
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON & state == GLUT_DOWN){
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
				VistaCorteModelo::getInstancia()->destruir();
				exit (1);
				break;
	case 't':
	case 'T':
				if (material == PLASTICO) material = DIFUSO;
				else material = PLASTICO;
				break;
	case 'l':
	case 'L':
				eliminarFuentes();
				nroLuz = 0;
				break;
	case 'p':
	case 'P':
				VistaCorteModelo::getInstancia()->limpiarVista();
				break;
	}

	glutPostRedisplay();
}

void uso(){
	cout<<"Presione t...Para cambiar textura "<<endl;
	cout<<"Presione l...Para eliminar todas las luces"<<endl;
	cout<<"Presione p...Para eliminar todos los puntos de control"<<endl;
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
