// Iluminacion.h: interface for the Iluminacion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_)
#define AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GL\glut.h>

class Iluminacion  
{
private:
	int nroLuz;
	GLfloat posicion_luz[8][4];
	static GLenum eluces[8];
	int material;

public:
	static const int PLASTICO;
	static const int DIFUSO;

	Iluminacion();

	virtual ~Iluminacion();

	/// Incrementa la cantidad de luces
	void incrementarNroLuz();

	/// Agrega una luz
	/// Devuelve verdadero en caso de ser posible.
	bool agregarLuz(float x, float y);

	void mostrarLuces();

	/// Habilita y configura las luces
	void luces() const;

	/// Para "desactivar" todas las fuentes de luz
	void eliminarFuentes();

///getters y setters
	int getCantLuces() const;

	int getMaterial();

	void setMaterial(int nuevo);

private: 

	void plastico() const;

	void difuso() const;
	
};

#endif // !defined(AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_)
