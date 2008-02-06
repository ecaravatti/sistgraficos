// Pelota.cpp: implementation of the Pelota class.
//
//////////////////////////////////////////////////////////////////////

#include "Pelota.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pelota::Pelota()
{
	posInicial.x = 0;
	posInicial.y = 0;
	posInicial.z = 0;
	posActual.x = 0;
	posActual.y = 0;
	posActual.z = 0;
	masa = 100;
	fuerzaRozamiento = 0.35*masa*10;
	aceleracion = fuerzaRozamiento/masa;
	angulo = 0;
	diametro = 30;
	velocidadInicial = Velocidad(5,0);
	velocidad = Velocidad(5,0);
}

Pelota::Pelota(double px, double py, double v, int ang)
{
	posInicial.x = px;
	posInicial.y = py;
	posInicial.z = 0;
	posActual.x = px;
	posActual.y = py;
	posActual.z = 0;
	masa = 100;
	fuerzaRozamiento = 0.35*masa*10;
	aceleracion = fuerzaRozamiento/masa;
	angulo = ang;
	diametro = 30;
	velocidadInicial = Velocidad(v,ang);
	velocidad = Velocidad(v,ang);
}

Pelota::~Pelota()
{

}


//	getters
double Pelota::getFRozamiento(){
	return(fuerzaRozamiento);
}

int Pelota::getAngulo() {
	return angulo;
}

double Pelota::getPosX(){
	return posActual.x;
}
	
double Pelota::getPosY(){
	return posActual.y;
}
	
double Pelota::getPosInicialX(){ 
	return posInicial.x;
}

double Pelota::getPosInicialY(){ 
	return posInicial.y; 
}

Punto Pelota::getPosActual(){
	return posActual;
}
	
double Pelota::getAceleracion() { 
	return aceleracion;
}
	
double Pelota::getVelocidadInicial() {
	return velocidadInicial.getVelocidad();
}
	
double Pelota::getVelocidad() {
	return velocidad.getVelocidad();
}

Velocidad Pelota::getVectorVelocidad(){
	return velocidad;
}

double Pelota::getDiametro() {
	return diametro;
}
	
double Pelota::getMasa() {
	return masa;
}

