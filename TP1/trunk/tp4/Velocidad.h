// Velocidad.h: interface for the Velocidad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VELOCIDAD_H__4CC641E6_0CE1_4823_B3D5_C288B5686416__INCLUDED_)
#define AFX_VELOCIDAD_H__4CC641E6_0CE1_4823_B3D5_C288B5686416__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "Declaraciones.h"

class Velocidad  
{

private:
	float velX;
	float velY;
	float modulo;
	int angulo;

public:
	//Costructor default
	Velocidad();

	//Constructor que recibe modulo y angulo
	Velocidad(float vel, int ang);

	//Constructor que recibe la velocidad en coordenadas
	Velocidad(float x, float y);

	//Destructor
	virtual ~Velocidad();

	//Pasa un angulo en grados a radianes
	static float toRadians(int ang);

	//Pasa un angulo de radianes a grados
	static float toDegrees(float ang);

	//Devuelve la coordenada X de la velocidad
	float getVelX();

	//Devuelve la coordenada Y de la velocidad
	float getVelY();

	//Devuelve el modulo de la velocidad
	float getModulo();

	//Devuelve el angulo de la velocidad
	int getAngulo();

	//Setea la coordenada X de la velocidad
	void setVelX(float vX);

	//Setea la coordenada Y de la velocidad
	void setVelY(float vY);

	//Setea modulo y angulo nuevos
	void setVelocidad(float v,int ang);
	

private:
	//Calcula el modulo de la velocidad
	void calcularModulo();
	
	//Calcula el angulo de la velocidad
	int calcularAngulo();
};

#endif // !defined(AFX_VELOCIDAD_H__4CC641E6_0CE1_4823_B3D5_C288B5686416__INCLUDED_)
