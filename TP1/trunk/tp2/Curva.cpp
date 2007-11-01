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

Curva::Curva(Punto* _bPtos, int _res, int _cantPtos, int _d,
			 const Color& _color0, const Color& _color1, float _grosor):
												bPtos(_bPtos),
												res(_res),
												cPtos(_cantPtos),
												d(_d),
												color0(_color0),
												color1(_color1),
												grosor(_grosor)
{	
}

Curva:: Curva(int _res, int _d, const Color &_color0, const Color &_color1):
												bPtos(NULL),
												res(_res),
												cPtos(0),
												d(_d),
												color0(_color0),
												color1(_color1),
												grosor(0)

{
}

Curva::~Curva()
{
}

void Curva:: dibujarBSpline(){
	Punto pto;
	Color colorPto;

	glLineWidth(this->grosor);
	glColor3ub(color0.r,color0.g,color0.b);
	glBegin(GL_LINE_STRIP);

	// dibujar la curva
    for (int i =1; i < this->cPtos ; i++) {
      for (int j = 1; j <= this->d; j++) {
			this->calcularPunto(i,j/(float)this->d, pto);
			this->calcularColor(pto.x, colorPto);
			glColor3ub(colorPto.r,colorPto.g,colorPto.b);
			glVertex2i(pto.x,pto.y);
      }
    }
    glEnd();
}

/// getters y setters
void Curva:: setCantPtos(int nuevaCant){
	this->cPtos = nuevaCant;
}

void Curva:: setGrosor(float nuevo){
	this->grosor = nuevo;
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

void Curva:: calcularColor(int posX, Color& color){
	color.r = this->color0.r*( res - posX )/res +  this->color1.r * posX/res;
	color.g = this->color0.g*( res - posX )/res +  this->color1.g * posX/res;
	color.b = this->color0.b*( res - posX )/res +  this->color1.b * posX/res;
}

