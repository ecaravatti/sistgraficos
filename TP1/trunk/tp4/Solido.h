// Solido.h: interface for the Solido class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
#define AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SOMBREADO	0
#define ALAMBRE		1

#include "Declaraciones.h"
#include "Iluminacion.h"
#include <vector>

class Solido  
{
private:
	int cantCortes;
	std::vector<Punto*> normales;
	std::vector<Punto*> puntos;
	Punto posicion;	
	float diametro;
	static bool vista;
	bool lcreadas;
	GLuint DLSombreado;
	GLuint DLAlambre;
	int nroTex;
	int nroMat;

public:
	//Constructor
	Solido(float posx, float posy,std::vector<Punto*> bPuntos,int nroMat,int nroTex);
	
	//Destructor
	virtual ~Solido();
	
	//Cambia de vista alambre/sombreada
	static void cambiarVista(){
		vista=!vista;
	}

	//Version static para chequeos de posicionamiento previos a la creacion
	static float Solido::calcularDiametro(std::vector<Punto*> &vector);

	//Setea cantidad de cortes
	void setCantCortes(int nueva);

	//Setea la posicion del solido
	void setPosicion(float posx,float posy,float posz);

	//Llama a la correspondiente display list
	void dibujar();

	//retorna la posicion del solido
	Punto getPosicion() const;

	//Retorna el diametro del cilindro que contiene al solido
	float getDiametro() const ;
	
private:
	
	//Evita instanciaciones accidentales
	Solido();

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
	void vistaSombreada(const Punto& r1, const Punto& r2,
						const Punto& r3, const Punto& r4,
						const Punto& n1, const Punto& n2,
						const Punto& n3, const Punto& n4);

	//Calcula las normales de la superficie del solido
	void calcularNormales();
	
	//Calcula el diametro del solido
	float calcularDiametro();

	//Crea las display lists
	void crearListas();

	//Dibuja el solido segun modo (alambre/sombreado)
	void dibujar_solido(int modo);
};

#endif // !defined(AFX_SOLIDO_H__CFDBD745_D827_41AE_AD2E_983274844BF8__INCLUDED_)
