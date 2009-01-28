// Pelota.h: interface for the Pelota class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
#define AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	std::list<Solido*> listaSolidos;
	static Pelota* instance;
	
public:
	//Devuelve la unica instancia (Singleton)
	static Pelota* getInstance(){
		if (instance==NULL) instance=new Pelota();
		return instance;
	}
	//Destructor
	virtual ~Pelota();
	
	//Devuelve la coordenada X de la posicion actual
	float getPosX();
	
	//Devuelve la coordenada Y de la posicion actual
	float getPosY();
	
	//Devuelve el modulo de la velocidad actual
	float getVelocidad();

	//Setea la posicion inicial desde donde se dispara la pelotita
	void setPosInicial(Punto posInicial);

	//Setea el angulo de movimiento
	void setAngulo(int angulo);

	//Setea la velocidad de disparo
	void setVelocidadInicial(Velocidad v);
	
	//Carga un solido (obstaculo) a la lista
	void cargarSolido(Solido* solido);

	//Metodo principal de movimiento
	void mover();

	//Dibuja la pelotita
	void dibujar_pelota();

private:
	
	//Constructor privado
	Pelota();

	//Calcula y setea la coordenada X para el tiempo t
	void calcularPosicionX(float t);

	//Calcula y setea la coordenada Y para el tiempo t
	void calcularPosicionY(float t);

	//Calcula y setea la velocidad para un tiempo t
	void calcularVelocidad(float t);

	//Busca choques con solidos 
	void buscarChoquesSolidos();

	//Calcula direccion y velocidad de rebote
	void chocar(Solido* solido);
	
	//Analiza si la pelotita esta chocando con un solido
	bool seChoca(Solido* solido);

	//Busca y resuelve choques con las paredes
	void buscarChoquesPared();
};
#endif // !defined(AFX_PELOTA_H__1E5E39AE_A87D_4879_8FE6_179645554F3B__INCLUDED_)
