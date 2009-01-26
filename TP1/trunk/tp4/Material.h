// Material.h: interface for the Material class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATERIAL_H__D393042B_175B_4EF3_AA62_A767E7B91306__INCLUDED_)
#define AFX_MATERIAL_H__D393042B_175B_4EF3_AA62_A767E7B91306__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GL\glut.h>
#include <stddef.h>
#define cantMat 6

class Material  
{
private:
	int nroMaterial;
	static Material* instance;

public:
	static GLfloat ambiente[cantMat][4];
	static GLfloat difuso[cantMat][4];
	static GLfloat especular[cantMat][4];
	static GLfloat brillo[cantMat];
	static Material* getInstance(){
		if (instance==NULL) instance=new Material();
		return instance;
	}
	virtual ~Material();

	///Elige el siguiente material
	//void sigMaterial();
	int getSigMat();
	void setMat(int nroMat);
	void activar();
private:
	Material();
};

#endif // !defined(AFX_MATERIAL_H__D393042B_175B_4EF3_AA62_A767E7B91306__INCLUDED_)
