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
												bPtos(_bPtos),
												cPtos(_cantPtos),
												d(_d)
{	
}


Curva::~Curva()
{
}

void Curva:: dibujarBSpline(){
	Punto pto;

	glBegin(GL_LINE_STRIP);

	// dibujar la curva
    for (int i =1; i < this->cPtos ; i++) {
      for (int j = 1; j <= this->d; j++) {
			this->calcularPunto(i,j/(float)this->d, pto);
			glVertex2i(pto.x,pto.y);
      }
    }
    glEnd();
}

/// getters y setters
void Curva:: setCantPtos(int nuevaCant){
	this->cPtos = nuevaCant;
}

void Curva:: setPuntos(Punto* nuevo){
	this->bPtos = nuevo;
}


/*--------------------------------------------------------------------*/
// Metodos Privados
void Curva:: calcularPunto(int i, float u, Punto& p) {
	
	int indice;
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

      p.x += base(j,u)*this->bPtos[indice].x;
      p.y += base(j,u)*this->bPtos[indice].y;
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

