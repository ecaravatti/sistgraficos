// Solido.cpp: implementation of the Solido class.
//
//////////////////////////////////////////////////////////////////////

#include "Solido.h"
#include <cmath>
#include <GL\glut.h> 

#ifndef NULL
#define NULL 0
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Solido::Solido():cantCortes(0),
				 alpha(0),
				 beta(0),
				 iluminacion(NULL)
{

}

Solido::~Solido()
{

}

// Dibuja los solidos 
void Solido:: solido(Punto* bPuntos, int nPuntos,
					 int wancho, int walto){
	double ang, c; 
	Punto p1, p2;
	int i, j;

	c=3.14159/180.0; //grados a radianes
	
	

	Punto r1,r2,r3,r4;

		for (i=1; i< nPuntos - 1 ; i++){

		p1.x = (bPuntos[i-1].x + 1)/2; p1.y = bPuntos[i-1].y; p1.z = bPuntos[i-1].z;
		p2.x = (bPuntos[i+1].x + 1)/2; p2.y = bPuntos[i+1].y; p2.z = bPuntos[i+1].z;

		
		for (j=0; j<=cantCortes-1;j++){

		ang=j*360.0*c/cantCortes; //angulo de la curva a calcular
		rotarPunto(ang, p1, r1);
		rotarPunto(ang, p2, r2);

		ang=(j+1)*360.0*c/cantCortes;
		rotarPunto(ang, p1, r3);
		rotarPunto(ang, p2, r4);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
				gluPerspective( 45 ,		// Ángulo de visión
				(float)walto/(float)wancho, // Razón entre el largo y el ancho, para calcular la perspectiva
				1,					    // Cuan cerca se puede ver
				2000);	
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
			gluLookAt(0.0,0.0,3.0,
					  0.0,0.0,-1.0,
					  -0.2,0.5,-0.2);
			glRotatef(alpha, 1.0f, 0.0f, 0.0f);
			glRotatef(beta, 0.0f, 1.0f, 0.0f);

		/// Vista de alambres
			viewport(wancho/2, walto/2, wancho/2, walto/2);
			vistaAlambres(r1, r2, r3, r4);

		//Vista Perspectiva Sombreada
			viewport(0, walto/2, wancho/2, walto/2);
			vistaSombreada(r1, r2, r3, r4);

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		/// Vista de luces
		viewport(0, 0, wancho/2, walto/2);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(0.0,1.0,0.0,
					  0.0,-1.0,0.0,
					  0.0,0.0,1.0);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glOrtho(-2.0, 2.0, -2.0 , 2.0, -1.0, 1.0);
			vistaSombreada(r1, r2, r3, r4);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
					
		}
	}

}

void Solido:: setCantCortes(int nueva){
	this->cantCortes = nueva;
}

void Solido:: setIluminacion(Iluminacion* iluminacion){
	this->iluminacion = iluminacion;
}

void Solido:: setAngulo(int _alpha, int _beta){
	this->alpha = _alpha;
	this->beta = _beta;
}
///----------------------------------------------------------------------
/// Metodos privados
void Solido:: rotarPunto(const double angulo, const Punto& p_in, Punto& p_out){

	//eje de revolucion y
	p_out.x = p_in.x*cos(angulo) - p_in.z*sin(angulo);
	p_out.y = p_in.y;
	p_out.z = p_in.x*sin(angulo) + p_in.z*cos(angulo);
}

void Solido:: normalizar(Punto& normal){
	double norm;

	norm = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
	normal.x = normal.x / norm;
	normal.y = normal.y / norm;
	normal.z = normal.z / norm;
}

//Calcula el producto vectorial de dos vectores
void Solido:: calcularNormal(const Punto &v1, const Punto &v2, const Punto &v3, Punto& normal){
	double Qx, Qy, Qz, Px, Py, Pz;

	Px = v2.x-v1.x;
	Py = v2.y-v1.y;
	Pz = v2.z-v1.z;
	Qx = v3.x-v1.x;
	Qy = v3.y-v1.y;
	Qz = v3.z-v1.z;
	normal.x = Py*Qz - Pz*Qy;
	normal.y = Pz*Qx - Px*Qz;
	normal.z = Px*Qy - Py*Qx;
	this->normalizar(normal);

}

void Solido:: vistaAlambres(const Punto& r1, const Punto& r2, const Punto& r3,
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

void Solido:: vistaSombreada(const Punto& r1, const Punto& r2, const Punto& r3,
						     const Punto& r4){
	Punto normal;

	iluminacion->luces();
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