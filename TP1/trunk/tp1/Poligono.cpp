// Poligono.cpp: implementación de la clase Poligono.
//
//////////////////////////////////////////////////////////////////////

#include "Poligono.h"
#include "Segmento.h"


//////////////////////////////////////////////////////////////////////
// Construcción/Destrucción
//////////////////////////////////////////////////////////////////////

Poligono::Poligono(Vertice* _pVertice, int cantVert)
{
	this->cantVertices = cantVert;
	this->vecAristas = NULL;
	this->cantAristas = 0;
	this->lVertices = new std::list<Vertice*>;
	cargarLVertices( _pVertice );
}

Poligono::~Poligono()
{
	this->destruirVecAristas();
	this->destruirLVertices(this->lVertices);
}

//////////////////////////////////////////////////////////////////////
// Otros métodos.
//////////////////////////////////////////////////////////////////////

// Devuelve el mínimo entre los números n1 y n2.
int min(int n1, int n2){
	if (n1 < n2) return n1;
	else return n2;
}

// Devuelve el máximo entre los números n1 y n2.
int max(int n1, int n2){
	if (n1 > n2) return n1;
	else return n2;
}


// Algoritmo de ScanLine para rellenar polígonos.
void Poligono:: dibujarScanLine()
{
	int ymax, ymin, yscan, i, posMin = 0, ymaxscan;
	bool fin;
	std:: list<int> aristasActivas;
	std::list<int>::iterator it;
	construirVectorAristas(ymax);
	bool busMin = true;

	while (yscan < ymax){
		ymaxscan = ymax;
		this->eliminarAristaActivas(&aristasActivas, yscan, ymaxscan);

	if (busMin){	
		i = posMin + 1;
		fin = false;
		ymin = this->vecAristas[posMin]->ymin;
		this->agregarArista(&aristasActivas, posMin, ymaxscan);

		while ( i < this->cantAristas && !fin){
			if (this->vecAristas[i]->ymin == ymin) {
				this->agregarArista(&aristasActivas, i, ymaxscan);
				i++;
			}
			else fin = true;
		}
		posMin = i;
	}

	if (posMin < this->cantAristas){
		if (ymaxscan < this->vecAristas[posMin]->ymin)
			busMin = false;
		else{
			busMin = true;
			ymaxscan = this->vecAristas[posMin]->ymin; //el sig minimo
		}
	}
	else busMin = false;

		yscan = ymin;
		while (yscan < ymaxscan){
			this->rellenar(&aristasActivas, yscan);
			yscan++;
		}
	ymin = ymaxscan;
	}
	
	
}

// Dibuja el contorno del polígono.
void Poligono:: dibujarContorno(){
	Segmento *s;
	Vertice *v1, *v2;
	int i;

	std::list<Vertice*>::iterator it = this->lVertices->begin() ;
	i = 0;
	while ( it != this->lVertices->end() ){
		v1 = *it;
		if (i < this->cantVertices - 1){
			v2= *(++it);
			s = new Segmento(new Vertice(*v1), new Vertice(*v2));
			s->dibujarBresenham();
			delete s;
		}
		else
			it++;
		i++;
	}

	v1 = this->lVertices->back();
	v2 = this->lVertices->front();
	s = new Segmento(new Vertice(*v1), new Vertice(*v2));
	s->dibujarBresenham();
	delete s;

}

/*--------------------------------------------------------------------*/
// Este método dibuja segmentos entre los vértices que se le pasan en la 
// lista de aristas activas.
void Poligono:: rellenar(std:: list<int>* aristasActivas, int yscan){
	Vertice *v1, *v2;
	Segmento *s;

	std:: list<int>::iterator it = aristasActivas->begin();
	while (it != aristasActivas->end()){
		v1 = new Vertice( this->vecAristas[*it]->x0, yscan );
		this->vecAristas[*it]->x0 += this->vecAristas[*it]->m;
		it++;
		v2 = new Vertice( this->vecAristas[*it]->x0, yscan); 
		this->vecAristas[*it]->x0 += this->vecAristas[*it]->m;
		s = new Segmento(v1, v2);
		s->dibujarBresenham();
		delete s;
		it++;
	}

}

//Agrega las aristas a la lista de aristas activas ordenadas por xmin
void Poligono:: agregarArista(std:: list<int>* aristasActivas,
							  int nroArista, int &ymaxscan){
	bool enc = false;
	std:: list<int>::iterator it= aristasActivas->begin();
	while (it != aristasActivas->end() && !enc){
		if (this->vecAristas[*it]->xmin > this->vecAristas[nroArista]->xmin) enc = true;
		else it++;
	}

	if (enc && it != aristasActivas->end()) 
			aristasActivas->insert(it, nroArista);
	else aristasActivas->push_back(nroArista);
	
	if (vecAristas[nroArista]->ymax < ymaxscan) ymaxscan = vecAristas[nroArista]->ymax;

}

//Elimina de las aristas activas las que ya fueron scaneadas
void Poligono:: eliminarAristaActivas(std:: list<int>* aristasActivas, int yscan, int &ymaxscan){
	std:: list<int>::iterator it = aristasActivas->begin();
	
	while (it != aristasActivas->end()){
		if (this->vecAristas[*it]->ymax <= yscan ) 
						it = aristasActivas->erase(it);
		else{
			if (this->vecAristas[*it]->ymax < ymaxscan) 
				ymaxscan = this->vecAristas[*it]->ymax;
			it++;
		}
	}
}

//Construye el vector con todas las aristas
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
	std:: list<Vertice*>::iterator it= this->lVertices->begin();
	Vertice *v0, *v1;

	for (int i = 0; i < this->cantVertices ; i++){
		v0 = (*it);
		x0 = v0->getX();
		y0 = v0->getY();

		if (i < this->cantVertices - 1)
			v1 = *(++it);
		else
			v1 = this->lVertices->front();
		
		x1 = v1->getX();
		y1 = v1->getY();

	if (y0 != y1){ //la arista no es una linea horizontal
		arista = new Poligono::Arista;
		
		dy = y1 - y0;
		dx = x1 - x0;

		arista->ymax = max( y0, y1 );
		if (y0 < y1){
			arista->ymin = y0;	
			arista->x0 = x0;
		}
		else{
			arista->ymin = y1;
			arista->x0 = x1;
		}

		arista->xmin = min(x0, x1);

		if (dy != 0 && dx != 0)
				arista->m = 1/(dy/dx);
		else arista->m = 0;
		
		ymax = max(ymax, y0);
		ymax = max(ymax, y1);

		j = 0;
		cond = true;
		while ( j < cant && cond){
			if (this->vecAristas[j]->ymin > arista->ymin) cond = false;
			else j++;
		}
		
		if (!cond)
			for (int k = cant; k > j; k--)
				this->vecAristas[k] = this->vecAristas[k-1];

		this->vecAristas[j] = arista;

		cant++;

	}
	}

	this->cantAristas = cant;	
}

void Poligono:: destruirVecAristas(){
	if (this->vecAristas != NULL){
		for (int i=0; i < this->cantAristas; i++)
			delete this->vecAristas[i];

		delete [] vecAristas;
	}
}

void Poligono:: cargarLVertices(Vertice* pVertice){
	
	for (int i = 0; i < this->cantVertices; i++)
		this->lVertices->push_back( new Vertice(pVertice[i]) );
}

void Poligono:: destruirLVertices(std:: list<Vertice*>* l){
	
	std::list<Vertice*>::iterator it= l->begin();
	for (; it != this->lVertices->end(); it++)
		delete (*it);

	delete l;
}

