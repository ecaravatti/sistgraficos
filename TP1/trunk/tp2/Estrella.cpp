// Estrella.cpp: implementation of the Estrella class.
//
//////////////////////////////////////////////////////////////////////

#include "Estrella.h"
#include <GL\glut.h>
#include <cmath>
#include <cstdlib>
#include "Curva.h"
#include "GeneradorPtos.h"

#define RAD 57.2957795135

const int Estrella:: maxTramos = 5;
const int Estrella:: maxGrosor = 500;
const int Estrella:: pasos = 20;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Estrella::Estrella(int _x, int _y, int _rMin, int _rMax, int _Nr, 
				   Color _color0, Color _color1):					
							x(_x),
							y(_y),
							rMin(_rMin),
							rMax(_rMax),
							Nr(_Nr),
							color0(_color0),
							color1(_color1)
{
	this->ptosRayos = new Punto[Nr];
	this->angRayos = new int[Nr];
	this->ptosCurvas = new Punto*[Nr];
}

Estrella::~Estrella()
{
	delete [] this->ptosRayos;
	delete [] this->angRayos;
	for (int i = 0; i < this->Nr; i++)
		delete [] ptosCurvas[i];
	delete [] ptosCurvas;
}

void Estrella:: dibujar(){
	Curva* curva = new Curva(GeneradorPtos::res, this->pasos, this->color0, this->color1);
	
	// Genera los puntos donde se ubica cada rayo
	this->generarRayos();
	
	// Dibuja el circulo relleno con radio minimo
	this->circuloRelleno(this->rMin, this->color0);

	for (int i = 0; i < this->Nr; i++){
		// Genera todos los puntos para dibujar rayo i
		this->generarPuntos(curva, i);	
		glPushMatrix();
			glTranslatef( (GLfloat)this->ptosRayos[i].x, (GLfloat)this->ptosRayos[i].y, 0.0);
			glRotatef((GLfloat)(this->angRayos[i]), 0.0,0.0,1.0);
			glScalef( (GLfloat) (this->rMax - this->rMin)/GeneradorPtos::res, 1.0,1.0 );
			curva->dibujarBSpline();
		glPopMatrix();
	}
	

}

/*--------------------------------------------------------------------*/
// Metodos privados
void Estrella:: circuloRelleno(int radio, Color color){
	float angRad;
	int paso = 5;

	glColor3ub(color.r,color.g,color.b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(this->x, this->y);

	for (int angulo = 0; angulo <= 360; angulo += paso){
		angRad = angulo/RAD;
		glVertex2f( this->x + sin(angRad) * radio, this->y + cos(angRad) * radio);
	}
	glEnd();
}

void Estrella:: generarRayos(){
	int rangoAng, i = 0, ang = 0;
	float angRad;
	rangoAng = 360/this->Nr;

	while (i < this->Nr){
		// Genero angulo
		ang = ang + rangoAng;
		angRad = ang/RAD;
		// Guardo el angulo y los puntos
		this->angRayos[i] = ang;
		this->ptosRayos[i].x = this->x + this->rMin*cos(angRad);
		this->ptosRayos[i].y = this->y + this->rMin*sin(angRad);
		this->ptosRayos[i].z = 1;
		i++;
	}
}

void Estrella:: generarPuntos(Curva* curva, int i){
	int cantTramos;
	cantTramos = rand() % maxTramos + 1;
	GeneradorPtos gp(cantTramos);
	gp.generarPtos();
	this->ptosCurvas[i] = gp.getPuntos();
	curva->setCantPtos(gp.getCantPtos());
	curva->setGrosor(this->generarGrosor());
	curva->setPuntos(gp.getPuntos());
}

float Estrella:: generarGrosor(){
	int ran = rand() % 500 + 101;
	return (float)ran / 100;
}