// Solido.h: interface for the Solido class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
#define AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Declaraciones.h"
#include "Iluminacion.h"

class Solido  
{
private:
	int cantCortes;
	int alpha, beta;
	Iluminacion* iluminacion;

public:
	Solido();
	virtual ~Solido();

///getters y setters
	void setCantCortes(int nueva);

	/// Para dibujar los solidos
	void solido(Punto* bPuntos, int nPuntos,
				int wancho, int walto);

	void setIluminacion(Iluminacion* iluminacion);

	void setAngulo(int _alpha, int beta);

private:
	 
	/// Rota el punto p_in theta radianes sobre el eje Y dando como resultado p_out
	void rotarPunto(const double angulo, const Punto& p_in, Punto& p_out);

	/// Para obtener el vector normal con norma = 1
	void normalizar(Punto& normal);

	/// Calcula el vector normal con norma == 1, usando producto vectorial de dos vectores
	void calcularNormal(const Punto &v1, const Punto &v2, const Punto &v3, Punto& normal);

	/// Completa la vista alambre con 4 puntos
	void vistaAlambres(const Punto& r1, const Punto& r2, const Punto& r3,
				       const Punto& r4);

	/// Completa la vista sombreada con 4 puntos
	void vistaSombreada(const Punto& r1, const Punto& r2, const Punto& r3,
						const Punto& r4);
};

#endif // !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
