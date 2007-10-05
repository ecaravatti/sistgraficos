// Matriz3t.h: interface for the Matriz3t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIZ3T_H__01C687DC_219B_4DE0_AB3E_CED0E1FB3BF1__INCLUDED_)
#define AFX_MATRIZ3T_H__01C687DC_219B_4DE0_AB3E_CED0E1FB3BF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector3t.h"

#define size_m3t 3

class Matriz3t  
{
private:
	double matriz[size_m3t][size_m3t];

public:
	Matriz3t();

	Matriz3t(const Matriz3t &otra);
	
	virtual ~Matriz3t();

	int getDimension() const;

	//Inicializa la matriz en 0
	void inicializar();

	void set(int i, int j, double valor);

	double get(int i, int j) const;

	void cargarId();

	void cargarMatrizTraslacion(float tx, float ty);

	void cargarMatrizRotacion( float angulo );

	void cargarMatrizEscalamiento(float ex, float ey);

	// this = this * m
	void multiplicar(const Matriz3t &m);
	
	// rtdo = this * vector
	void multiplicar(const Vector3t& vector, Vector3t& rtdo);

};

#endif // !defined(AFX_MATRIZ3T_H__01C687DC_219B_4DE0_AB3E_CED0E1FB3BF1__INCLUDED_)
