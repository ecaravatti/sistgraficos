// Pipeline2D.cpp: Implementación de la clase CPipeline2D.
//
//////////////////////////////////////////////////////////////////////

#include "Pipeline2D.hpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPipeline2D::CPipeline2D()
{
	this->colorLinea.r=255;
	this->colorLinea.g=255;
	this->colorLinea.b=255;
	this->colorPunto.r=255;
	this->colorPunto.g=255;
	this->colorPunto.b=255;
	this->colorRelleno.r=255;
	this->colorRelleno.g=255;
	this->colorRelleno.b=255;
	this->CargarIdentidad();
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
	//mrot.multiplicar(mtras);
	mtras.multiplicar(mrot);
	//this->mTransformacion.multiplicar( mrot );
	this->mTransformacion.multiplicar( mtras );
}

void CPipeline2D:: Escalado (float ex, float ey){
	Matriz3t mesc;
	
	mesc.cargarMatrizEscalamiento(ex, ey);
	this->mTransformacion.multiplicar( mesc );

}

void CPipeline2D::Dibujar(Vertice* p_vertice,unsigned int nro_vertices){
	Vertice* p_verticeTransf = new Vertice[nro_vertices];
	this->AplicarTransf(p_vertice,p_verticeTransf,nro_vertices);
	switch (primitiva){

		case PRIM2D_POLIGONO:{
			glBegin(GL_POINTS);

			glColor3ub(colorLinea.r,colorLinea.g,colorLinea.b);
			Poligono poligono(p_verticeTransf,nro_vertices);
			poligono.dibujarContorno();
			
			glEnd();
			break;
			}

		case PRIM2D_POLIGONO_RELLENO:{
			glBegin(GL_POINTS);

			Poligono poligono(p_verticeTransf,nro_vertices);
			glColor3ub(colorLinea.r,colorLinea.g,colorLinea.b);
			poligono.dibujarContorno();
			glColor3ub(colorRelleno.r,colorRelleno.g,colorRelleno.b);
			poligono.dibujarScanLine();

			glEnd();
			break;
			}
		case PRIM2D_PUNTO:{
			glBegin(GL_POINTS);
			glColor3ub(colorPunto.r,colorPunto.g,colorPunto.b);
			for (int i=0; i<nro_vertices; i++)
				p_verticeTransf[i].dibujar();

			glEnd();
			break;
			}
		
		case PRIM2D_SEGMENTO:{
			int i=0;
			glBegin(GL_POINTS);

			glColor3ub(colorLinea.r,colorLinea.g,colorLinea.b);
			while (nro_vertices>=2){
				Segmento segmento(&p_verticeTransf[i],&p_verticeTransf[i+1]);
				segmento.dibujarBresenham();
				i+=2;
				nro_vertices-=2;
			}

			glEnd();
			break;
			}
	}
}
	//Y el circulo?? 

void CPipeline2D::AplicarTransf(const Vertice* p_vertice,Vertice* transf,
								unsigned int nro_vertices){
	Vector3t vectorResultado;
	Vector3t* vectorOriginal;
	for (int i=0; i<nro_vertices; i++){
		vectorOriginal=new Vector3t(p_vertice[i]);
		this->mTransformacion.multiplicar(*vectorOriginal,vectorResultado);
		transf[i].set((int)vectorResultado.get(0),(int)vectorResultado.get(1));
		delete vectorOriginal;
	}
}