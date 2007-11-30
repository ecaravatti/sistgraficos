// VistaCorteModelo.cpp: implementation of the VistaCorteModelo class.
//
//////////////////////////////////////////////////////////////////////

#include "VistaCorteModelo.h"
#include <GL\glut.h> 
#include "Curva.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int VistaCorteModelo::pasos = 5; //tramos de la curva bspline
const Color VistaCorteModelo::colorCurva = {0,0,255}; //color de la curva bpline
const Color VistaCorteModelo::colorPtoControl = {255,0,0};

VistaCorteModelo* VistaCorteModelo::vcm = NULL; //instancia

VistaCorteModelo::VistaCorteModelo():
											lPuntos(),
											bPuntos(NULL),
											generatriz(pasos),
											cGeneratriz(false)
{
}

VistaCorteModelo::~VistaCorteModelo()
{
	delete [] this->bPuntos;
}

/*--------------------------------------------------------------------*/
// Metodos publicos
void VistaCorteModelo:: dibujar(){

	this->copiarPuntos();
	glColor3ub(this->colorCurva.r,this->colorCurva.g,this->colorCurva.b);
	this->generatriz.setCantPtos(this->lPuntos.size());
	this->generatriz.setPuntos(this->bPuntos);
	if (cGeneratriz){
		this->generatriz.discretizarCurva();
		this->cGeneratriz = false;
	}
	this->generatriz.dibujarBSpline();
	this->mostrarPuntoControl();
}

VistaCorteModelo* VistaCorteModelo::getInstancia(){
	if (vcm == NULL) vcm = new VistaCorteModelo();
		return vcm;
}

void VistaCorteModelo::destruir(){
	//delete [] bPuntos;
	delete vcm;
}

void VistaCorteModelo:: guardarPunto(const Punto &pto){
	Punto pAnt;
	if (!this->lPuntos.empty()){
		pAnt = this->lPuntos.back();
		if (pAnt.x != pto.x && pAnt.y != pto.y){
			this->lPuntos.push_back(pto);
			this->cGeneratriz = true;
		}
	}
	else{
		this->lPuntos.push_back(pto);
		this->cGeneratriz = true;
	}
}

void VistaCorteModelo:: mostrarPuntoControl(){
	std::list<Punto>::iterator it;
	glPointSize(3.0);
	glColor3ub(this->colorPtoControl.r,this->colorPtoControl.g,this->colorPtoControl.b);
	glBegin(GL_POINTS);
	for (it = this->lPuntos.begin(); it != this->lPuntos.end(); it++)
			glVertex3f((*it).x,(*it).y,(*it).z);
	
	glEnd();
}

void VistaCorteModelo:: mostrarCurvaDiscretizada(){
	Punto *ptos = this->generatriz.getBufferPtosDisc();

	for (int i = 0; i < this->generatriz.getCantPtosDisc(); i++){
		std:: cout<<"Punto i: "<<i<<std:: endl;
		std:: cout<<"{"<<ptos[i].x<<" , "<<ptos[i].y<<" , "<<ptos[i].z<<"}"<<std::endl;
	}

}

/// getters y setters
Curva* VistaCorteModelo:: getCurvaGeneratriz(){
	return &this->generatriz;
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