/// Pipeline2D.hpp
/// La clase CPipeline2D modela un pipeline grafico 2D que permite dibujar pol�gonos,
/// poligonos rellenos, segmentos de rectas, puntos y circulos.
/// El pipeline dibuja utilizando la API OpenGL
/// Ofrece metodos que permiten configurar el pipeline antes de ingresar el conjunto de vertices.
/// 66.71 Sistemas Graficos 2do Cuatrimestre de 2007
#pragma once

#include "Matriz3t.h"
#include "Poligono.h"
#include "Vertice.h"
#include "Segmento.h"

enum PRIMITIVA_2D
{
	PRIM2D_POLIGONAL,
	PRIM2D_POLIGONO,
	PRIM2D_POLIGONO_RELLENO,
	PRIM2D_PUNTO,
	PRIM2D_SEGMENTO,
	PRIM2D_CIRCULO,
	PRIM2D_CIRCULO_RELLENO
};

typedef struct _COLOR
{
	int r;
	int g;
	int b;
}COLOR;

class Vertice;

/**********************************************************************************************/
/* Esta clase modela un pipeline grafico 2D.												  */
/* provee servicios para indicar el tipo de primitiva grafica								  */
/* y los colores asociados.																	  */
/* Tambi�n permite definir transformaciones las cuales se aplicar�n							  */
/* de manera compuesta a los v�rtices en el momento de renderizarlos.					      */
/* El usuario deber� definir las dimensiones y posici�n de la ventana de					  */
/* mundo y del vierport.																	  */
/**********************************************************************************************/
class CPipeline2D
{
private:
	PRIMITIVA_2D primitiva;
	COLOR colorLinea;
	COLOR colorRelleno;
	COLOR colorPunto;
	Matriz3t mTransformacion, mVista; // Matriz de transformacion, matriz de vista
	Vertice ptoMinMundo;	  // Punto inferior izquierdo de las coordenadas del mundo.
	Vertice ptoMinViewport;	  // Punto inferior izquierdo de las coordenadas del viewport.
	float anchoMundo;		  // Ancho de la ventana del mundo.
	float altoMundo;		  // Alto de la ventana del mundo.
	int anchoViewport;		  // Ancho de la ventana del viewport.
	int altoViewport;		  // Alto de la ventana del viewport.
	static CPipeline2D* pipe;
	static bool instanceFlag;

/**********************************************************************************************/
/* Constructor																				  */
/**********************************************************************************************/
	CPipeline2D ();

public:

/**********************************************************************************************/
/* Destructor																				  */
/**********************************************************************************************/
	~CPipeline2D ()
	{
		instanceFlag = false;
	}

/**********************************************************************************************/
/* M�todo usado para obtener la instancia del singleton CPipeline2D							  */
/**********************************************************************************************/
	static CPipeline2D* getInstancia();

/**********************************************************************************************/
/* Configuracion de la primitiva2D															  */
/* param prim2d Identificador que indica el tipo de primitiva2D								  */
/**********************************************************************************************/
	void Primitiva2D (PRIMITIVA_2D prim2d);

/**********************************************************************************************/
/* Este m�todo permite configurar el color con el cual ser�n dibujados						  */
/* los segmentos de linea, circulo, y el contorno del pol�gono.								  */
/* param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255			  */
/* param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255			  */
/* param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255			  */											  
/**********************************************************************************************/
	void ColorLinea (int r, int g, int b);

/**********************************************************************************************/
/* Este m�todo permite configurar el color con el cual ser�n rellenado						  */
/* el pol�gono en caso de ser indicado dibujar pol�gonos rellenos.							  */
/* param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255			  */
/* param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255			  */
/* param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255			  */											  
/**********************************************************************************************/
	void ColorRelleno (int r, int g, int b);

/**********************************************************************************************/
/* Este m�todo permite configurar el color con el cual ser�n los puntos cuando				  */
/* se indique trabajar con la primitiva 2D PUNTO											  */
/* param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255			  */
/* param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255			  */
/* param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255			  */											  
/**********************************************************************************************/
	void ColorPunto	(int r, int g, int b);

/**********************************************************************************************/
/*	Trasformaciones																			  */
/**********************************************************************************************/

/**********************************************************************************************/
/* Inicializa la matriz de Transformaciones a la Matriz Identidad.							  */
/* Este m�todo destruye el contenido de la matriz de Transformaciones						  */
/**********************************************************************************************/
	void CargarIdentidad();

/**********************************************************************************************/
/* Define una traslaci�n.																	  */
/* La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Traslaci�n			  */
/* MTransf = MTransf * MTraslaci�n															  */
/* param tx Indica la traslaci�n en el eje x												  */
/* param ty Indica la traslaci�n en el eje y												  */
/**********************************************************************************************/
	void Traslacion (float tx, float ty);

/**********************************************************************************************/
/* Define una rotaci�n sobre un punto.														  */
/* La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Rotaci�n			  */
/* MTransf = MTransf * MRotaci�n															  */
/* param rx Coordenada x del centro de rotaci�n												  */
/* param ry Coordenada y del centro de rotacion												  */
/* param alfa �ngulo de rotacion expresado en grados.										  */
/**********************************************************************************************/
	void Rotacion (float rx, float ry, float alfa);

/**********************************************************************************************/
/* brief Define un escalado.																  */
/* La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Escalado			  */
/* MTransf = MTransf * MEscalado															  */
/* param ex Indica el factor de escalado en el eje x										  */
/* param ey Indica el factor de escalado en el eje y										  */
/**********************************************************************************************/
	void Escalado (float ex, float ey);

/**********************************************************************************************/
/* brief Define el Viewport																	  */
/* Este metodo permite definir la posici�n en la pantalla y las dimensiones					  */
/* del viewport donde ser� renderizada la escena.											  */
/* param x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.	  */
/* param y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.     */
/* param ancho Ancho del viewport expresado en pixels.										  */
/* param alto Alto del viewport expresado en pixels.										  */
/**********************************************************************************************/
	void Viewport (int x0, int y0, int ancho, int alto);

/**********************************************************************************************/
/* Define la ventana de mundo																  */
/* Este metodo permite definir la posici�n en la pantalla y las dimensiones					  */
/* del viewport donde ser� renderizada la escena.											  */
/* param x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.	  */
/* param y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.     */
/* param ancho Ancho del viewport expresado en pixels.										  */
/* param alto Alto del viewport expresado en pixels.										  */
/**********************************************************************************************/
	void VentanaMundo (float u0, float v0, float ancho, float alto);
	
/**********************************************************************************************/
/* Este m�todo permite dibujar en funci�n de los datos ingresados y la configuraci�n		  */
/* realizada del Pipeline realizada previamente.											  */
/* Este m�todo no destruye (borra) lo que se haya dibujado hasta el momento.			      */
/* param p_vertice Puntero al buffer que contiene los v�rtices.								  */
/* param nro_vertices N�mero de v�rtices contenidos en el buffer							  */
/**********************************************************************************************/
	void Dibujar (Vertice * p_vertice, unsigned int nro_vertices);

/**********************************************************************************************/
/* Borra la pantalla.																		  */
/**********************************************************************************************/
	void ClearScreen();

/**********************************************************************************************/
/* Getters and setters																		  */
/**********************************************************************************************/
	setPtoMinMundo(Vertice v);
	Vertice getPtoMinMundo() const;
	setPtoMinViewport(Vertice v);
	Vertice getPtoMinViewport() const;
	setAnchoMundo(float ancho);
	float getAnchoMundo() const;
	setAltoMundo(float alto);
	float getAltoMundo() const;
	setAnchoViewport(int ancho);
	int getAnchoViewport() const;
	setAltoViewport(int alto);
	int getAltoViewport() const;



private: 

/**********************************************************************************************/
/* Aplica las transformaciones afines.														  */
/**********************************************************************************************/
	void AplicarTransf(Matriz3t& m, const Vertice* p_vertice,Vertice* transf,
						unsigned int nro_vertices);

/**********************************************************************************************/
/* Calcula la matriz de vista, encargada de hacer los cambios de coordenadas desde la ventana */
/* del mundo al viewport.																	  */
/**********************************************************************************************/
	void calcularMVista();
};

