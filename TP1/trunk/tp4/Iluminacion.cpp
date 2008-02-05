// Iluminacion.cpp: implementation of the Iluminacion class.
//
//////////////////////////////////////////////////////////////////////

#include "Iluminacion.h"
#include "Declaraciones.h"

GLenum Iluminacion:: eluces[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
						  GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

#include <iostream>
#include <GL\glut.h> 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Iluminacion::Iluminacion():nroLuz(3)
{
/*	
	posicion_luz[0][0] = 0.66;
	posicion_luz[0][1] = 0.416;
	posicion_luz[0][2] = 1.0;
	posicion_luz[0][3] = 0.0;
	posicion_luz[1][0] = -0.65333;
	posicion_luz[1][1] = 0.424;
	posicion_luz[1][2] = 1.0;
	posicion_luz[1][3] = 0.0;
*/
	posicion_luz[0][0] = 0.5;
	posicion_luz[0][1] = 0.416;
	posicion_luz[0][2] = 1.0;
	posicion_luz[0][3] = 0.0;
	posicion_luz[1][0] = -0.5;
	posicion_luz[1][1] = 0.424;
	posicion_luz[1][2] = 1.0;
	posicion_luz[1][3] = 0.0;

	posicion_luz[2][0] = 0.0;
	posicion_luz[2][1] = 0.0;
	posicion_luz[2][2] = -1.0;
	posicion_luz[2][3] = 0.0;


/*
	posicion_luz[0][0] = 0.0;
	posicion_luz[0][1] = 0.0;
	posicion_luz[0][2] = 1.0;
	posicion_luz[0][3] = 0.0;
	posicion_luz[1][0] = 0.0;
	posicion_luz[1][1] = 0.9;
	posicion_luz[1][2] = -0.5;
	posicion_luz[1][3] = 0.0;
*/
}

Iluminacion::~Iluminacion(){

}

void Iluminacion:: incrementarNroLuz(){
	this->nroLuz++;
}

void Iluminacion:: luces() const{
	int div;
	
	if (nroLuz == 0) div = 1;
	else div = nroLuz;
	
	/*GLfloat ambientlight[] =	{3.0f/div ,3.0f/div,3.0f/div,3.0f};
	GLfloat difuselight[] =		{3.0f/div ,3.0f/div ,1.0f/div,3.0f};
	GLfloat specularlight[] =	{3.0f/div,3.0f/div,1.0f/div,3.0f};*/
	
	GLfloat ambientlight[] =	{0.5f ,0.5f,0.5f,1.0f};
	GLfloat difuselight[] =		{1.0f ,1.0f,1.0f,1.0f};
	GLfloat specularlight[] =	{1.0f,1.0f,1.0f,1.0f};
	glEnable(GL_LIGHTING);	    //se activa la iluminacion

	for (int i = 0; i < nroLuz; i++){
		glEnable(eluces[i]);
		glLightfv(eluces[i],GL_AMBIENT,ambientlight);
		glLightfv(eluces[i],GL_DIFFUSE,difuselight);
		glLightfv(eluces[i],GL_SPECULAR,specularlight);
		glLightfv(eluces[i],GL_POSITION,posicion_luz[i]);
		glBegin(GL_POINTS);
			glColor3ub(255,255,255);
			glVertex3d(posicion_luz[i][0], posicion_luz[i][1], posicion_luz[i][2]);
		glEnd();
	}
}

/// getters y setters
int Iluminacion:: getCantLuces() const{
	
	return this->nroLuz;
}

///---------------------------------------------------------------------
