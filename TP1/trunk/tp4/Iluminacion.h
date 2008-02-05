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

public:

	Iluminacion();

	virtual ~Iluminacion();

	/// Incrementa la cantidad de luces
	void incrementarNroLuz();

	/// Habilita y configura las luces
	void luces() const;

///getters y setters
	int getCantLuces() const;
	
};

#endif // !defined(AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_)
