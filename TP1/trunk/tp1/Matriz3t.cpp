// Matriz3t.cpp: implementation of the Matriz3t class.
//
//////////////////////////////////////////////////////////////////////

#include "Matriz3t.h"
#include <cmath>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define PI 3.14159265

Matriz3t::Matriz3t()
{
}

Matriz3t:: Matriz3t(const Matriz3t &otra){
	for (int i = 0; i < this->getDimension(); i++)
		for (int j = 0; j < this->getDimension(); j++)
			this->matriz[i][j] = otra.matriz[i][j];
}

Matriz3t::~Matriz3t()
{
}

int Matriz3t::getDimension() const
{
	return size_m3t;
}

void Matriz3t::inicializar()
{
	for ( int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)
			this->matriz[i][j] = 0.0;			
}

void Matriz3t:: set(int i, int j, double valor){
	if ( i < this->getDimension() && j < this->getDimension() &&
		 i >= 0 && j >= 0)
			this->matriz[i][j] = valor;
}

double Matriz3t:: get(int i, int j) const{
	if ( i < this->getDimension() && j < this->getDimension() &&
		 i >= 0 && j >= 0)
			 return this->matriz[i][j];
	return this->matriz[0][0];
}

void Matriz3t:: cargarId(){

	for (int i = 0; i < this->getDimension(); i++)
		for (int j = 0; j < this->getDimension(); j++)
			if (i == j) this->matriz[i][j] = 1.0;
			else this->matriz[i][j] = 0.0;	
}

void Matriz3t:: cargarMatrizTraslacion(float tx, float ty){

	this->cargarId();
	this->matriz[0][2] = tx;
	this->matriz[1][2] = ty;	
}

void Matriz3t:: cargarMatrizRotacion( float angulo ){
	double angRad = (angulo*PI)/180;

	this->cargarId();
	this->matriz[0][0] = cos(angRad);
	this->matriz[0][1] = -sin(angRad);
	this->matriz[1][0] = sin(angRad);
	this->matriz[1][1] = cos(angRad);

}

void Matriz3t:: cargarMatrizEscalamiento(float ex, float ey){
	this->cargarId();
	this->matriz[0][0] = ex;
	this->matriz[1][1] = ey;
}

void Matriz3t:: multiplicar(const Matriz3t &m){
	Matriz3t aux(*this);	
	this->inicializar();

	for (int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)
			for (int k = 0; k < this->getDimension(); k++)
				this->matriz[i][j] += aux.matriz[i][k]*m.matriz[k][j]; 	
}

void  Matriz3t::multiplicar(const Vector3t& vector, Vector3t rtdo){
			
	for (int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)	
			rtdo.set(i, rtdo.get(i) + this->matriz[i][j] * vector.get(j) );
	

}