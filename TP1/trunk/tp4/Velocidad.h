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
	Velocidad();
	Velocidad(float vel, int ang);
	Velocidad(float x, float y);
	virtual ~Velocidad();

	static float toRadians(int ang);
	static float toDegrees(float ang);
	float getVelX();
	float getVelY();
	float getModulo();
	int getAngulo();
	void setVelX(float vX);
	void setVelY(float vY);
	void setVelocidad(float v,int ang);
	

private:
	void calcularModulo();
	int calcularAngulo();

};

#endif // !defined(AFX_VELOCIDAD_H__4CC641E6_0CE1_4823_B3D5_C288B5686416__INCLUDED_)
