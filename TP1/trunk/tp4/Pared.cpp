// Pared.cpp: implementation of the Pared class.
//
//////////////////////////////////////////////////////////////////////

#include "Pared.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pared::Pared(Punto p1, Punto p2)
{
	// Se le resta p1 a p2 para obtener la direccion de la recta.
	p2.x = p2.x - p1.x;
	p2.y = p2.y - p1.y;

	direccion = p2;
	origen = p1; 

}

Pared::~Pared()
{

}

//Getters
Punto Pared::getOrigen() {
	return origen;
}

Punto Pared::getDireccion() {
	return direccion;
}


/**
 * Este método se fija si la Pelota choca contra la pared. Para esto, se busca la distancia entre 
 * un punto (la Pelota) y una recta (la pared); y se comprueba si es menor al radio de la pelota.
 * @param Pelota
 * @return boolean que devuelve true si la pelota choca contra la pared o false en caso contrario.
 */ /*
bool Pared::seChoca(Pelota pelota){
	Punto p= pelota.getPosActual();
	//Primero calculo una recta perpendicular a la direccion de la pared que pase por el punto p.
	double x,y; //son las coordenadas de la direccion de la recta a calcular.
	if (direccion.x==0) {
		y=0;
		x=1;
	}
	else{
		if(direccion.y==0){
	
		x=0;
		y=1;
		}
		else {
			x=1;
			y= -direccion.x/direccion.y;
		}
	}// la nueva recta queda configurada como L1: r(x,y) + p ; donde r pertenece a los reales.
	
	//se calcula la interseccion entre la recta L1 y la pared,el punto p2 será el mas cercano a la esfera.
	double t = (x*(origen.y-p.y)+ y*(p.x-origen.x))/(y*direccion.x-x*direccion.y);
	Punto p2;
	p2.x = (t*direccion.x+origen.x);
	p2.y = (t*direccion.y+origen.y); 

	if ((sqrt(pow((p.x-p2.x),2) + pow((p.y-p2.y),2))) <= pelota.getDiametro())
		return true;
	return false;
}
*/