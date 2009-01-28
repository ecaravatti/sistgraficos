// Velocidad.cpp: implementation of the Velocidad class.
//
//////////////////////////////////////////////////////////////////////

#include "Velocidad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*****************************************************************************************/

Velocidad::Velocidad()
{}
/*****************************************************************************************/
Velocidad::Velocidad(float vel, int ang)
{
	if (vel<0)
		vel = 0;
	modulo = vel;
	velX = vel* (float)cos(toRadians(ang));
	velY = vel*(float)sin(toRadians(ang));
	
}

/*****************************************************************************************/

Velocidad::Velocidad(float x, float y){
	velX = x;
	velY = y;
	calcularModulo();
	angulo=calcularAngulo();
}

/*****************************************************************************************/

Velocidad::~Velocidad()
{}

/*****************************************************************************************/

//Getters		
float Velocidad::getVelX(){
	return velX;
}

/*****************************************************************************************/

float Velocidad::getVelY() {
	return velY;
}

/*****************************************************************************************/

float Velocidad::getModulo(){
	return modulo; 
}

/*****************************************************************************************/

int Velocidad::getAngulo(){
	return angulo;
}

/*****************************************************************************************/
	
//Setters
void Velocidad::setVelX(float vX) 
{
	this->velX = vX;
	calcularModulo(); //Al cambiar una coordenada del vector hay que actualizar el módulo del mismo.
	angulo=calcularAngulo(); //idem para el angulo
}

/*****************************************************************************************/

void Velocidad::setVelY(float vY) 
{
	this->velY = vY;
	calcularModulo(); //Al cambiar una coordenada del vector hay que actualizar el módulo del mismo.
	angulo=calcularAngulo();//idem para el angulo
}

/*****************************************************************************************/

void Velocidad::setVelocidad(float v,int ang)
{
	if (v<0)
		v = 0;
	modulo = v;
	angulo=ang;
	velX = modulo* (float)cos(toRadians(ang));
	velY = modulo* (float)sin(toRadians(ang));
}

/*****************************************************************************************/	

void Velocidad::calcularModulo(){
	modulo =(float) sqrt(pow(velX, 2) + pow(velY, 2));
}

/*****************************************************************************************/

int Velocidad::calcularAngulo(){
	if (velX>0 && velY>0)
		return (int)toDegrees((float)atan(velY/velX));
	else {
		if (velX>0 && velY<0)
			return(int)(360 + toDegrees((float)atan(velY/velX)));				
		else {
			if (velX<0)
				return (int)(toDegrees((float)atan(velY/velX))+ 180);
			else{
				if (velY>0) // && velX=0
					return 90;
				else // velX=0 && velY<0
					return 270;
			}
		}
	}
}

/*****************************************************************************************/
	
float Velocidad::toRadians(int ang){
	return ((float)(ang*PI)/180);
}

/*****************************************************************************************/

float Velocidad::toDegrees(float ang){
	return ((ang*180)/(float)PI);
}

/*****************************************************************************************/
