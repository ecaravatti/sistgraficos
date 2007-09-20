// Segmento.cpp: implementation of the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#include "Segmento.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Segmento::Segmento(Punto &inicio, Punto &fin)
{
	//Invariante: El segmento siempre se recorre de izquierda a derecha.
	if (inicio.getX() < fin.getX())
	{
		puntoInicio = inicio;
		puntoFin = fin;
	}else
	{
		puntoInicio = fin;
		puntoFin = inicio;
	}
}

Segmento::~Segmento()
{

}

//////////////////////////////////////////////////////////////////////
// Getters y Setters
//////////////////////////////////////////////////////////////////////
Punto Segmento::getPuntoFin()
{
	return (puntoFin);
}

Punto Segmento::getPuntoInicio()
{
	return (puntoInicio);
}

void Segmento::setPuntoFin(Punto &p)
{
	//Controlo que se mantenga el invariante de que se recorra el segmento de izquierda a derecha.
	if (puntoInicio.getX() < p.getX())
		puntoFin = p;
	else 
	{
		puntoFin = puntoInicio;
		puntoInicio = p;
	}
}

void Segmento::setPuntoInicio(Punto &p)
{
	//Controlo que se mantenga el invariante de que se recorra el segmento de izquierda a derecha.
	if (puntoFin.getX() > p.getX())
		puntoInicio = p;
	else
	{
		puntoInicio = puntoFin;
		puntoFin = p;
	}
}
//////////////////////////////////////////////////////////////////////
// Otros métodos
//////////////////////////////////////////////////////////////////////
void Segmento::dibujarInicio()
{
	puntoInicio.dibujar();
}

void Segmento::dibujarFin()
{
	puntoFin.dibujar();
}

Segmento Segmento::transladarAlOrigen()
{
	Punto p1 = (*new Punto(0,0));


	Punto p2 = (*new Punto( (getPuntoFin().getX() - getPuntoInicio().getX()),(getPuntoFin().getY() - getPuntoInicio().getY()) ) ) ;

	Segmento* seg = new Segmento(p1,p2);
	
	return *seg;
}

void Segmento::dibujarDDA()
{
	// Calculo la pendiente de la recta m.
	float m = (float)(getPuntoFin().getY() - getPuntoInicio().getY())/(float)(getPuntoFin().getX()-getPuntoInicio().getX());

	if (abs(m) <= 1)
	{
		float y = getPuntoInicio().getY();
		for (int x = getPuntoInicio().getX(); x < getPuntoFin().getX(); x++)
		{
			glVertex2i(x,(int) floor(y + 0.5));
			y+=m;
		}
	}
	else if (m > 1)
	{
		float x = getPuntoInicio().getX();
		for (int y = getPuntoInicio().getY(); y < getPuntoFin().getY(); y++)
		{
			glVertex2i((int)floor(x+0.5),y);
			x+=1/m;
		}
	}else // si (m < -1)
	{
		float x = 0;
		for (int y = getPuntoInicio().getY(); y > getPuntoFin().getY(); y--)
		{
			glVertex2i((int)floor(x+0.5),y);
			x-=1/m;
		}
	}
}