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
	double velX;
	double velY;
	double modulo;

public:
	Velocidad();
	Velocidad(double vel, int ang);
	Velocidad(double x, double y);
	virtual ~Velocidad();

	static double toRadians(int ang);
	static double toDegrees(double ang);
	double getVelX();
	double getVelY();
	double getVelocidad();
	void setVelX(double vX);
	void setVelY(double vY);
	void setVelocidad(double v,int ang);
	void CalcularModulo();
	int calcularAngulo();



};

#endif // !defined(AFX_VELOCIDAD_H__4CC641E6_0CE1_4823_B3D5_C288B5686416__INCLUDED_)
