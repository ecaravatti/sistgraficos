// urva.h: interface for the Curva class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_URVA_H__ACDE7D3A_606B_4364_B3E8_BAD07B52A8F2__INCLUDED_)
#define AFX_URVA_H__ACDE7D3A_606B_4364_B3E8_BAD07B52A8F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"

class Curva  
{
private:
	Punto* bPtos;
	int cPtos, cTramos, d;
	Color color0, color1;
	int res;
	float grosor;

public:
	/// bPuntos: buffer q contiene los puntos de control
	/// cantPtos: cantidad de ptos de control en el buffer
	/// cantTramos: cantidad de tramos q tendra la curva
	/// d: cantidad de subdivisiones por tramo
	/// color0: color inicial
	/// color1: color final
	Curva(Punto* bPtos, int res, int cantPtos, int cantTramos, int d, const Color &color0,
		  const Color &color1, float grosor);
	
	virtual ~Curva();

	/// Dibuja una curva bspline cubica
	void dibujarBSpline();
private:

	/// i: subindice de la base
	/// u: parametro de la base
	/// Calcula el valor de la base b(i)
	float base(int i, float u) ;

	//Punto Curva:: p(int i, float t) ;

	///punto: punto donde se carga el pto de la curva calculado
	/// Calcula un punto de la curva
	void calcularPunto(int i, float u, Punto& p) ;

	/// Calcula el color para la posicion x
	void calcularColor(int posX, Color& color);

};

#endif // !defined(AFX_URVA_H__ACDE7D3A_606B_4364_B3E8_BAD07B52A8F2__INCLUDED_)
