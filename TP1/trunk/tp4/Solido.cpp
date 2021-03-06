// Solido.cpp: implementation of the Solido class.
//
//////////////////////////////////////////////////////////////////////

#include "Solido.h"
#include "textura.h"
#include "Material.h"
#include <cmath>
#include <GL\glut.h> 
//
#include <iostream>
#ifndef NULL
#define NULL 0
#endif

bool Solido::vista=true;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*****************************************************************************************/

Solido::Solido(float posx, float posy,std::vector<Punto*> bPuntos,int nroMat,int nroTex)
{	
	this->posicion.x=posx;
	this->posicion.y=posy;
	this->puntos=bPuntos;
	this->diametro=calcularDiametro();
	this->calcularNormales();
	this->nroMat=nroMat;
	this->nroTex=nroTex;
	DLSombreado=0;
	DLAlambre=0;
	lcreadas=false;
}

/*****************************************************************************************/

Solido::~Solido()
{
	std::vector<Punto*>::iterator it;
	for (it=puntos.begin(); it!=puntos.end(); it++)
		delete (*it);
	puntos.clear();
	for (it=normales.begin(); it!=normales.end(); it++)
		delete (*it);
	normales.clear();

}

/*****************************************************************************************/

void Solido::setPosicion(float posx,float posy,float posz){
	this->posicion.x=posx;
	this->posicion.y=posy;
	this->posicion.z=posz;
}

/*****************************************************************************************/

void Solido::crearListas(){
	DLAlambre=glGenLists(1);
	DLSombreado=glGenLists(1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glNewList(DLAlambre,GL_COMPILE);

		dibujar_solido(ALAMBRE);

	glEndList();

	glNewList(DLSombreado,GL_COMPILE);

		Material::getInstance()->activar();
		Material::getInstance()->setMat(this->nroMat);

		Textura::getInstance()->activar();
		Textura::getInstance()->setTex(this->nroTex);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		dibujar_solido(SOMBREADO);

		Textura::getInstance()->desactivar();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

	glEndList();
	glPopMatrix();
	lcreadas=true;
}

/*****************************************************************************************/

void Solido::dibujar(){
	if (!lcreadas)
		crearListas();	

	glPushMatrix();
		if (Solido::vista==true)
				glCallList(DLSombreado);
		else
				glCallList(DLAlambre);
	
	glPopMatrix();
}

/*****************************************************************************************/

//Metodo q dibuja al solido
void Solido::dibujar_solido(int modo){

	double ang, c; 
	Punto p1, p2, r1,r2,r3,r4, n1, n2, n3, n4;
	int i, j;

	c=3.14159/180.0; //grados a radianes
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(this->posicion.x,this->posicion.y,this->posicion.z);
		glTranslatef(0.0,0.0,1.0);
		glRotatef((GLfloat) 90, 1.0, 0.0, 0.0);
		
		for (i=0; i< puntos.size() - 1 ; i++){

			p1.x = (puntos[i]->x + 1)/2;
			p1.y = puntos[i]->y; 
			p1.z = puntos[i]->z;

			p2.x = (puntos[i+1]->x + 1)/2; 
			p2.y = puntos[i+1]->y; 
			p2.z = puntos[i+1]->z;
		
			for (j=0; j<=cantCortes-1;j++){

				ang=j*360.0*c/cantCortes; //angulo de la curva a calcular
				rotarPunto(ang, p1, r1);
				rotarPunto(ang, *(normales[i]), n1);
				rotarPunto(ang, p2, r2);
				rotarPunto(ang, *(normales[i+1]), n2);

				ang=(j+1)*360.0*c/cantCortes;
				rotarPunto(ang, p1, r3);
				rotarPunto(ang, *(normales[i]), n3);
				rotarPunto(ang, p2, r4);
				rotarPunto(ang, *(normales[i+1]), n4);

				//vista sombreada o alambre segun seleccion
				if (modo==SOMBREADO)
					vistaSombreada(r1, r2, r3, r4, n1, n2, n3, n4);
				else
					vistaAlambres(r1,r2,r3,r4);
	
			}
		}
	glPopMatrix();

}

/*****************************************************************************************/

void Solido:: setCantCortes(int nueva){
	this->cantCortes = nueva;
}

/*****************************************************************************************/

/// Metodos privados
void Solido:: rotarPunto(const double angulo, const Punto& p_in, Punto& p_out){

	//eje de revolucion y
	p_out.x = p_in.x*cos(angulo) - p_in.z*sin(angulo);
	p_out.y = p_in.y;
	p_out.z = (p_in.x*sin(angulo) + p_in.z*cos(angulo));
}

/*****************************************************************************************/

void Solido:: normalizar(Punto& normal){
	double norm;

	norm = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
	normal.x = normal.x / norm;
	normal.y = normal.y / norm;
	normal.z = normal.z / norm;
}

/*****************************************************************************************/

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

/*****************************************************************************************/

void Solido::vistaAlambres(const Punto& r1, const Punto& r2, const Punto& r3,
				   const Punto& r4){
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_QUADS);
			glVertex3d(r1.x, r1.y, r1.z);
			glVertex3d(r2.x, r2.y, r2.z);
			glVertex3d(r4.x, r4.y, r4.z);
			glVertex3d(r3.x, r3.y, r3.z);
		glEnd();
	glEnable(GL_LIGHTING);
}

/*****************************************************************************************/

void Solido:: vistaSombreada(const Punto& r1, const Punto& r2,
							 const Punto& r3, const Punto& r4,
							 const Punto& n1, const Punto& n2,
							 const Punto& n3, const Punto& n4){
	glEnable(GL_LIGHTING);
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);

			glNormal3f(n1.x, n1.y, n1.z);
			glTexCoord2d(0.0, 0.0); glVertex3f(r1.x, r1.y, r1.z);
			glNormal3f(n2.x, n2.y, n2.z);
			glTexCoord2d(0.0, 1.0); glVertex3f(r2.x, r2.y, r2.z);
			glNormal3f(n3.x, n3.y, n3.z);
			glTexCoord2d(1.0, 0.5); glVertex3f(r3.x, r3.y, r3.z);

			
			glNormal3f(n2.x, n2.y, n2.z);
			glTexCoord2d(0.0, 0.0); glVertex3f(r2.x, r2.y, r2.z);
			glNormal3f(n3.x, n3.y, n3.z);
			glTexCoord2d(0.0, 1.0); glVertex3f(r3.x, r3.y, r3.z);
			glNormal3f(n4.x, n4.y, n4.z);
			glTexCoord2d(1.0, 0.5); glVertex3f(r4.x, r4.y, r4.z);
	
	
	
	glEnd();
}

/*****************************************************************************************/

//Calcula las normales de la superficie del solido
void Solido::calcularNormales(){

	double dery, mag;
	Punto* normal;

	for(int i = 0; i < puntos.size(); i++) {
		if (i == 0) 
			dery = (puntos[i+1]->y - puntos[i]->y)/0.1;
		else if (i == puntos.size()-1) 
			dery = (puntos[i]->y - puntos[i-1]->y)/0.1;
		
 		else   
			dery = (puntos[i+1]->y - puntos[i-1]->y)/(2*0.1);
		
		mag = sqrt(1.0+dery*dery);

		normal=new Punto();
		normal->y=-dery/mag;
		normal->x=1.0/mag;
		normal->z=0.0;
		normales.push_back(normal);
	}
}

/*****************************************************************************************/

//Calcula el Diametro del Solido
float Solido::calcularDiametro(){
	Punto* punto;
	double ndist=0,distmax=0;
	for (int i=0; i<puntos.size(); i++){
		punto=puntos[i];
		ndist=sqrt(pow(punto->x+1,2));
		if (ndist>distmax) distmax=ndist;
	}

	return (distmax*0.96);

}
/*****************************************************************************************/
//sobrecarga static
float Solido::calcularDiametro(std::vector<Punto*> &vector){
	Punto *punto;
	double ndist=0,distmax=0;

	for (int i=0; i<vector.size(); i++){
		punto=vector[i];
		ndist=sqrt(pow(punto->x+1,2));
		if (ndist>distmax) distmax=ndist;
	}

	return (distmax*0.96);
}

/*****************************************************************************************/
Punto Solido::getPosicion() const{
	return posicion;
}

/*****************************************************************************************/

float Solido::getDiametro() const{
	return diametro;
}
/*****************************************************************************************/
