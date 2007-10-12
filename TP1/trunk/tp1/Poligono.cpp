// Poligono.cpp: implementación de la clase Poligono.
//
//////////////////////////////////////////////////////////////////////

#include "Poligono.h"
#include "Segmento.h"
#include <math.h>

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
	int ymax = 0, ymin, yscan= 0, i, posMin = 0, ymaxscan;
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
	if (!this->lVertices->empty()){
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

/**********************************************************************************/
void Poligono::clipping(Vertice* viewPmin,Vertice* viewPmax){
	actualizarLista( Left,viewPmin,viewPmax); //Recorta el lado izquierdo
	actualizarLista( Right,viewPmin,viewPmax); //Recorta el lado derecho
	actualizarLista( Top,viewPmin,viewPmax);	//Recorta el lado superior 
	actualizarLista( Bottom,viewPmin,viewPmax); //Recorta el lado inferior
	
	this->cantVertices = this->lVertices->size();
}

void Poligono::actualizarLista( enum Borde borde,Vertice *viewPmin,Vertice *viewPmax){
	Vertice *vertice, *v2, *vIni;
	std::list<Vertice*>::iterator it,it2;
	std::list<Vertice*>* listaNueva=new std::list<Vertice*>;
	
	it=lVertices->begin();
	it2=lVertices->begin();

	for (unsigned int i=0;i<lVertices->size();i++){
		if (i < lVertices->size() - 1){
			it2++;
			v2 = *it2;	
		}
		else
			v2 = this->lVertices->front();


		if (!adentro(*it,borde,viewPmin,viewPmax) && adentro(v2,borde,viewPmin,viewPmax)){
			vertice=intersecar(*it,v2,borde,viewPmin,viewPmax);
			this->agregarVertice(listaNueva, vertice);
			this->agregarVertice(listaNueva, new Vertice(*v2));
		
		}
		
		if(adentro(*it,borde,viewPmin,viewPmax)){

			this->agregarVertice(listaNueva, new Vertice(**it));
		
			if (adentro(v2,borde,viewPmin,viewPmax) )
				this->agregarVertice(listaNueva, new Vertice(*v2));
			
			if (!adentro(v2,borde,viewPmin,viewPmax) ){
				vertice=intersecar(*it,v2,borde,viewPmin,viewPmax);
				this->agregarVertice(listaNueva, vertice);
			}
		}
		it++;
	}
	if (!listaNueva->empty()){
		vIni = listaNueva->front();
		v2 = listaNueva->back();
		if (vIni->getX() == v2->getX() && vIni->getY() == v2->getY() ){
			delete v2;
			listaNueva->pop_back();
		}
	}
	this->destruirLVertices(this->lVertices);
	this->lVertices=listaNueva;
	
}

//Agrega el vertice a la lista, siempre y cuando, el ultimo en la lista
//no sea el que se igual al que se quiere agregar
void Poligono:: agregarVertice(std:: list<Vertice*>* lVertices, Vertice* nuevo){
	Vertice* ult;
	
	if (!lVertices->empty()){
		ult = lVertices->back();
		if (ult->getX() != nuevo->getX() || ult->getY() != nuevo->getY())
			lVertices->push_back(nuevo);
	}
	else lVertices->push_back(nuevo);

}

bool Poligono::adentro(Vertice *v, enum Borde borde,Vertice *viewPmin,Vertice *viewPmax){
	switch (borde){
	case Left: 
			if(v->getX()<viewPmin->getX()) return false;
			break;
	case Right: 
			if (v->getX()>viewPmax->getX()) return false;
			break;
	case Bottom:
			if (v->getY()<viewPmin->getY()) return false;
			break;
	case Top:
			if (v->getY()>viewPmax->getY()) return false;
			break;
	}
	return true;
}

Vertice* Poligono::intersecar(Vertice *v1,Vertice *v2,enum Borde borde,Vertice *viewPmin,Vertice *viewPmax){
	Vertice* interseccion=new Vertice();
	float m;
	
	if (v1->getX()!=v2->getX())
		m=(float)(v1->getY() - v2->getY()) / (v1->getX() - v2->getX());
	
	switch (borde){
	case Left: 
			interseccion->setX(viewPmin->getX());
			interseccion->setY((int)floor(v2->getY()+(viewPmin->getX()-v2->getX())*m));
			break;
	case Right:
			interseccion->setX(viewPmax->getX());
			interseccion->setY((int)floor(v2->getY()+(viewPmax->getX()-v2->getX())*m));
			break;
	case Bottom:
			interseccion->setY(viewPmin->getY());
			if (v1->getX()!=v2->getX())
				interseccion->setX((int)floor(v2->getX()+(viewPmin->getY()-v2->getY())/m));
			else interseccion->setX(v2->getX());
			break;
	case Top:
			interseccion->setY(viewPmax->getY());
			if (v1->getX()!=v2->getX())
				interseccion->setX((int)floor(v2->getX()+(viewPmax->getY()-v2->getY())/m));
			else interseccion->setX(v2->getX());
			break;
	}
	return (interseccion);
}
