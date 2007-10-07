// Segmento.h: interface for the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEGMENTO_H__3DBB0562_71F0_4699_92EC_BA17FC6F82EC__INCLUDED_)
#define AFX_SEGMENTO_H__3DBB0562_71F0_4699_92EC_BA17FC6F82EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertice.h"

class Segmento  
{

private:
	Vertice *ptoInicio;
	Vertice *ptoFin;

public:
	Segmento();
	Segmento(Vertice* v1,Vertice* v2);
	virtual ~Segmento();

	//getters y setters
	Vertice* getPtoFin();
	Vertice* getPtoInicio();
	void setPtoFin(Vertice v);
	void setPtoInicio(Vertice v);
	
	// Dibuja el segmento con el algoritmo de Bresenham
	void dibujarBresenham();

private:
	void dibujar_Mod_Menor_1(Vertice* vInicial, Vertice* vFinal, 
										bool cEje, int inc);
};

#endif // !defined(AFX_SEGMENTO_H__3DBB0562_71F0_4699_92EC_BA17FC6F82EC__INCLUDED_)
