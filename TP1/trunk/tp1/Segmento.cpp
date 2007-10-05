// Segmento.cpp: implementation of the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#include "Segmento.h"
#include <cstdlib>
#include <cmath>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Segmento::Segmento()
{
}

Segmento::Segmento(Vertice* v1,Vertice* v2)
{
	ptoInicio = v1;
	ptoFin = v2;
}

Segmento::~Segmento()
{
	delete ptoInicio;
	delete ptoFin;
}

//////////////////////////////////////////////////////////////////////
// Getters y setters
//////////////////////////////////////////////////////////////////////


Vertice* Segmento::getPtoFin()
{
	return (ptoFin);
}

Vertice* Segmento::getPtoInicio()
{
	return (ptoInicio);
}

void Segmento::setPtoFin(Vertice v)
{
	*ptoFin = v;
}

void Segmento::setPtoInicio(Vertice v)
{
	*ptoInicio = v;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// Dibuja rectas con abs(m) < 1
void Segmento:: dibujar_Mod_Menor_1(Vertice* vInicial, Vertice* vFinal, 
									bool cEje, int inc){
  int x, y, xend, p, iy, iyx, dx, dy;
  Vertice v;

  dx = abs(vInicial->getX() - vFinal->getX());
  dy = abs(vInicial->getY() - vFinal->getY());

  if ( vInicial->getX() > vFinal->getX() ) {
 	x = vFinal->getX();
	y = vFinal->getY();
	xend = vInicial->getX(); 
  }
  else {
	x = vInicial->getX();
	y = vInicial->getY();
	xend = vFinal->getX();
  }

  p = 2*dy - dx;
  iy = 2*dy;
  iyx = 2*(dy-dx);

	
	
  while (x <= xend){

	if (!cEje) v.set(x,y);
	else v.set(y,x);
	
	v.dibujar();

	x = x + 1;
	if (p < 0)
		p = p + iy;
	else {
		y = y + inc;
		p = p + iyx;
	}
  }
}

void Segmento:: dibujarBresenham()
{
  int dx, dy, cont, ini, fin, inc = 1;
  Vertice v1, v2;
  float m = 0;

	dx = (this->getPtoFin()->getX() - this->getPtoInicio()->getX());
	dy = (this->getPtoFin()->getY() - this->getPtoInicio()->getY());

  if (dx != 0){
	m = (float)dy/(float)dx;

	if (m < 0) inc = -1;
	
	if (abs(m) <= 1) 
		dibujar_Mod_Menor_1(this->getPtoInicio(), this->getPtoFin(), false,
							inc);
	else{
		//cambio ejes
		v1.set(this->getPtoInicio()->getY(), this->getPtoInicio()->getX());
		v2.set(this->getPtoFin()->getY(), this->getPtoFin()->getX());
		dibujar_Mod_Menor_1(&v1, &v2, true, inc);
	}
  }
  else if ( dx == 0)
  {
	  //Ver esto
	  if (this->getPtoInicio()->getY() > this->getPtoFin()->getY() ){
			ini = this->getPtoFin()->getY();
			fin = this->getPtoInicio()->getY();
	  }
	  else{
			ini = this->getPtoInicio()->getY();
			fin = this->getPtoFin()->getY();
	  }
	  for (cont = ini; cont < fin; cont++){
			v1.set(this->getPtoInicio()->getX(),cont);
			v1.dibujar();
	  }
  }
  
}
