// Matriz3t.cpp: Implementaci�n de la clase Matriz3t.
//
//////////////////////////////////////////////////////////////////////

#include "Matriz3t.h"
#include <cmath>
//////////////////////////////////////////////////////////////////////
// Construcci�n/Destrucci�n
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

// Devuelve la dimensi�n de la matriz. En este caso, 3.
int Matriz3t::getDimension() const
{
	return size_m3t;
}

// Inicializa la matrix con ceros.
void Matriz3t::inicializar()
{
	for ( int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)
			this->matriz[i][j] = 0.0;			
}

// Pone le numero "valor" en la posici�n (i,j).
void Matriz3t:: set(int i, int j, double valor){
	if ( i < this->getDimension() && j < this->getDimension() &&
		 i >= 0 && j >= 0)
			this->matriz[i][j] = valor;
}

// Devuelve el valor de la posici�n (i,j).
double Matriz3t:: get(int i, int j) const{
	if ( i < this->getDimension() && j < this->getDimension() &&
		 i >= 0 && j >= 0)
			 return this->matriz[i][j];
	return this->matriz[0][0];
}

// Carga la matriz Identidad.
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

// multiplica por la matriz m.
void Matriz3t:: multiplicar(const Matriz3t &m){
	Matriz3t aux(*this);	
	this->inicializar();

	for (int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)
			for (int k = 0; k < this->getDimension(); k++)
				this->matriz[i][j] += aux.matriz[i][k]*m.matriz[k][j]; 	
}

void  Matriz3t::multiplicar(const Vector3t &vector, Vector3t& rtdo){
	rtdo.set(0,0.0);
	rtdo.set(1,0.0);
	rtdo.set(2,0.0);
	for (int i = 0; i < this->getDimension(); i++ )
		for (int j = 0; j < this->getDimension(); j++)	
			rtdo.set(i, rtdo.get(i) + this->matriz[i][j] * vector.get(j) );
}