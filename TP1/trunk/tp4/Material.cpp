// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////

#include "Material.h"

GLfloat Material::ambiente[cantMat][3] = {{0.57, 0.40, 0.00},
			{0.30, 0.30, 0.35}, {0.33, 0.26, 0.23}, {0.25, 0.17, 0.19},
			{0.25, 0.15, 0.15}, {0.10, 0.11, 0.79}};
GLfloat Material::difuso[cantMat][3] ={{0.22, 0.15, 0.00},
			{0.30, 0.30, 0.50}, {0.50, 0.11, 0.00}, {0.10, 0.03, 0.22},
			{0.27, 0.00, 0.00}, {0.30, 0.30, 0.71}};
GLfloat Material::especular[cantMat][3] = {{0.71, 0.70, 0.56},
			{0.70, 0.70, 0.80}, {0.95, 0.73, 0.00}, {0.64, 0.00, 0.98},
			{0.61, 0.13, 0.18}, {0.83, 0.83, 0.83}};
GLfloat Material::brillo[cantMat] = {16.0, 9.0, 93.0, 8.0, 12.0, 12.0 };
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Material::Material():nroMaterial(-1)
{

}

Material::~Material()
{

}

void Material::sigMaterial(){
	this->nroMaterial++;
}

void Material::material(){
	int mat = this->nroMaterial % cantMat;
	glEnable(GL_COLOR_MATERIAL);	//Se activa lo materiales de color
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  //tipo ambiente y difusión (tambien incluyen specular)

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente[mat]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso[mat]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular[mat]);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo[mat]);
}