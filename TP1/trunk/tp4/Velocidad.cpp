// Velocidad.cpp: implementation of the Velocidad class.
//
//////////////////////////////////////////////////////////////////////

#include "Velocidad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Velocidad::Velocidad()
{

}

/**
 * Constructor 
 * @param double v: representa el modulo de la velocidad.
 * @param int ang: representa el angulo que da la direccion del vector velocidad.
 */	
Velocidad::Velocidad(double vel, int ang)
{

	if (vel<0)
		vel = 0;
	modulo = vel;
	velX = vel* cos(toRadians(ang));
	velY = vel*sin(toRadians(ang));
	
}

/**
 *Constructor 
 * @param double x 
 * @param double y
 * 	Representan las coordenadas en x e y del vector velocidad.
 */
Velocidad::Velocidad(double x, double y){
	velX = x;
	velY = y;
	CalcularModulo();
}


Velocidad::~Velocidad()
{

}


//Getters		
double Velocidad::getVelX() 
{
	return velX;
}

double Velocidad::getVelY() 
{
	return velY;
}

double Velocidad::getVelocidad()
{
	return modulo; 
}




	
//Setters
void Velocidad::setVelX(double vX) 
{
	this->velX = vX;
	CalcularModulo(); //Al cambiar una coordenada del vector hay que actualizar el módulo del mismo.
}

void Velocidad::setVelY(double vY) 
{
	this->velY = vY;
	CalcularModulo(); //Al cambiar una coordenada del vector hay que actualizar el módulo del mismo.
}

void Velocidad::setVelocidad(double v,int ang)
{
	if (v<0)
		v = 0;
	modulo = v;
	velX = modulo*cos(toRadians(ang));
	velY = modulo*sin(toRadians(ang));
}

	
	
/**
 * Calcula el modulo del vector velocidad; y actualiza dicho atributo.
 */
void Velocidad::CalcularModulo()
{
	modulo = sqrt(pow(velX, 2) + pow(velY, 2));
}

/**
 * 
 * @return El angulo que da la dirección del vector velocidad en grados.
 */
int Velocidad::calcularAngulo(){
	if (velX>0 && velY>0)
		return (int)toDegrees(atan(velY/velX));
	else {
		if (velX>0 && velY<0)
			return(int)(360 + toDegrees(atan(velY/velX)));				
		else {
			if (velX<0)
				return (int)(toDegrees(atan(velY/velX))+ 180);
			else{
				if (velY>0) // && velX=0
					return 90;
				else // velX=0 && velY<0
					return 270;
			}
		}
	}
}
	
double Velocidad::toRadians(int ang)
{
	return (ang*PI)/180;
}

double Velocidad::toDegrees(double ang)
{
	return (ang*180)/PI;
}




