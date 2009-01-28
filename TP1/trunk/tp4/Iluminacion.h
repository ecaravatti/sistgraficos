// Iluminacion.h: interface for the Iluminacion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_)
#define AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GL\glut.h>
#include <stddef.h>

class Iluminacion  
{
private:
	//int nroLuz;
	GLfloat posicion_luz[8][4];
	static GLenum eluces[8];
	static Iluminacion* instance;

public:

	//Devuelve la unica instancia (Singleton)
	static Iluminacion* getInstance(){
		if (instance==NULL) instance=new Iluminacion();
		return instance;
	}
	//Destructor
	virtual ~Iluminacion();

	/// Habilita y configura la iluminacion
	void encender_luces() const;

	//Apaga el sistema de iluminacion
	void apagar_luces();

private:
	//Constructor Privado
	Iluminacion();
};

#endif // !defined(AFX_ILUMINACION_H__7B5CA91B_8126_465E_A104_85BD85F6D2C3__INCLUDED_)
