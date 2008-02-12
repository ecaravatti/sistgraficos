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
#include "Pared.h"
#include "Solido.h"
#include <stdlib.h>

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
	void setPosInicial(Punto posInicial);
	void setAngulo(int angulo);
	void setPosInicialX(double px);
	void setPosInicialY(double py);
	void setPosX(double x);
	void setPosY(double y);
	void setVelocidadInicial(double velocidad_i);
	void setVelocidad(double velocidad);
	void setVectorVelocidad(Velocidad v);
	void setTiempoRebote(double tiempoRebote);
	bool seChoca(Solido &solido);
	bool seChoca(Pared& p);
	void mover(double tiempo);
	int calcularAnguloIncidencia(Punto p);
	int calcularAnguloReflexion(int angIncidencia);
	void chocar(Pared p, double t);
	double calcularVelocidadReflexion(int angIncidencia, Punto dirPared);
	void chocar(Pelota pelota, double tiempo); // TODO: VER SI SIRVE PARA LOS CUERPOS DE REVOLUCION.
private:
	void calcularPosicionX(double t);
	void calcularPosicionY(double t);
	void calcularVelocidad(double t);
	void anguloReflexionASistFijo(Punto p,int angReflexion);
	double calcularVelocidadMaxima();
};

#endif // !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
