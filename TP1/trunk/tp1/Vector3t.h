// Vector3t.h: interface for the Vector3t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3T_H__C991D96B_64C7_4E2C_BBE3_184CF873FDEE__INCLUDED_)
#define AFX_VECTOR3T_H__C991D96B_64C7_4E2C_BBE3_184CF873FDEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define size_v3t 3

#include "Vertice.h"

class Vector3t  
{
private:
	double vector[size_v3t];

public:
	Vector3t();
	
	// Construye el vector con coordenadas (vert->getX, vert->getY, 1)
	Vector3t(const Vertice& vert);
	
	// Constructor copia
	Vector3t(const Vector3t& otro);

	virtual ~Vector3t();

	int getDimension() const;

	void set(int i, double valor);

	double get(int i) const;

};

#endif // !defined(AFX_VECTOR3T_H__C991D96B_64C7_4E2C_BBE3_184CF873FDEE__INCLUDED_)
