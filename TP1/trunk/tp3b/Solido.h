// Solido.h: interface for the Solido class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
#define AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"

class Solido  
{
private:
	int cantPuntos, cantCortes;
	Solido* solido;

public:
	Solido();
	virtual ~Solido();

};

#endif // !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
