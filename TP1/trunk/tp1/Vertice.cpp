// Vertice.cpp: implementation of the Vertice class.
//
//////////////////////////////////////////////////////////////////////

#include "Vertice.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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

Vertice::dibujar(int coorX, int coorY){
	glVertex2i(coorX,coorY);	
}

//////////////////////////////////////////////////////////////////////
// Otros m�todos
//////////////////////////////////////////////////////////////////////
Vertice::dibujar()
{
	glVertex2i(x,y);
}

int Vertice::distancia(Vertice v)
{
	float difx = abs(getX()-v.getX());
	float dify = abs(getY()-v.getY());
	return (int)(sqrt(difx*difx + dify*dify));

}


