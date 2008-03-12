// LSolidos.h: interface for the LSolidos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSOLIDOS_H__8D6A6175_C24D_4980_B8F7_B97459F34A66__INCLUDED_)
#define AFX_LSOLIDOS_H__8D6A6175_C24D_4980_B8F7_B97459F34A66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "Declaraciones.h"

struct RegSolido{
	double posx, posy;
	int cantPuntos;
	Punto* bPuntos;
	

	RegSolido(int posx, int posy, int cantPuntos, Punto* bPuntos);

	virtual ~RegSolido();
};

struct LSolidos  
{
	std:: list<RegSolido*> lista;

	LSolidos();

	virtual ~LSolidos();

};

#endif // !defined(AFX_LSOLIDOS_H__8D6A6175_C24D_4980_B8F7_B97459F34A66__INCLUDED_)
