// VistaCorteModelo.h: interface for the VistaCorteModelo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_)
#define AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "Curva.h"
#include "Declaraciones.h"

class VistaCorteModelo  
{
private:
	std::list<Punto> lPuntos;
	Punto* bPuntos;
	static VistaCorteModelo *vcm;
	Curva generatriz;
	bool cGeneratriz; //para indicar cuando debe ser calculada la curva generatriz

	/*
	 * _ancho: ancho del viewport
	 * _alto: alto del viewport
	 */
	VistaCorteModelo();

public:
// Atributos publicos	

	// cantidad de pasos para dibujar bspline
	static const int pasos;
	//colorCurva: color de la curva
	//colorPtoControl: color de los puntos de control
	static const Color colorCurva, colorPtoControl;

// Destructor
	virtual ~VistaCorteModelo();

// Metodos publicos
	/*
	 * Devuelve la instancia de esta clase
	 */
	static VistaCorteModelo* getInstancia();

	static void destruir();

	/*
	 * Dibuja la vista cuando se agrega un punto
	 */
	void dibujar();

	/*
	 * pto: punto a ser guardado
	 * Guarda punto en la lista de puntos
	 */
	void guardarPunto(const Punto& pto);

	/*
	 * Muestra los puntos de control
	 */
	void mostrarPuntoControl();

	/*
	 * Devuelve puntero a curva
	 */
	Curva* getCurvaGeneratriz();

	//sacar
	void mostrarCurvaDiscretizada();
private:
	//Copia la lista de puntos en un buffer de puntos
	void copiarPuntos();
};

#endif // !defined(AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_)
