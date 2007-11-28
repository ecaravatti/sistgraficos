// VistaCorteModelo.cpp: implementation of the VistaCorteModelo class.
//
//////////////////////////////////////////////////////////////////////

#include "VistaCorteModelo.h"
#include <GL\glut.h> 
#include "Curva.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int VistaCorteModelo::x = 300;
const int VistaCorteModelo::y = 0;
const int VistaCorteModelo::pasos = 10; 
const Color VistaCorteModelo::color = {0,0,255}; 
VistaCorteModelo* VistaCorteModelo::vcm = NULL;

VistaCorteModelo::VistaCorteModelo(int _ancho, int _alto):
											ancho(_ancho),
											alto(_alto),
											lPuntos(),
											bPuntos(NULL)
{
}

VistaCorteModelo::~VistaCorteModelo()
{
}

/*--------------------------------------------------------------------*/
// Metodos publicos
void VistaCorteModelo:: dibujar(){
	/*glViewport(this->x, this->y, this->ancho, this->alto);
	glMatrixMode (GL_PROJECTION);						
	glLoadIdentity ();	
	gluOrtho2D(0, this->ancho/2, this->alto/2, 0);*/

	this->copiarPuntos();
	glColor3ub(this->color.r,this->color.g,this->color.b);
	Curva curva(this->bPuntos, this->lPuntos.size(), this->pasos);
	curva.dibujarBSpline();
}

VistaCorteModelo* VistaCorteModelo::getInstancia(){
	if (vcm == NULL) vcm = new VistaCorteModelo(wancho, walto);
		return vcm;
}

void VistaCorteModelo:: guardarPunto(const Punto &pto){
	Punto pAnt;
	if (!this->lPuntos.empty()){
		pAnt = this->lPuntos.back();
			if (pAnt.x != pto.x && pAnt.y != pto.y && pAnt.z != pto.z)
			this->lPuntos.push_back(pto);
	}
	this->lPuntos.push_back(pto);
}

/*--------------------------------------------------------------------*/
// Metodos privados
void VistaCorteModelo:: copiarPuntos(){
	std::list<Punto>::iterator it;
	int i = 0;

	if (this->bPuntos != NULL) delete [] this->bPuntos;
	this->bPuntos = new Punto[this->lPuntos.size()];

	for (it = this->lPuntos.begin(); it != this->lPuntos.end(); it++){
		this->bPuntos[i].x = (*it).x;
		this->bPuntos[i].y = (*it).y;
		this->bPuntos[i].z = (*it).z;
		i++;
	}
}