// Segmento.h: interface for the Segmento class.
//
//////////////////////////////////////////////////////////////////////
#include "Punto.h"
#include <math.h>


class Segmento  
{
private:
	Punto puntoInicio;
	Punto puntoFin;

public:
	//Getters y Setters
	void setPuntoInicio(Punto &p);
	void setPuntoFin(Punto &p);
	Punto getPuntoInicio();
	Punto getPuntoFin();

	//Otros métodos
	Segmento(Punto &inicio, Punto &fin);	//Constructor.
	virtual ~Segmento();	//Destructor.
	void dibujarInicio();
	void dibujarFin();
	void dibujarDDA();	//Dibuja el segmento usando el algoritmo DDA.
	Segmento transladarAlOrigen();



};


