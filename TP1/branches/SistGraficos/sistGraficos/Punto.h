// Punto.h: interface for the Punto class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "glut.h"

class Punto  
{
private:
	int x;
	int y;

public:
	Punto(int u, int v);
	Punto();
	virtual ~Punto();
	int getX();
	int getY();
	setX(int x);
	setY(int y);
	void dibujar();

};


