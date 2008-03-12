// LSolidos.cpp: implementation of the LSolidos class.
//
//////////////////////////////////////////////////////////////////////

#include "LSolidos.h"

//////////////////////////////////////////////////////////////////////
// Clase RegSolido
//////////////////////////////////////////////////////////////////////
RegSolido::RegSolido(int _posx, int _posy, int _cantPuntos, Punto* _bPuntos):
									posx(_posx),
									posy(_posy),
									cantPuntos(_cantPuntos)
{
	this->bPuntos = new Punto[cantPuntos];
	for (int i = 0; i < this->cantPuntos; i++){
		this->bPuntos[i].x = _bPuntos[i].x;
		this->bPuntos[i].y = _bPuntos[i].y;
		this->bPuntos[i].z = _bPuntos[i].z;
	}

}

RegSolido:: ~RegSolido()
{
	delete [] this->bPuntos;
}
//////////////////////////////////////////////////////////////////////
// Clase LSolidos
//////////////////////////////////////////////////////////////////////

LSolidos::LSolidos(): lista()
{
}

LSolidos::~LSolidos()
{
  std::list<RegSolido*>::iterator it;

  for ( it = this->lista.begin() ; it != this->lista.end(); it++ )
  	delete (*it);
}
