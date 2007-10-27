// Estrella.h: interface for the Estrella class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ESTRELLA_H__0C95D84B_DB2F_404B_980D_1B7AD42E1B3C__INCLUDED_)
#define AFX_ESTRELLA_H__0C95D84B_DB2F_404B_980D_1B7AD42E1B3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curva.h"
#include "Declaraciones.h"

class Estrella  
{
private:
	int x, y, rMin, rMax, Nr;
	Color color0, color1;
	Punto *ptosRayos, **ptosCurvas; 
	//ptosRayos: ptos donde empiezan los rayos
	//ptosCurvas: ptos para dibujar las curvas
	int* angRayos;
	static const int maxTramos, maxGrosor, pasos;
	
public:
	Estrella(int x, int y, int rMin, int rMax, int Nr, Color color0, Color color1);

	virtual ~Estrella();

	void dibujar();

private:
	/// radio: radio del circulo
	/// color: color del circulo
	/// Dibuja un circulo relleno con centro (0,0)
	void circuloRelleno(int radio, Color color);

	void generarRayos();

	/// Genera los puntos para una curva i
	void generarPuntos(Curva* curva, int i);

	/// Genera el grosor de una curva
	float generarGrosor();
};

#endif // !defined(AFX_ESTRELLA_H__0C95D84B_DB2F_404B_980D_1B7AD42E1B3C__INCLUDED_)
