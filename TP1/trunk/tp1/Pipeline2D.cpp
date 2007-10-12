// Pipeline2D.cpp: Implementaci�n de la clase CPipeline2D.
//
//////////////////////////////////////////////////////////////////////

#include "Pipeline2D.hpp"
#include "Circulo.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////
// Construcci�n/Destrucci�n
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


//////////////////////////////////////////////////////////////////////
// Otros m�todos
//////////////////////////////////////////////////////////////////////

// Indica la forma en que se interpretar�n los vertices que entren al
// pipeline. Es decir, si ser�n puntos sueltos, lineas, poligonos, etc.
void CPipeline2D::Primitiva2D(enum PRIMITIVA_2D prim2d)
{
	primitiva = prim2d;
}

// Establece el color con que se dibujan las lineas.
void CPipeline2D::ColorLinea (int r, int g, int b)
{
	colorLinea.r = r;
	colorLinea.g = g;
	colorLinea.b = b;
}

// Establece el color con que se dibujan los rellenos.
void CPipeline2D::ColorRelleno (int r, int g, int b)
{
	colorRelleno.r = r;
	colorRelleno.g = g;
	colorRelleno.b = b;
}

// Establece el color con que se dibujan los puntos.
void CPipeline2D::ColorPunto (int r, int g, int b)
{
	colorPunto.r = r;
	colorPunto.g = g;
	colorPunto.b = b;
}

// Inicializa la matriz de transformaciones con la matriz Identidad.
void CPipeline2D::CargarIdentidad(){
	this->mTransformacion.cargarId();
}

// M�todo utilizado para aplicar una translaci�n.
void CPipeline2D::Traslacion (float tx, float ty){
	Matriz3t mtras;
	
	mtras.cargarMatrizTraslacion(tx, ty);
	this->mTransformacion.multiplicar( mtras );
}

// M�todo utilizado para aplicar una rotaci�n.
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

// M�todo utilizado para aplicar una escala determinada.
void CPipeline2D:: Escalado (float ex, float ey){
	Matriz3t mesc;
	
	mesc.cargarMatrizEscalamiento(ex, ey);
	this->mTransformacion.multiplicar( mesc );

}

// Este m�todo procesa la lista de v�rtices por el pipeline, y los dibuja dependiendo de
// como est�n seteados los diferentes estados del mismo.
void CPipeline2D::Dibujar(Vertice* p_vertice,unsigned int nro_vertices){
	Vertice* p_verticeTransf = new Vertice[nro_vertices];
	Vertice* p_aux = new Vertice[nro_vertices];
	Vertice maxViewport,minViewport;
	this->calcularMVista();
	this->AplicarTransf(this->mTransformacion, p_vertice,p_aux,nro_vertices);
	this->AplicarTransf(this->mVista,p_aux,p_verticeTransf,nro_vertices);
	
	//this->AplicarTransf(this->mTransformacion, p_vertice,p_verticeTransf,nro_vertices);

	minViewport.setX(ptoMinViewport.getX());
	minViewport.setY(ptoMinViewport.getY());
	maxViewport.setX(ptoMinViewport.getX()+anchoViewport);
	maxViewport.setY(ptoMinViewport.getY()+altoViewport);
	switch (primitiva){

		case PRIM2D_POLIGONO:{
			glBegin(GL_POINTS);

			glColor3ub(colorLinea.r,colorLinea.g,colorLinea.b);
			Poligono poligono(p_verticeTransf,nro_vertices);
			poligono.clipping(&minViewport,&maxViewport);
			poligono.dibujarContorno();

			
			glEnd();
			break;
			}

		case PRIM2D_POLIGONO_RELLENO:{
			glBegin(GL_POINTS);

			Poligono poligono(p_verticeTransf,nro_vertices);
			poligono.clipping(&minViewport,&maxViewport);
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

			for (int i=0; i<nro_vertices; i++){
				p_verticeTransf[i].clipping(&minViewport, &maxViewport);
				p_verticeTransf[i].dibujar();
			}

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
		case PRIM2D_CIRCULO:{

			int i = 0;
			glBegin(GL_POINTS);
			glColor3ub(colorLinea.r,colorLinea.g,colorLinea.b);
			int nro = nro_vertices;
			while (nro>=2){
				Circulo circulo(&p_verticeTransf[i],p_verticeTransf[i].distancia(p_verticeTransf[i+1]));
				circulo.dibujarContorno();
				i+=2;
				nro-=2;
			}
			
			glEnd();
			break;
			}
	}
	//delete p_verticeTransf;
	//delete p_aux;
}
//TODO: el circulo relleno, bajo que "case" se haria???

// Define el Viewport
// Este metodo permite definir la posici�n en la pantalla y las dimensiones
// del viewport donde ser� renderizada la escena.
// x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.
// y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.  
// ancho Ancho del viewport expresado en pixels.
// alto Alto del viewport expresado en pixels.
void CPipeline2D::Viewport (int x0, int y0, int ancho, int alto)
{
	setPtoMinViewport(Vertice(x0,y0));
	setAnchoViewport(ancho);
	setAltoViewport(alto);
}

// Define la ventana de mundo
// Este metodo permite definir la posici�n en la pantalla y las dimensiones
// del viewport donde ser� renderizada la escena.
// param x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.
// y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.  
// ancho Ancho del viewport expresado en pixels.
// alto Alto del viewport expresado en pixels.
 void CPipeline2D::VentanaMundo (float u0, float v0, float ancho, float alto)
{
	setPtoMinMundo(Vertice(u0,v0));
	setAnchoMundo(ancho);
	setAltoMundo(alto);
}

void CPipeline2D::AplicarTransf(Matriz3t& m, const Vertice* p_vertice,Vertice* transf,
								unsigned int nro_vertices){
	Vector3t vectorResultado;
	Vector3t* vectorOriginal;
	for (int i=0; i<nro_vertices; i++){
		vectorOriginal=new Vector3t(p_vertice[i]);
		m.multiplicar(*vectorOriginal,vectorResultado);
		transf[i].set((int)floor(vectorResultado.get(0)+0.5),(int)floor(vectorResultado.get(1)+0.5));
		delete vectorOriginal;
	}
}

// Pone la pantalla en negro
void CPipeline2D::ClearScreen()
{	
	ColorLinea(0,0,0);
	ColorRelleno(0,0,0);
	Primitiva2D(PRIM2D_POLIGONO_RELLENO);
	Vertice* v = new Vertice[4];
	v[0].set(getPtoMinMundo().getX(),getPtoMinMundo().getY());
	v[1].set(getPtoMinMundo().getX() + anchoMundo,getPtoMinMundo().getY());
	v[2].set(getPtoMinMundo().getX() + anchoMundo,getPtoMinMundo().getY() + altoMundo);
	v[3].set(getPtoMinMundo().getX(), getPtoMinMundo().getY() + altoMundo);

	CargarIdentidad();
	Dibujar(v,4);

	delete[] v;
}



//////////////////////////////////////////////////////////////////////
// Getters y setters
//////////////////////////////////////////////////////////////////////

CPipeline2D::setPtoMinMundo(Vertice v)
{
	ptoMinMundo = v;
}

Vertice CPipeline2D::getPtoMinMundo() const
{
	return ptoMinMundo;
}

CPipeline2D::setPtoMinViewport(Vertice v)
{
	ptoMinViewport = v;
}

Vertice CPipeline2D::getPtoMinViewport() const
{
	return ptoMinViewport;
}

CPipeline2D::setAnchoMundo(float ancho)
{
	anchoMundo = ancho;
}

float CPipeline2D::getAnchoMundo() const
{
	return anchoMundo;
}

CPipeline2D::setAltoMundo(float alto)
{
	altoMundo = alto;
}

float CPipeline2D::getAltoMundo() const
{
	return altoMundo;
}

CPipeline2D::setAnchoViewport(int ancho)
{
	anchoViewport = ancho;
}

int CPipeline2D::getAnchoViewport() const
{
	return anchoViewport;
}

CPipeline2D::setAltoViewport(int alto)
{
	altoViewport = alto;
}

int CPipeline2D::getAltoViewport() const
{
	return altoViewport;
}

void CPipeline2D:: calcularMVista()
{
	Matriz3t aux,esc;
	aux.cargarMatrizTraslacion(-this->ptoMinMundo.getX(), -this->ptoMinMundo.getY());
	esc.cargarMatrizEscalamiento(this->anchoViewport/this->anchoMundo, this->altoViewport/this->altoMundo);
	esc.multiplicar(aux);
	this->mVista.cargarMatrizTraslacion(this->ptoMinViewport.getX(), this->ptoMinViewport.getY());
	this->mVista.multiplicar(esc);
}

bool CPipeline2D::instanceFlag = false;

CPipeline2D* CPipeline2D::pipe = NULL;

CPipeline2D* CPipeline2D::getInstancia()
{
	if(!instanceFlag)
	{
		pipe = new CPipeline2D();
		instanceFlag = true;
		return pipe;
	}
	else
		return pipe;
}