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
#include "Solido.h"
#include <stdlib.h>
#include <list>

class Pelota  
{
private:
	Punto posInicial;
	Punto posActual;      
	Velocidad velocidadInicial;
	Velocidad velocidad;
	float diametro;
	float tiempo;
	float tiempoAnt;
	float aceleracion;
	float fuerzaRozamiento;
	std::list<Solido*> listaSolidos;
	static Pelota* instance;
	
	
public:
	static Pelota* getInstance(){
		if (instance==NULL) instance=new Pelota();
		return instance;
	}
	virtual ~Pelota();
	float getPosX();
	float getPosY();
	float getVelocidad();
	void setPosInicial(Punto posInicial);
	void setAngulo(int angulo);
	void setVelocidadInicial(Velocidad v);
	void cargarSolido(Solido* solido);
	void mover();
	void dibujar_pelota();

private:
	Pelota();
	void calcularPosicionX(float t);
	void calcularPosicionY(float t);
	void calcularVelocidad(float t);
	void buscarChoques(float tiempo);
	void chocar(Solido* solido);
	bool seChoca(Solido* solido);
	void buscarChoquesPared();
};


//int getAngulo();
//float getPosInicialX();
//float getPosInicialY();
//Punto getPosActual();
//float getVelocidadInicial();
//Velocidad getVectorVelocidad();
//float getDiametro();
//void setPosInicialX(float px);
//void setPosInicialY(float py);
//void setPosX(float x);
//void setPosY(float y);
//void cargarPared(Pared* pared);
//void eliminarSolido(Solido* solido);
//void setVelocidad(float velocidad);
//void setVectorVelocidad(Velocidad v);
//void anguloReflexionASistFijo(Punto p,int angReflexion);
//bool seChoca(Pared* p);
//int calcularAnguloIncidencia(Punto p);
//int calcularAnguloReflexion(int angIncidencia);
//float calcularVelocidadReflexion(int angIncidencia, Punto dirPared);
//void chocar(Pared* p, float t);
#endif // !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
