// Segmento.cpp: implementación de la clase Segmento.
//
//////////////////////////////////////////////////////////////////////

#include "Segmento.h"
#include <cstdlib>
#include <cmath>
//////////////////////////////////////////////////////////////////////
// Construcción/Destrucción
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
// Otros métodos
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

// Dibuja el segmento utilizando el algortimo de Bresenham.
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
	
	if ((m <= 1 && m >= 0) || (m >= -1 && m <= 0)) 
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

bool Segmento:: evaluarPQ(float p, float q, float &u1, float &u2){
	float r ;
	bool ret = true;
	if (p < 0.0) {
		r = q/p;
		if (r > u2)
			ret = false;
		else if (r > u1 )
			u1 = r;
	}
	else if (p > 0.00){
			r = q/p ;
		if ( r < u1 )
			ret = false;
		else if (r < u2)
			u2 = r;
	}
	else if (q < 0.0) //p == 0 paralela y q < 0 la linea esta fuera de la ventana
			ret = false;

	return  ret;
}

bool Segmento:: clipping(int wxmin, int wxmax, int wymin, int wymax){
	
	float u1 = 0.0, u2 = 1.0, dx = this->ptoFin->getX() - this->ptoInicio->getX(),
		  dy = this->ptoFin->getY() - this->ptoInicio->getY(), p, q;
	
	//cargo p1 q1 (vent lado izq)
	p = -dx;
	q = this->ptoInicio->getX() - wxmin;
	if ( evaluarPQ(p, q, u1, u2) ){
		//cargo p2 q2 (vent lado der)
		p = dx;
		q = wxmax - this->ptoInicio->getX();
		if ( evaluarPQ(p, q, u1, u2) ){
			//cargo p3 q3 (vent lim inf)
			p = -dy;
			q = this->ptoInicio->getY() - wymin;
			if ( evaluarPQ(p, q, u1, u2) ){
				// cargo p4 q4 (vent lim sup)
				p = dy;
				q = wymax - this->ptoInicio->getY();
				if ( evaluarPQ(p, q, u1, u2) ){
					if (u2 < 1.0){
					//actualizo punto final del segmento
						this->ptoFin->setX( floor (this->ptoInicio->getX() + u2 * dx + 0.5));
						this->ptoFin->setY( floor (this->ptoInicio->getY() + u2 * dy + 0.5));
					}
					if (u1 > 0.0){
					//actualizo punto inicial del segmento
						this->ptoInicio->setX( floor(this->ptoInicio->getX() + u1 * dx + 0.5));
						this->ptoInicio->setY( floor(this->ptoInicio->getY() + u1 * dy + 0.5));
					}
				return true;
				}
			}
		}

	}
	return false;
}
