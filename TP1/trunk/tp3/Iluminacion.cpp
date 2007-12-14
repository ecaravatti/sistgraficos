// Iluminacion.cpp: implementation of the Iluminacion class.
//
//////////////////////////////////////////////////////////////////////

#include "Iluminacion.h"
#include "Declaraciones.h"

GLenum Iluminacion:: eluces[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
						  GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

#include <iostream>
//////////////////////////////////////////////////////////////////////
const int Iluminacion:: PLASTICO = 0;
const int Iluminacion:: DIFUSO = 1;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Iluminacion::Iluminacion():nroLuz(2), material(PLASTICO)
{

	//nroLuz = 2;
	posicion_luz[0][0] = 0.66;
	posicion_luz[0][1] = 0.416;
	posicion_luz[0][2] = 1.0;
	posicion_luz[0][3] = 1.0;
	posicion_luz[1][0] = -0.65333;
	posicion_luz[1][1] = 0.424;
	posicion_luz[1][2] = 1.0;
	posicion_luz[1][3] = 1.0;
}

Iluminacion::~Iluminacion(){

}

void Iluminacion:: incrementarNroLuz(){
	this->nroLuz++;
}

bool Iluminacion:: agregarLuz(float x, float y){
	
	if (x != posicion_luz[nroLuz-1][0] && y != posicion_luz[nroLuz-1][1]){
		posicion_luz[nroLuz][0] = x; 
		posicion_luz[nroLuz][1] = y;
		posicion_luz[nroLuz][2] = 1.0;
		posicion_luz[nroLuz][3] = 1.0;
		this->incrementarNroLuz();
		return true;
	}
	return false;
}

void Iluminacion:: mostrarLuces(){
	
	glDisable(GL_LIGHTING);
	glPointSize(3.0);
	glColor3ub(255,255,255);
	glBegin(GL_POINTS);
	for (int i = 0; i < nroLuz; i++)
		glVertex3f(posicion_luz[i][0],posicion_luz[i][1],0);
	
	glEnd();
}

void Iluminacion:: luces() const{
	int div;
	
	if (nroLuz == 0) div = 1;
	else div = nroLuz;
	
	GLfloat ambientlight[] =	{3.0f/div ,3.0f/div,3.0f/div,3.0f};
	GLfloat difuselight[] =		{3.0f/div ,3.0f/div ,1.0f/div,3.0f};
	GLfloat specularlight[] =	{3.0f/div,3.0f/div,1.0f/div,3.0f};
	
	
	glEnable(GL_LIGHTING);	    //se activa la iluminacion

	for (int i = 0; i < nroLuz; i++){
		glEnable(eluces[i]);
		glLightfv(eluces[i],GL_AMBIENT,ambientlight);
		glLightfv(eluces[i],GL_DIFFUSE,difuselight);
		glLightfv(eluces[i],GL_SPECULAR,specularlight);
		glLightfv(eluces[i],GL_POSITION,posicion_luz[i]);
	}
	
	glEnable(GL_COLOR_MATERIAL);	//Se activa lo materiales de color
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  //tipo ambiente y difusión (tambien incluyen specular)

	if (material == PLASTICO){
		this->plastico();
	}
	else{
		this->difuso();
	}
}

void Iluminacion:: eliminarFuentes(){
	for (int i = 0; i < nroLuz; i++)
		glDisable(eluces[i]);

	this->nroLuz = 0;
		
}

/// getters y setters
int Iluminacion:: getCantLuces() const{
	
	return this->nroLuz;
}

int Iluminacion:: getMaterial(){
	return this->material;
}

void Iluminacion:: setMaterial(int nuevo){
	this->material = nuevo;
}
///---------------------------------------------------------------------
/// Metodos privados
void Iluminacion:: plastico() const{
	GLfloat plasticoAmb[3] = {0.0, 0.0, 0.0};
	GLfloat  plasticoDif[3] = {0.1,0.35, 0.1};
	GLfloat plasticoSpe[3] = {0.45, 0.55, 0.45};
	GLfloat plasticoShi = 32.0;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, plasticoAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, plasticoDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, plasticoSpe);
	glMaterialf(GL_FRONT, GL_SHININESS, plasticoShi);
}

void Iluminacion::  difuso() const{
	GLfloat difusionAmb[4] = {0.0f,0.0f,0.0f,1.0f};
	GLfloat difusionDif[4] = {1.0f,0.0f,0.0f,1.0f};
	GLfloat difusionSpe[4] = {0.0f,0.0f,0.0f,1.0f};
	GLfloat difusionShi = 1.0f;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, difusionAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusionDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, difusionSpe);
	glMaterialf(GL_FRONT, GL_SHININESS, difusionShi);
}