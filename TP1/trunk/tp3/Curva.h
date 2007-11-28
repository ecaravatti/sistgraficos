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
	int cPtos, d;

public:
	/// bPuntos: buffer q contiene los puntos de control
	/// cantPtos: cantidad de ptos de control en el buffer
	/// d: cantidad de subdivisiones por tramo
	Curva::Curva(Punto* _bPtos, int _cantPtos, int _d);
	
	virtual ~Curva();

	/// Dibuja una curva bspline cubica
	void dibujarBSpline();

/// getters y setters
	void setCantPtos(int nuevaCant);

	void setPuntos(Punto* nuevo);

private:

	/// i: subindice de la base
	/// u: parametro de la base
	/// Calcula el valor de la base b(i)
	float base(int i, float u);

	///punto: punto donde se carga el pto de la curva calculado
	/// Calcula un punto de la curva
	void calcularPunto(int i, float u, Punto& p);

};

#endif // !defined(AFX_URVA_H__ACDE7D3A_606B_4364_B3E8_BAD07B52A8F2__INCLUDED_)
