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
#include <list>

class Pelota  
{
private:
	Punto posInicial;
	Punto posActual;
	//int angulo;        
	Velocidad velocidadInicial;
	//Velocidad velocidad;
	float masa;
	float diametro;
	//float tiempoRebote;
	//float t0;
	float tiempo;
	float tiempoAnt;
	float aceleracion;
	float fuerzaRozamiento;
	std::list<Pared*> listaParedes;
	std::list<Solido*> listaSolidos;
	
	
public:
	Pelota();
	Pelota(float px, float py, float v, int ang);
	virtual ~Pelota();
	Velocidad velocidad;
	int getAngulo();
	float getPosX();
	float getPosY();
	float getPosInicialX();
	float getPosInicialY();
	Punto getPosActual();
	float getVelocidadInicial();
	float getVelocidad();
	Velocidad getVectorVelocidad();
	float getDiametro();
	void setPosInicial(Punto posInicial);
	void setAngulo(int angulo);
	void setPosInicialX(float px);
	void setPosInicialY(float py);
	void setPosX(float x);
	void setPosY(float y);
	void setVelocidadInicial(Velocidad v);
	//void setTiempoInicial(float t0);
	void cargarPared(Pared* pared);
	void cargarSolido(Solido* solido);
	void eliminarSolido(Solido* solido);
	//void mover(float tiempo);
	void mover();
	void dibujar_pelota();

private:
	void setVelocidad(float velocidad);
	void setVectorVelocidad(Velocidad v);
	void calcularPosicionX(float t);
	void calcularPosicionY(float t);
	void calcularVelocidad(float t);
	void anguloReflexionASistFijo(Punto p,int angReflexion);
	//float calcularVelocidadMaxima();
	void buscarChoques(float tiempo);
	int calcularAnguloIncidencia(Punto p);
	int calcularAnguloReflexion(int angIncidencia);
	float calcularVelocidadReflexion(int angIncidencia, Punto dirPared);
	void chocar(Pared* p, float t);
	void chocar(Solido* solido);
	bool seChoca(Solido* solido);
	bool seChoca(Pared* p);
	void buscarChoquesPared();
};

#endif // !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
