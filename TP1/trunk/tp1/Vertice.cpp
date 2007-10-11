// Vertice.cpp: implementaci�n de la clase Vertice.
//
//////////////////////////////////////////////////////////////////////

#include "Vertice.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construcci�n/Destrucci�n
//////////////////////////////////////////////////////////////////////
Vertice::Vertice(const Vertice &vertice){
	this->x=vertice.getX();
	this->y=vertice.getY();
}

Vertice::Vertice(int coordX, int coordY)
{
	x = coordX;
	y = coordY;
}

Vertice::Vertice()
{
	x = 0;
	y = 0;
}

Vertice::~Vertice()
{

}

//////////////////////////////////////////////////////////////////////
// Getters y Setters
//////////////////////////////////////////////////////////////////////

int Vertice::getX() const
{
	return x;
}

int Vertice::getY() const
{
	return y;
}

void Vertice::setX(int coordX)
{
	x = coordX;
}

void Vertice::setY(int coordY)
{
	y = coordY;
}

void Vertice::set(int coorX, int coorY)
{
	this->x = coorX;
	this->y = coorY;
}

//////////////////////////////////////////////////////////////////////
// Otros m�todos
//////////////////////////////////////////////////////////////////////

// Dibuja un v�rtice en la posici�n (coorX,coorY).
Vertice::dibujar(int coorX, int coorY){
	glVertex2i(coorX,coorY);	
}

// Dibuja el v�rtice.
Vertice::dibujar()
{
	glVertex2i(x,y);
}

// Calcula la distancia con el v�rtice v.
int Vertice::distancia(Vertice v)
{
	float difx = abs(getX()-v.getX());
	float dify = abs(getY()-v.getY());
	return (int)(sqrt(difx*difx + dify*dify));

}


