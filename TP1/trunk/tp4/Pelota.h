// Pelota.h: interface for the Pelota class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
#define AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"
#include "Velocidad.h"

class Pelota  
{
private:
	Punto posInicial;
	Punto posActual;
	int angulo;        
	Velocidad velocidadInicial;
	Velocidad velocidad;
	double masa;
	double diametro;
	double tiempoRebote;
	double aceleracion;
	double fuerzaRozamiento;
	
	
public:
	Pelota();
	Pelota(double px, double py, double v, int ang);
	virtual ~Pelota();

		
	double getFRozamiento();
	int getAngulo();
	double getPosX();
	double getPosY();
	double getPosInicialX();
	double getPosInicialY();
	Punto getPosActual();
	double getAceleracion();
	double getVelocidadInicial();
	double getVelocidad();
	Velocidad getVectorVelocidad();
	double getDiametro();
	double getMasa();

};

#endif // !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
