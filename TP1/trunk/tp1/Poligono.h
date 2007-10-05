// Poligono.h: interface for the Poligono class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLIGONO_H__3C0B5C85_762C_425A_9ED3_11E7A7B5F983__INCLUDED_)
#define AFX_POLIGONO_H__3C0B5C85_762C_425A_9ED3_11E7A7B5F983__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vertice.h"
#include <list>

class Poligono  
{
private:
	struct Arista{
		int ymax, ymin;
		float m, xmin;
	};	
	Vertice* pVertice;
	int cantVertices;
	Arista** vecAristas;
	int cantAristas;
	
	//std:: list<Vertice*> lvertices;
	//std:: list laristas;
public:
	Poligono(Vertice* pVertice, int cantVert);
	
	virtual ~Poligono();

	void dibujarScanLine();

	void dibujarContorno();

private:

	void construirVectorAristas(int &ymax);

	void buscarAdyacente(std:: list<int>* aristasActivas, 
								int nroArista);

	void eliminarAristaActivas(std:: list<int>* aristasActivas, 
								int yscan);

	void rellenar(std:: list<int>* aristasActivas, int yscan);

	void destuirVecAristas();
};

#endif // !defined(AFX_POLIGONO_H__3C0B5C85_762C_425A_9ED3_11E7A7B5F983__INCLUDED_)
