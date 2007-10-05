// Circulo.h: interface for the Circulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCULO_H__169A5A3F_329F_4F61_90AC_24F7F674CE0A__INCLUDED_)
#define AFX_CIRCULO_H__169A5A3F_329F_4F61_90AC_24F7F674CE0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertice.h"

class Circulo  
{
private:
	Vertice* vert0;
	int radio;
public:

	Circulo(Vertice* vO, int r);

	virtual ~Circulo();

	void dibujarContorno();

	void dibujarRelleno();

private:
	void dibujarPtos(int x, int y);

	void Circulo::dibujarBresenham(int radio);
};

#endif // !defined(AFX_CIRCULO_H__169A5A3F_329F_4F61_90AC_24F7F674CE0A__INCLUDED_)
