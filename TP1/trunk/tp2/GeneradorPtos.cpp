// GeneradorPtos.cpp: implementation of the GeneradorPtos class.
//
//////////////////////////////////////////////////////////////////////

#include "GeneradorPtos.h"
#include <cstdlib>

const int GeneradorPtos:: res = 200;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GeneradorPtos::GeneradorPtos(int _cantTramos):cantTramos(_cantTramos),
											  pendiente(0.125)
{
	this->cantPtos = this->cantTramos*3 + 1;
	this->ptroPuntos = new Punto[this->cantPtos];
}

GeneradorPtos::~GeneradorPtos()
{
	//delete [] this->ptroPuntos;
}


void GeneradorPtos:: generarPtos(){
	int menorX = 0, rangoX, xAnt = -1, i = 1, x, rangoY, y;
	bool cond = false;

	this->cargarPtos(0,0,0);
	
	rangoX = res / (this->cantPtos - 2);

	while (!cond){
		// Genero la coordenada x
		x =  ( menorX + ( rand() % rangoX ) ); // * i/(this->cantPtos - 1);
	
		if (x < res && x != xAnt){
			//Genero la coordenada y
			rangoY = (int) (this->pendiente * (float)x);
			
			if (rangoY != 0)
				y = (1 + rand() % (rangoY*2)) - rangoY;
			else 
				y = 0;

			this->cargarPtos(i, x, y);
			if (i == this->cantTramos*3 - 1) cond = true;
			menorX = rangoX*i;
			i++;
			xAnt = x;
		}
		
	}
	rangoY = (float) this->pendiente * res;
	y = (1 + rand() % (rangoY*2) ) - rangoY;
	this->cargarPtos(this->cantPtos - 1, res, y);
}

Punto* GeneradorPtos:: getPuntos(){
	return this->ptroPuntos;
}

///getters y setters
int GeneradorPtos:: getCantPtos(){
	return this->cantPtos;
}

/*--------------------------------------------------------------------*/
/// Metodos Privados
void GeneradorPtos:: cargarPtos(int ind, int x, int y){
	this->ptroPuntos[ind].x = x;
	this->ptroPuntos[ind].y = y;
	this->ptroPuntos[ind].z = 1;
}