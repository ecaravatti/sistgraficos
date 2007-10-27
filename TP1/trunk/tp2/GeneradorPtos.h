// GeneradorPtos.h: interface for the GeneradorPtos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERADORPTOS_H__CF1F883C_E8EF_4935_A670_F2A1739F00DB__INCLUDED_)
#define AFX_GENERADORPTOS_H__CF1F883C_E8EF_4935_A670_F2A1739F00DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"

class GeneradorPtos  
{
private:
	int cantTramos, cantPtos;
	Punto *ptroPuntos;
	const float pendiente;

public:
	static const int res;

	GeneradorPtos(int cantTramos);

	virtual ~GeneradorPtos();

	void generarPtos();
	
	Punto* getPuntos();

/// getters y setters
	int getCantPtos();

private:
	void cargarPtos(int ind, int x, int y);
};

#endif // !defined(AFX_GENERADORPTOS_H__CF1F883C_E8EF_4935_A670_F2A1739F00DB__INCLUDED_)
