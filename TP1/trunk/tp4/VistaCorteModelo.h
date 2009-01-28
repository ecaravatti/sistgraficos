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
	Curva generatriz;
	bool cGeneratriz; //para indicar cuando debe ser calculada la curva generatriz
	int pasos;
	static VistaCorteModelo* instance;

public:
// Atributos publicos	
	//colorCurva: color de la curva
	//colorPtoControl: color de los puntos de control
	static const Color colorCurva, colorPtoControl;

	//Devuelve la unica instancia (Singleton)
	static VistaCorteModelo* getInstance(){
		if (instance==NULL) instance=new VistaCorteModelo();
		return instance;
	}
// Destructor
	virtual ~VistaCorteModelo();

// Metodos publicos
	void destruir();

	//Dibuja la vista cuando se agrega un punto
	void dibujar();

	//Guarda punto en la lista de puntos
	void guardarPunto(const Punto& pto);

	//Muestra los puntos de control
	void mostrarPuntoControl();

	//Elimina todos los datos de la vista
	void limpiarVista();

    //Devuelve puntero a curva
	Curva* getCurvaGeneratriz();
	
	//Para setear la cantidad de pasos
	void setCantPasos(int nueva);

	//Devuelve cantidad de pasos actual
	int getCantPasos();

private:
	//Copia la lista de puntos en un buffer de puntos
	void copiarPuntos();

	//Constructor Privado
	VistaCorteModelo();
};

#endif // !defined(AFX_VISTACORTEMODELO_H__A8FC1254_C46C_40A9_9D0D_C93C820EA9BE__INCLUDED_)
