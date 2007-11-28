// VistaCorteModelo.h: interface for the VistaCorteModelo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_)
#define AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "Declaraciones.h"

class VistaCorteModelo  
{
private:
	int ancho, alto;
	std::list<Punto> lPuntos;
	Punto* bPuntos;
	static VistaCorteModelo *vcm;

	/*
	 * _ancho: ancho del viewport
	 * _alto: alto del viewport
	 */
	VistaCorteModelo(int _ancho, int _alto);

public:
// Atributos publicos	
	/*
	 * _x: coordenada x de la esquina inferior del rectangulo de viewport
	 * _y: coordenana y de la esquina inferior del rectangulo de viewport
	 * cantidad de pasos para dibujar bspline
	 */
	static const int x, y, pasos;
	//color de la curva
	static const Color color;

// Destructor
	virtual ~VistaCorteModelo();

// Metodos publicos
	/*
	 * Devuelve la instancia de esta clase
	 */
	static VistaCorteModelo* getInstancia();

	/*
	 * Dibuja la vista cuando se agrega un punto
	 */
	void dibujar();

	/*
	 * pto: punto a ser guardado
	 * Guarda punto en la lista de puntos
	 */
	void guardarPunto(const Punto& pto);
private:
	//Copia la lista de puntos en un buffer de puntos
	void copiarPuntos();
};

#endif // !defined(AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_)
