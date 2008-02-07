// Pared.h: interface for the Pared class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARED_H__1D4454C8_1947_4E92_B030_972C2EDCDDF8__INCLUDED_)
#define AFX_PARED_H__1D4454C8_1947_4E92_B030_972C2EDCDDF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"

class Pared  
{

	/**
	* Cada pared es considerada como una recta, tomándose la 
	* ecuación paramétrica de la misma, según la forma:
	* L: t * direccion + origen. Donde t pertenece a los Reales.
	*/
private:
	Punto direccion;
	Punto origen;


public:
	Pared(Punto p1, Punto p2);
	virtual ~Pared();
	Punto getOrigen();
	Punto getDireccion();
	//bool seChoca(Pelota pelota);

};

#endif // !defined(AFX_PARED_H__1D4454C8_1947_4E92_B030_972C2EDCDDF8__INCLUDED_)
