// Segmento.cpp: implementation of the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#include "Segmento.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Segmento::Segmento()
{

}

Segmento::Segmento(Vertice &v1,Vertice &v2)
{
	*ptoInicio = v1;
	*ptoFin = v2;
}

Segmento::~Segmento()
{
	delete ptoInicio;
	delete ptoFin;
}

//////////////////////////////////////////////////////////////////////
// Getters y setters
//////////////////////////////////////////////////////////////////////


Vertice Segmento::getPtoFin()
{
	return (*ptoFin);
}

Vertice Segmento::getPtoInicio()
{
	return (*ptoInicio);
}

Segmento::setPtoFin(Vertice v)
{
	*ptoFin = v;
}

Segmento::setPtoInicio(Vertice v)
{
	*ptoInicio = v;
}