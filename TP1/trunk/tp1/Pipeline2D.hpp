/// \file Pipeline2D.hpp
/// \details La clase CPipeline2D modela un pipeline grafico 2D que permite dibujar pol�gonos,
/// poligonos rellenos, segmentos de rectas, puntos y circulos.
/// El pipeline dibuja utilizando la API OpenGL
/// Ofrece metodos que permiten configurar el pipeline antes de ingresar el conjunto de vertices.
/// \author 66.71 Sistemas Graficos 2do Cuatrimestre de 2007
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



/// \brief La clase vertice debe ser especificada e implementada
class Vertice;

/// \details Esta clase modela un pipeline grafico 2D.
/// provee servicios para indicar el tipo de primitiva grafica
/// y los colores asociados.
/// Tambi�n permite definir transformaciones las cuales se aplicar�n
/// de manera compuesta a los v�rtices en el momento de renderizarlos.
/// El usuario deber� definir las dimensiones y posici�n de la ventana de
/// mundo y del vierport.
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


	/// \brief Constructor 
	CPipeline2D ();

public:
	/// \brief Destructor
	~CPipeline2D ()
	{
		instanceFlag = false;
	}


	static CPipeline2D* getInstancia();

	
	/// \brief Configuracion de la primitiva2D
	/// \param prim2d Identificador que indica el tipo de primitiva2D
	void Primitiva2D (PRIMITIVA_2D prim2d);

	/// \brief Este m�todo permite configurar el color con el cual ser�n dibujados
	/// los segmentos de linea, circulo, y el contorno del pol�gono.
	/// \param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255
	/// \param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255
	/// \param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255
	void ColorLinea (int r, int g, int b);

	/// \brief Este m�todo permite configurar el color con el cual ser�n rellenado 
	/// el pol�gono en caso de ser indicado dibujar pol�gonos relle�os.
	/// \param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255
	/// \param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255
	/// \param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255
	void ColorRelleno (int r, int g, int b);

	/// \brief Este m�todo permite configurar el color con el cual ser�n los puntos cuando
	/// se indique trabajar con la primitiva 2D PUNTO
	/// \param r Intenisidad de la componente rojo del color. Rango de valores: 0 - 255
	/// \param g Intenisidad de la componente verde del color. Rango de valores: 0 - 255
	/// \param b Intenisidad de la componente azul del color. Rango de valores: 0 - 255
	void ColorPunto	(int r, int g, int b);
	
	/// \section Trasformaciones
	
	/// \brief Inicializa la matriz de Transformaciones a la Matriz Identidad.
	/// Este m�todo destruye el contenido de la matriz de Transformaciones
	void CargarIdentidad();
	 
	/// \brief Define una traslaci�n. 
	/// <br>La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Traslaci�n
	/// <br><b>MTransf = MTransf * MTraslaci�n<\b>
	/// \param tx Indica la traslaci�n en el eje x
	/// \param ty Indica la traslaci�n en el eje y
	void Traslacion (float tx, float ty);

	/// \brief Define una rotaci�n sobre un punto. 
	/// <br>La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Rotaci�n
	/// <br><b>MTransf = MTransf * MRotaci�n<\b> 
	/// \param rx Coordenada x del centro de rotaci�n
	/// \param ry Coordenada y del centro de rotacion
	/// \param alfa �ngulo de rotacion expresado en grados.
	void Rotacion (float rx, float ry, float alfa);

	/// \brief Define un escalado. 
	/// <br>La matriz de Transfomaci�n es multiplicada a derecha por la matriz de Escalado
	/// <br><b>MTransf = MTransf * MEscalado<\b>
	/// \param ex Indica el factor de escalado en el eje x
	/// \param ey Indica el factor de escalado en el eje y 
	void Escalado (float ex, float ey);


	/// \brief Define el Viewport
	/// <br>Este metodo permite definir la posici�n en la pantalla y las dimensiones
	/// del viewport donde ser� renderizada la escena.
	/// \param x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.
	/// \param y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.  
	/// \param ancho Ancho del viewport expresado en pixels.
	/// \param alto Alto del viewport expresado en pixels.
	void Viewport (int x0, int y0, int ancho, int alto);

	/// \brief Define la ventana de mundo
	/// <br>Este metodo permite definir la posici�n en la pantalla y las dimensiones
	/// del viewport donde ser� renderizada la escena.
	/// \param x0 Coordenada x del extremo inferior izquierdo del viewport expresado en pixels.
	/// \param y0 Coordenada y del extremo inferior izquierdo del viewport expresado en pixels.  
	/// \param ancho Ancho del viewport expresado en pixels.
	/// \param alto Alto del viewport expresado en pixels.
	void VentanaMundo (float u0, float v0, float ancho, float alto);
	

	/// \brief Este m�todo permite dibujar en funci�n de los datos ingresados y la configuraci�n
	/// realizada del Pipeline realizada previamente.
	/// Este m�todo no destruye (borra) lo que se haya dibujado hasta el momento.
	/// \param p_vertice Puntero al buffer que contiene los v�rtices.
	/// \param nro_vertices N�mero de v�rtices contenidos en el buffer
	void Dibujar (Vertice * p_vertice, unsigned int nro_vertices);

	/// \brief Borra la pantalla.
	void ClearScreen();

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
	void AplicarTransf(Matriz3t& m, const Vertice* p_vertice,Vertice* transf,
						unsigned int nro_vertices);

	void calcularMVista();
};

