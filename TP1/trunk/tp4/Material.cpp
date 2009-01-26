// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////

#include "Material.h"
//#include <iostream>
Material* Material::instance=NULL;
GLfloat Material::ambiente[cantMat][4] = {{0.57, 0.4, 0.00, 1.0},
			{0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, 
			{0.0, 0.0, 0.0, 1.0}, {0.12, 0.10, 0.15, 1.0}, 
			{0.10, 0.11, 0.2, 1.0}};
GLfloat Material::difuso[cantMat][4] ={{0.22, 0.15, 0.00,1.0},
			{0.1,0.35, 0.1, 1.0}, {0.50, 0.11, 0.00, 1.0}, 
			{0.10, 0.30, 0.22, 1.0}, {0.0, 0.56, 0.60, 1.0},
			{0.81, 0.00, 0.85, 1.0}};
GLfloat Material::especular[cantMat][4] = {{0.71, 0.70, 0.56, 1.0},
			{0.45, 0.55, 0.45, 1.0}, {0.95, 0.73, 0.00, 1.0}, 
			{0.54, 0.00, 0.58, 1.0}, {0.10, 0.70, 0.8, 1.0},
			{0.85, 0.0, 0.75, 1.0}};
GLfloat Material::brillo[cantMat] = {16.0, 16.0, 93.0, 8.0, 9.0, 12.0 };
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Material::Material():nroMaterial(0)
{

}

Material::~Material()
{

}
/*
void Material::sigMaterial(){
	this->nroMaterial++;
	int mat = this->nroMaterial % cantMat;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente[mat]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso[mat]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular[mat]);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo[mat]);
}
*/
void Material::setMat(int nroMat){
	if (nroMat>cantMat) nroMat=0;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente[nroMat]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso[nroMat]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular[nroMat]);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo[nroMat]);
}

void Material::activar(){
//	nroMaterial=-1;
	glEnable(GL_COLOR_MATERIAL);	//Se activan los materiales de color
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  //tipo ambiente y difusión (tambien incluyen specular)
//	sigMaterial();
}
int Material::getSigMat(){
	this->nroMaterial++;
	if (nroMaterial>cantMat)
		nroMaterial=0;
	return nroMaterial;
}