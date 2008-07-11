// urva.cpp: implementation of the Curva class.
//
//////////////////////////////////////////////////////////////////////

#include "Curva.h"
#include <cmath>
#include <GL\glut.h>
#include "Declaraciones.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Curva::Curva(Punto* _bPtos, int _cantPtos, int _d):
												bPtosControl(_bPtos),
												bPtosDiscret(NULL),
												cPtos(_cantPtos),
												d(_d)
{	
}

Curva::Curva(int _d):
					bPtosControl(NULL),
					bPtosDiscret(NULL),
					cPtos(0),
					d(_d)
{}
					
Curva::~Curva()
{
	delete [] this->bPtosDiscret;
}

void Curva:: discretizarCurva(){
	Punto pto;
	int k = 0;
	this->iniBufferPtosDiscret(this->cPtos, this->d);
	// calcular todos los puntos
    for (int i =1; i < this->cPtos ; i++) {
      for (int j = 1; j <= this->d; j++) {
			this->calcularPunto(i,j/(float)this->d, pto);
			this->bPtosDiscret[k] = pto;
			k++;
      }
    }
    
}

void Curva:: dibujarBSpline() const{
	
	glBegin(GL_LINE_STRIP);
		// dibujar la curva
		for (int k = 0; k < this->getCantPtosDisc(); k++) 
			glVertex3f(this->bPtosDiscret[k].x, this->bPtosDiscret[k].y,this->bPtosDiscret[k].z);
	glEnd();
}

/// getters y setters
void Curva:: setCantPtos(int nuevaCant){
	this->cPtos = nuevaCant;
}

void Curva:: setPuntos(Punto* nuevo){
	this->bPtosControl = nuevo;
}

int Curva:: getCantPtosDisc() const{
	return (this->cPtos-1)*this->d;
}

Punto* Curva:: getBufferPtosDisc() const{
	return this->bPtosDiscret;
}

/*--------------------------------------------------------------------*/
// Metodos Privados
void Curva:: iniBufferPtosDiscret(int cPtos, int d){
	if (this->bPtosDiscret != NULL) delete [] this->bPtosDiscret;
	this->bPtosDiscret = new Punto[(cPtos-1)*d];
}

void Curva:: calcularPunto(int i, float u, Punto& p) {
	
	int indice;
	float x = 0, y = 0, z = 0;
	p.x = 0; p.y = 0; p.z = 0;

    for (int j = -2; j<=1; j++){
	  indice = i + j;
	  //Condicion para q la curva empiece en el primer pto
	  if (i == 1){ 
		  if (j != 1) indice = 0;
		  else indice = 1;
	  }
	  //cond. para q termine en el ultimo pto
	  else if (i == this->cPtos - 1){
		  if (j == -2) indice = this->cPtos - 2;
		  else indice = this->cPtos - 1;
	  }

      p.x += base(j,u)*this->bPtosControl[indice].x;
      p.y += base(j,u)*this->bPtosControl[indice].y;
    }
}

float Curva:: base(int i, float u) {
    switch (i) {
    case -2:
      return (((-u+3)*u-3)*u+1)/6;
    case -1:
      return (((3*u-6)*u)*u+4)/6;
    case 0:
      return (((-3*u+3)*u+3)*u+1)/6;
    case 1:
      return (u*u*u)/6;
    }
    return 0; // Solo se llega acá si se especifica una i inválida.
}

