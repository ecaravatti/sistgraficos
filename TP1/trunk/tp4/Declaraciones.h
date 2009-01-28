// Declaraciones.h: interface for the Declaraciones class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_)
#define AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <math.h>
#define PI 3.1415926535

struct Punto{
	
	double x, y, z;
	
	double distancia(const Punto& punto){
		return sqrt(pow(punto.x - x,2)+pow(punto.y - y,2));
	}
	Punto(double x,double y, double z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Punto(const Punto& punto){
		x=punto.x;
		y=punto.y;
		z=punto.z;
	}
	Punto(){
		x=0;
		y=0;
		z=0;
	}
	
	bool operator==(const Punto& punto){
		if (punto.x==x && punto.y==y) return true;
		return false;
	}

};

/*****************************************************************************************/

struct Color{
	int r, g, b, alpha;
};

/*****************************************************************************************/

//void viewport(int posx, int posy, int w, int h);

#endif // !defined(AFX_DECLARACIONES_H__1E16576E_D7E9_4C3E_83AE_1732893E2BB0__INCLUDED_)
