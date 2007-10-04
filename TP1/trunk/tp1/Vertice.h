// Vertice.h: Interfase de la clase Vertice.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTICE_H__C7EF80BF_9F41_4534_AF14_7C2567C11D83__INCLUDED_)
#define AFX_VERTICE_H__C7EF80BF_9F41_4534_AF14_7C2567C11D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/glut.h>

class Vertice  
{

private:
	int x;
	int y;

public:
	// Constructores y destructores
	Vertice();
	Vertice(int coordX, int coordY);
	virtual ~Vertice();

	// Getters y setters
	int getX();
	int getY();
	void setX(int coordX);
	void setY(int coordY);
	void set(int coorX, int coorY);

	// Otros métodos
	dibujar();

};

#endif // !defined(AFX_VERTICE_H__C7EF80BF_9F41_4534_AF14_7C2567C11D83__INCLUDED_)
