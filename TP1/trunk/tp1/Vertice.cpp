// Vertice.cpp: implementación de la clase Vertice.
//
//////////////////////////////////////////////////////////////////////

#include "Vertice.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construcción/Destrucción
//////////////////////////////////////////////////////////////////////
Vertice::Vertice(const Vertice &vertice){
	this->x=vertice.getX();
	this->y=vertice.getY();
	this->clip = true;
}

Vertice::Vertice(int coordX, int coordY)
{
	x = coordX;
	y = coordY;
	this->clip = true;
}

Vertice::Vertice()
{
	x = 0;
	y = 0;
	this->clip = true;
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
// Otros métodos
//////////////////////////////////////////////////////////////////////

// Dibuja un vértice en la posición (coorX,coorY).
Vertice::dibujar(int coorX, int coorY){
	glVertex2i(coorX,coorY);	
}

// Dibuja el vértice.
Vertice::dibujar()
{
	if (clip)
			glVertex2i(x,y);
}

// Calcula la distancia con el vértice v.
int Vertice::distancia(Vertice v)
{
	float difx = abs(getX()-v.getX());
	float dify = abs(getY()-v.getY());
	return (int)(sqrt(difx*difx + dify*dify));

}

void Vertice:: clipping(Vertice* viewPmin,Vertice* viewPmax){
	
	if (this->getX() >= viewPmin->getX() && this->getX() <= viewPmax->getX() 
		&& this->getY() >= viewPmin->getY() && this->getY() <= viewPmax->getY())
		this->clip = true;
	else this->clip = false;

}


