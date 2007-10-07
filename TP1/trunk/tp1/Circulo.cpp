// Circulo.cpp: implementation of the Circulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Circulo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circulo::Circulo(Vertice* v0, int r) 
{
	this->vert0 = v0;
	this->radio = r;
}

Circulo::~Circulo()
{
}

void Circulo:: dibujarContorno(){
	this->dibujarBresenham(this->radio);
}

void Circulo:: dibujarRelleno(){

	for (int i = 0; i <= this->radio; i++)
		this->dibujarBresenham(i);


}

void Circulo:: dibujarPtos(int x, int y){
	int x0 = this->vert0->getX(), y0 = this->vert0->getY();

	Vertice::dibujar( x0 + x, y0 + y);
	Vertice::dibujar( x0 - x, y0 + y);
	Vertice::dibujar( x0 + x, y0 - y);
	Vertice::dibujar( x0 - x, y0 - y);
	Vertice::dibujar( x0 + y, y0 + x);
	Vertice::dibujar( x0 - y, y0 + x);
	Vertice::dibujar( x0 + y, y0 - x);
	Vertice::dibujar( x0 - y, y0 - x);
}

void Circulo::dibujarBresenham(int r){
	int x = 0, y = r, e = 1 - r;

	this->dibujarPtos(x, y);

	while ( x < y ){
		x++;
		if (e < 0) e += 2 * x + 1;
		else{
			y--;
			e += 2 * (x - y) + 1;
		}
		this->dibujarPtos(x, y);
	}
}