// Iluminacion.cpp: implementation of the Iluminacion class.
//
//////////////////////////////////////////////////////////////////////

#include "Iluminacion.h"
#include "Declaraciones.h"
#include <GL\glut.h> 

GLenum Iluminacion:: eluces[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
						  GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Iluminacion* Iluminacion::instance=NULL;

Iluminacion::Iluminacion()
{

	posicion_luz[0][0] = 0.0f;
	posicion_luz[0][1] = 0.0f;
	posicion_luz[0][2] = 1.0f;
	posicion_luz[0][3] = 1.0f;
	
	posicion_luz[1][0] = 1.5f;
	posicion_luz[1][1] = 0.0f;
	posicion_luz[1][2] = 1.0f;
	posicion_luz[1][3] = 1.0f;
	
	posicion_luz[2][0] = 0.0f;
	posicion_luz[2][1] = 2.0f;
	posicion_luz[2][2] = 1.0f;
	posicion_luz[2][3] = 1.0f;
	
	posicion_luz[3][0] = 1.5f;
	posicion_luz[3][1] = 2.0f;
	posicion_luz[3][2] = 1.0f;
	posicion_luz[3][3] = 1.0f;

}
/*****************************************************************************************/
Iluminacion::~Iluminacion(){

}
/*****************************************************************************************/
void Iluminacion::encender_luces() const{
	
	GLfloat ambientlight[] =	{0.5f ,0.5f,0.5f,1.0f};
	GLfloat difuselight[] =		{1.0f ,1.0f,1.0f,1.0f};
	GLfloat specularlight[] =	{1.0f,1.0f,1.0f,1.0f};
	
	/*
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
		for (int i=0; i<4;i++)
			glVertex3f(posicion_luz[i][0], posicion_luz[i][1], posicion_luz[i][2]);
	glEnd();
	*/
	glEnable(GL_LIGHTING);	    //se activa la iluminacion

	for ( int i = 0; i < 4; i++){
		glEnable(eluces[i]);
		glLightfv(eluces[i],GL_AMBIENT,ambientlight);
		glLightfv(eluces[i],GL_DIFFUSE,difuselight);
		glLightfv(eluces[i],GL_SPECULAR,specularlight);
		glLightfv(eluces[i],GL_POSITION,posicion_luz[i]);
		glColor3ub(130,170,200);
	}
}

/*****************************************************************************************/
void Iluminacion::apagar_luces(){
	glDisable(GL_LIGHTING);
}

/*****************************************************************************************/