// Pipeline2D.cpp: Implementación de la clase CPipeline2D.
//
//////////////////////////////////////////////////////////////////////

#include "Pipeline2D.hpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPipeline2D::CPipeline2D()
{

}

CPipeline2D::~CPipeline2D()
{

}

void CPipeline2D::Primitiva2D(enum PRIMITIVA_2D prim2d)
{
	primitiva = prim2d;
}

void CPipeline2D::ColorLinea (int r, int g, int b)
{
	colorLinea.r = r;
	colorLinea.g = g;
	colorLinea.b = b;
}

void CPipeline2D::ColorRelleno (int r, int g, int b)
{
	colorRelleno.r = r;
	colorRelleno.g = g;
	colorRelleno.b = b;
}

void CPipeline2D::ColorPunto (int r, int g, int b)
{
	colorPunto.r = r;
	colorPunto.g = g;
	colorPunto.b = b;
}