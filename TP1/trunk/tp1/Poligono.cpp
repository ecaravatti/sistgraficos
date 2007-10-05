// Poligono.cpp: implementation of the Poligono class.
//
//////////////////////////////////////////////////////////////////////

#include "Poligono.h"
#include "Segmento.h"

#include <iostream>
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
int min(int n1, int n2){
	if (n1 < n2) return n1;
	else return n2;
}

int max(int n1, int n2){
	if (n1 > n2) return n1;
	else return n2;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Poligono::Poligono(Vertice* pVertice, int cantVert)
{
	this->pVertice = pVertice;
	this->cantVertices = cantVert;
	this->vecAristas = NULL;
}

Poligono::~Poligono()
{
	delete [] pVertice;
	this->destuirVecAristas();
}

void Poligono:: dibujarScanLine()
{
	int ymax, ymin, yscan = 0, i, posMin = 0, ymaxscan;
	bool fin;
	std:: list<int> aristasActivas;
	std::list<int>::iterator it;
	construirVectorAristas(ymax);
	
	while (yscan < ymax){
		this->eliminarAristaActivas(&aristasActivas, yscan);

		i = posMin + 1;
		fin = false;
		ymin = this->vecAristas[posMin]->ymin;
		buscarAdyacente(&aristasActivas, posMin );
		while ( i < this->cantVertices && !fin){
			if (this->vecAristas[i]->ymin == ymin) {
				buscarAdyacente(&aristasActivas, i);
				i++;
			}
			else fin = true;
		}
		posMin = i;

		if (posMin < this->cantVertices)
				ymaxscan = this->vecAristas[posMin]->ymin;
		else ymaxscan = ymax;

		yscan = ymin;
		while (yscan < ymaxscan){
			this->rellenar(&aristasActivas, yscan);
			yscan++;
		}

	}
	
}

void Poligono:: rellenar(std:: list<int>* aristasActivas, int yscan){
	Vertice *v1, *v2;
	Segmento *s;

	std:: list<int>::iterator it = aristasActivas->begin();
	while (it != aristasActivas->end()){
		v1 = new Vertice( this->vecAristas[*it]->xmin, yscan );
		this->vecAristas[*it]->xmin += this->vecAristas[*it]->m;
		v2 = new Vertice( this->vecAristas[*it]->xmin, yscan); 
		it++;
		this->vecAristas[*it]->xmin += this->vecAristas[*it]->m;
		s = new Segmento(v1, v2);
		s->dibujarBresenham();
		delete s;
		it++;
	}

}

void Poligono:: buscarAdyacente(std:: list<int>* aristasActivas, 
								int nroArista){
	bool enc = false;
	std:: list<int>::iterator it = aristasActivas->begin();
	while (it != aristasActivas->end() && !enc){
		if (this->vecAristas[nroArista]->xmin == this->vecAristas[*it]->xmin)
			enc = true;
		else it++;
	}
	
	if (enc) aristasActivas->insert(it, nroArista);
	else aristasActivas->push_front(nroArista);
}

void Poligono:: eliminarAristaActivas(std:: list<int>* aristasActivas, int yscan){
	std:: list<int>::iterator it = aristasActivas->begin();
	
	while (it != aristasActivas->end()){
		if (this->vecAristas[*it]->ymax < yscan ) 
						it = aristasActivas->erase(it);
		else it++;
	}
}

void Poligono:: construirVectorAristas(int& ymax)
{
	int j;
	int cant = 0;
	bool cond = true;
	Poligono:: Arista* arista;
	this->vecAristas = new Poligono::Arista*[this->cantVertices];
	int x0, x1, y0, y1;
	float dy, dx;
	ymax = 0;

	for (int i = 0; i < this->cantVertices ; i++){
		arista = new Poligono::Arista;
		x0 = this->pVertice[i].getX();
		y0 = this->pVertice[i].getY();
		if (i < this->cantVertices - 1){
			x1 = this->pVertice[i+1].getX();
			y1 = this->pVertice[i+1].getY();
		}
		else{
			x1 = this->pVertice[0].getX();
			y1 = this->pVertice[0].getY();
		}
		dy = y1 - y0;
		dx = x1 - x0;
		if (dy != 0 && dx != 0)
				arista->m = 1/(dy/dx);
		else arista->m = 0;
		arista->xmin = min( x0, x1 );
		arista->ymax = max( y0, y1 );
		arista->ymin = min( y0, y1 );
		ymax = max(ymax, y0);
		ymax = max(ymax, y1);

		j = 0;
		while ( j < cant && cond){
			if (this->vecAristas[j]->ymin > arista->ymin) cond = false;
			else j++;
		}
		
		if (!cond)
			for (int k = cant; k > j; k--)
				this->vecAristas[k] = this->vecAristas[k-1];
		else if (j!=0) j -= 1;

			this->vecAristas[j] = arista;

		cant++;

	}

}

void Poligono:: destuirVecAristas(){

	for (int i=0; i < this->cantVertices; i++)
		delete this->vecAristas[i];

	delete [] vecAristas;
}
