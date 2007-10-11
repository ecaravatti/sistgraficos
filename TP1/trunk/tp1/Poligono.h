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

enum Borde{
	Left,
	Right,
	Top,
	Bottom
};

class Poligono  
{
private:
	struct Arista{
		int ymax, ymin;
		float m, xmin, x0;
	};	
	std:: list<Vertice*>* lVertices;
	int cantVertices;
	Arista** vecAristas;
	int cantAristas;
	
public:
	Poligono(Vertice* pVertice, int cantVert);
	
	virtual ~Poligono();

	void dibujarScanLine();

	void dibujarContorno();

	void clipping(Vertice* viewPmin,Vertice* viewPmax);
	
private:

	//Carga los vertices que estan en pVertice en una lista
	void cargarLVertices(Vertice* pVertice);
	
	//A partir de los vertices construye el vector de las aristas
	void construirVectorAristas(int &ymax);

	void eliminarAristaActivas(std:: list<int>* aristasActivas, 
								int yscan, int &ymaxscan);

	void rellenar(std:: list<int>* aristasActivas, int yscan);

	//Para rellenar agrega una arista a la lista de aristas activas
	void agregarArista(std:: list<int>* aristasActivas,
							  int nroArista, int &ymacscan);
	
	// Destruye el vector de aristas
	void destruirVecAristas();
	
	// Destruye la lista de vertices
	void destruirLVertices(std:: list<Vertice*>* l);

	bool adentro(Vertice *v, enum Borde borde,Vertice *viewPmin,Vertice *viewPmax);
	
	Vertice* intersecar(Vertice *v1,Vertice *v2,enum Borde borde,Vertice *viewPmin,Vertice *viewPmax);
	
	void actualizarLista(enum Borde borde,Vertice *viewPmin,Vertice *viewPmax);
	
};

#endif // !defined(AFX_POLIGONO_H__3C0B5C85_762C_425A_9ED3_11E7A7B5F983__INCLUDED_)
