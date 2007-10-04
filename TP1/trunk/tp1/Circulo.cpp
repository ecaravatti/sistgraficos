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
	delete this->vert0;
}

void Circulo::dibujarBresenham(){
	int x = 0, y = this->radio, e = 1 - this->radio;

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