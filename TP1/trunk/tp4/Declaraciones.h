// Declaraciones.h: interface for the Declaraciones class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_)
#define AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.1415926535

struct Punto{
	double x, y, z;
};

struct Color{
	int r, g, b;
};

void viewport(int posx, int posy, int w, int h);

#endif // !defined(AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_)
