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

void CPipeline2D::CargarIdentidad(){
	this->mTransformacion.cargarId();
}


void CPipeline2D::Traslacion (float tx, float ty){
	Matriz3t mtras;
	
	mtras.cargarMatrizTraslacion(tx, ty);
	this->mTransformacion.multiplicar( mtras );
}

void CPipeline2D::Rotacion (float rx, float ry, float alfa){
	Matriz3t mrot, mtras;

	mtras.cargarMatrizTraslacion(-rx, -ry);
	mrot.cargarMatrizRotacion(alfa);
	mrot.multiplicar(mtras);
	mtras.cargarMatrizTraslacion(rx, ry);
	mrot.multiplicar(mtras);
	this->mTransformacion.multiplicar( mrot );
}

void CPipeline2D:: Escalado (float ex, float ey){
	Matriz3t mesc;
	
	mesc.cargarMatrizEscalamiento(ex, ey);
	this->mTransformacion.multiplicar( mesc );

}