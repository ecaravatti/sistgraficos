// Vector3t.cpp: implementation of the Vector3t class.
//
//////////////////////////////////////////////////////////////////////

#include "Vector3t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector3t::Vector3t()
{
	for (int i=0; i < this->getDimension(); i++)
		this->vector[i] = 0.0;
}

Vector3t::Vector3t(const Vector3t &otro){
	if (this != &otro)
		for (int i=0; i < this->getDimension(); i++)
			this->vector[i] = otro.vector[i];
}

Vector3t::Vector3t(const Vertice &vert){
	this->vector[0] = (double)vert.getX();
	this->vector[1] = (double)vert.getY();
	this->vector[2] = 1.0;
}

Vector3t::~Vector3t()
{
}

int Vector3t:: getDimension() const{
	return size_v3t;
}


void Vector3t:: set(int i, double valor){
	if (i < this->getDimension())
		this->vector[i] = valor;
}

double Vector3t:: get(int i) const{
	if (i < this->getDimension())
		return this->vector[i];
	return this->vector[0];
}

