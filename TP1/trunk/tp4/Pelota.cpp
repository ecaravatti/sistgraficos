// Pelota.cpp: implementation of the Pelota class.
//
//////////////////////////////////////////////////////////////////////

#include "Pelota.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pelota::Pelota()
{
	posInicial.x = 3.75;
	posInicial.y = 1.0;
	posInicial.z = 0.0;
	posActual.x = 3.75;
	posActual.y = 1.0;
	posActual.z = 0.0;
	masa = 10;
	fuerzaRozamiento =0.35*masa*10;
	aceleracion = 0.3;//fuerzaRozamiento/masa;
	diametro = 1.25*1/4;
	velocidadInicial = Velocidad(2.0f,2.0f);
	velocidad = Velocidad(2.0f,2.0f);
	tiempo=0;
}

Pelota::Pelota(float px, float py, float v, int ang)
{
	tiempo=0;
	posInicial.x = px;
	posInicial.y = py;
	posInicial.z = 0;
	posActual.x = px;
	posActual.y = py;
	posActual.z = 0;
	masa = 100;
	fuerzaRozamiento = 0.35*masa*10;
	aceleracion = fuerzaRozamiento/masa;
	diametro = 30;
	velocidadInicial = Velocidad(v,ang);
	velocidad = Velocidad(v,ang);
}

Pelota::~Pelota()
{

}

int Pelota::getAngulo() {
	return velocidadInicial.getAngulo();
}

float Pelota::getPosX(){
	return posActual.x;
}
	
float Pelota::getPosY(){
	return posActual.y;
}
	
float Pelota::getPosInicialX(){ 
	return posInicial.x;
}

float Pelota::getPosInicialY(){ 
	return posInicial.y; 
}

Punto Pelota::getPosActual(){
	return posActual;
}
	
float Pelota::getVelocidadInicial() {
	return velocidadInicial.getModulo();
}
	
float Pelota::getVelocidad() {
	return velocidad.getModulo();
}

Velocidad Pelota::getVectorVelocidad(){
	return velocidad;
}

float Pelota::getDiametro() {
	return diametro;
}

//	setters	
void Pelota::setPosInicial(Punto posInicial) {
	this->posInicial = posInicial;
}

void Pelota::setAngulo(int angulo) {
	velocidad.setVelocidad(getVelocidad(),angulo);
}

void Pelota::setPosInicialX(float px){ 
	posInicial.x = px;
}

void Pelota::setPosInicialY(float py){ 
	posInicial.y = py;
}

void Pelota::setPosX(float x){
	posActual.x = x;
}

void Pelota::setPosY(float y){
	posActual.y = y;
}

void Pelota::setVelocidadInicial(Velocidad v){
	//float vMax=calcularVelocidadMaxima();
	float nvel=v.getModulo();

	/*if ( nvel > vMax )
		nvel=vMax;
*/
	this->velocidadInicial.setVelocidad(nvel,v.getAngulo());
	this->setAngulo(v.getAngulo());
	this->velocidad.setVelocidad(nvel,v.getAngulo());
	this->posInicial=posActual;
	tiempo=0;
	tiempoAnt=0;

}

void Pelota::setVelocidad(float velocidad) {
		if (velocidad < 0)
			velocidad = 0;
		/*if (velocidad>	calcularVelocidadMaxima())	
			velocidad = calcularVelocidadMaxima();*/
		//this->velocidad.setVelocidad(velocidad,angulo);
		this->velocidad.setVelocidad(velocidad,this->velocidadInicial.getAngulo());
}

	
void Pelota::setVectorVelocidad(Velocidad v){
	velocidad=v;
}
	
/**
 * Calcula la posicion en la coordenada X luego de un tiempo "t"
 * @param float t 
 */
void Pelota::calcularPosicionX(float t){
	//posActual.x = (posInicial.x + velocidadInicial.getVelX()*(t-tiempoRebote) +0.5*aceleracion*cos(Velocidad::toRadians(angulo))*pow(t-tiempoRebote,2));
	//posActual.x = (posInicial.x + velocidadInicial.getVelX()*(t-t0) -0.5*aceleracion*cos(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t-t0,2));
	posActual.x = (posInicial.x + velocidadInicial.getVelX()*(t) -0.5*aceleracion*cos(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t,2));
}

/**
 * Calcula la posicion en la coordenada Y luego de un tiempo "t"
 * @param float t
 */
void Pelota::calcularPosicionY(float t){
	//posActual.y = (posInicial.y + velocidadInicial.getVelY()*(t-tiempoRebote) +0.5*aceleracion*sin(Velocidad::toRadians(angulo))*pow(t-tiempoRebote,2));
	//posActual.y = (posInicial.y + velocidadInicial.getVelY()*(t-t0) -0.5*aceleracion*sin(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t-t0,2));
	posActual.y = (posInicial.y + velocidadInicial.getVelY()*(t) -0.5*aceleracion*sin(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t,2));
}
	
	
void Pelota::calcularVelocidad(float t){
	//velocidad.setVelocidad(velocidadInicial.getModulo()+aceleracion*(t-tiempoRebote),angulo);
	//velocidad.setVelocidad(velocidadInicial.getModulo()-aceleracion*(t-t0),velocidadInicial.getAngulo());
	velocidad.setVelocidad(velocidadInicial.getModulo()-aceleracion*(t),velocidadInicial.getAngulo());
}


/**
 * Este metodo se fija si se produce un choque la pelota y un solido. 
 * Para esto se fija si la distancia entre ellas es menor a la suma de sus radios
 * @param Solido <b>solido</b> 
 * @return <b>bool</b> Retorna true si se produjo el choque; 
 * caso contrario retorna false
 */
bool Pelota::seChoca(Solido* solido){
	if (posActual.distancia(solido->getPosicion()) <= (diametro/2 + solido->getDiametro()/2)) 
		return true;
	return false;
}

/**
 * Este metodo se fija si se produce un choque entre la esfera y la pared 
 * Para esto se fija si la distancia entre ellas es menor al radio de la esfera
 * @param Pared <b>p</b> 
 * @return <b>boolean</b> Retorna true si se produjo el choque; 
 * caso contrario retorna false
 */
bool Pelota::seChoca(Pared* p){

	//Primero calculo una recta perpendicular a la direccion de la pared que pase por el punto p.
	float x,y; //son las coordenadas de la direccion de la recta a calcular.
	if (p->getDireccion().x==0) {
		y=0;
		x=1;
	}
	else{
		if(p->getDireccion().y==0){
	
		x=0;
		y=1;
		}
		else {
			x=1;
			y= -p->getDireccion().x/p->getDireccion().y;
		}
	}// la nueva recta queda configurada como L1: r(x,y) + p ; donde r pertenece a los reales.
	
	//se calcula la interseccion entre la recta L1 y la pared,el punto p2 será el mas cercano a la esfera.
	float t = (x*(p->getOrigen().y-posActual.y)+ y*(posActual.x-p->getOrigen().x))/(y*p->getDireccion().x-x*p->getDireccion().y);
	Punto p2;
	p2.x = (t*p->getDireccion().x+p->getOrigen().x);
	p2.y = (t*p->getDireccion().y+p->getOrigen().y); 

	if (posActual.distancia(p2)<= diametro)
		return true;
	return false;
}
	
/**
 * Este método calcula la posición y velocidad a la que llega la esfera 
 * luego de un periodo de tiempo <b>tiempo</b>; y agrega esta nueva huella a 
 * la trayectoria de la misma.
 * @param float <b>tiempo</b>
 */

void Pelota::mover(){
	tiempoAnt=tiempo;
	tiempo+=0.05;
	//std::cout<<"getvelocidad---> "<<getVelocidad()<<std::endl;
	if (getVelocidad()>0){ 
				calcularPosicionX(tiempo); 
				calcularPosicionY(tiempo); 
				calcularVelocidad(tiempo);
				//std::cout<<std::endl;
				//std::cout<<"t = "<<tiempo<<std::endl;
				//std::cout<<"Posicion: "<<this->getPosX()<<" , "<<getPosY()<<std::endl;
				//std::cout<<"Velocidad: "<<velocidad.getVelX()<<" , "<<velocidad.getVelY()<<std::endl;
				//std::cout<<std::endl<2.4<std::endl<<std::endl;
	}
	buscarChoques(tiempo);
	buscarChoquesPared();// t0=tiempo;
}
/**
 * Calcula el ángulo de incidencia cuando la esfera choca contra una pared.
 * @param Punto p es la dirección de la pared contra la que se choca.
 * @return El angulo de incidencia del choque en grados. 
 */
int Pelota::calcularAnguloIncidencia(Punto p){
	int angulo=velocidadInicial.getAngulo();
	if ((getAngulo()>=0)&&(getAngulo()<=90)){
		if (p.y == 0)  return (90-angulo);
		else /*if p.x==0*/ return angulo;		
	}
	else{
		if((getAngulo()>90)&&(getAngulo()<=180)){
			if (p.y==0)  return (angulo-90);
			else /*if p.x==0*/ return (180-angulo);
		}
		else{
			if((getAngulo()>180)&&(getAngulo()<=270)){
				if (p.y==0)  return (270-angulo);
				else /*if p.x==0*/ return (angulo-180);
			}
			else {  //if((getAngulo()>270)&&(getAngulo()<=360))
				if (p.y==0)  return (angulo-270);
				else /*if p.x==0*/ return (360-angulo);
			}
		}
	}
}
	
/**
 * Este metodo pasa el angulo de reflexion al sistema de coordenadas fijo
 * @param Punto p Es la dirección  de la recta contra la que chocó la esfera
 * @param int angReflexion Es el angulo de reflexion del choque contra la pared 
 * medido desde la recta normal a la misma
 */
void Pelota::anguloReflexionASistFijo(Punto p,int angReflexion){
	if ((getAngulo()>=0)&&(getAngulo()<=90)){
		if (p.y==0)  setAngulo(270+angReflexion);
		else /*if p.x==0*/ setAngulo(180-angReflexion);
	}
	else{
		if((getAngulo()>90)&&(getAngulo()<=180)){
			if (p.y==0)  setAngulo(270-angReflexion);
			else /*if p.x==0*/ setAngulo(angReflexion);
		}
		else{
			if((getAngulo()>180)&&(getAngulo()<=270)){
				if (p.y==0)  setAngulo(90+angReflexion);
				else /*if p.x==0*/ setAngulo(360-angReflexion);
			}
			else {  //if((getAngulo()>270)&&(getAngulo()<=360))
				if (p.y==0)  setAngulo(90-angReflexion);
				else /*if p.x==0*/ setAngulo(180 + angReflexion);
			}
		}
	}
}
	
	
	
/**
 * Este método calcula las nuevas velocidades de la esfera cuando choca contra una pared; y crea un rebote 
 * con los datos del choque que agrega en las lista de rebotes de la esfera.
 * @param Pared p Es la pared contra la que choca la esfera.
 */
void Pelota::chocar(Pared* p, float t){
	int angIncidencia=0;
	
	//int r = (rand() % 40);	// Numero random entre 0 y 40.

	angIncidencia=calcularAnguloIncidencia(p->getDireccion());
	
	setPosInicialX(getPosX());
	setPosInicialY(getPosY());
	
	
	if (getVelocidad() <= 0){
		setVelocidad(0);
	}
	
	Velocidad velocidadIncidencia = Velocidad(velocidad.getVelX(),velocidad.getVelY());
	
//	setTiempoRebote(t);
// TODO: settear el tiempo a 0???	
	setVelocidad(calcularVelocidadReflexion(angIncidencia,p->getDireccion()));
	
	if (getVelocidad() <= 0){
		setVelocidad(0);
	}
	
	//setVelocidadInicial(getVelocidad());
	velocidadInicial.setVelocidad(getVelocidad(),velocidadInicial.getAngulo());
}
	
/**
 * Calcula la velocidad máxima para que la esfera no avance mas de su
 * diametro en 0,1 segundos.
 * @return float - La velocidad maxima calculada
 */
/*float Pelota::calcularVelocidadMaxima(){
	return((this->getDiametro()-0.005*this->getAceleracion())/0.1);
}*/
	
/////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Este metodo calcula el angulo de reflexión en el choque contra una pared
 * @return int Devuelve el angulo en grados
 */
int Pelota::calcularAnguloReflexion(int angIncidencia){
	
	int reflexion = (int)(Velocidad::toDegrees(atan(tan(Velocidad::toRadians(angIncidencia))/(0.33/100.0))));
	if (reflexion < 0)
		reflexion = 360 + reflexion;
	return(reflexion);
}

/**
 * Calcula la velocidad de reflexión de la esfera luego de que choca con una pared. Para esto
 * tambien le asigna un nuevo ángulo que le da la direccion de movimiento a la esfera.
 * @param int angIncidencia: angulo de incidencia del choque, medido desde la normal a 
 * la pared.
 * @param Punto dirPared: es la direccion de la pared contra la que se choca, sirve para calcular 
 * el angulo de reflexión.
 * @return float que es el módulo de la velocidad de reflexión de la esfera.
 */
float Pelota::calcularVelocidadReflexion(int angIncidencia,Punto dirPared){
	int angReflexion = calcularAnguloReflexion(angIncidencia);
	anguloReflexionASistFijo(dirPared,angReflexion);
	return(getVelocidad()*(sin((Velocidad::toRadians(angIncidencia))/(sin(Velocidad::toRadians(angReflexion))))));
}

/**
 * Este metodo resuelve el choque entre esferas.
 * @param Esfera e: Esfera contra la que choca
 * @param float tiempo: Tiempo en el que se produce la colision
 */

void Pelota::chocar(Solido* solido){
	float x1,y1;	//Centro solido
	float x2,y2;	//Centro pelota
	float ki,kn,kr;

	float Ix,Iy,Nx,Ny,Rx,Ry;
	
	x1=solido->getPosicion().x;
	y1=solido->getPosicion().y;
	Velocidad nVel;

	x2=posActual.x;
	y2=posActual.y;

	kn=1/sqrt( pow(x2-x1,2) + pow(y2-y1,2) );
	ki=1/sqrt( pow(velocidad.getVelX(),2) + pow(velocidad.getVelY(),2) );

	Ix=velocidad.getVelX()*ki;
	Iy=velocidad.getVelY()*ki;

	Nx=kn*(x2-x1);
	Ny=kn*(y2-y1);

	Rx=2*(-Ix*Nx-Iy*Ny)*Nx + Ix;
	Ry=2*(-Ix*Nx-Iy*Ny)*Ny + Iy;
	
	kr=1/sqrt(pow(Rx,2) + pow(Ry,2));

	Rx*=kr;
	Ry*=kr;

	Rx*=velocidad.getModulo();
	Ry*=velocidad.getModulo();

	nVel.setVelX(Rx);
	nVel.setVelY(Ry);

	tiempo=tiempoAnt+0.025;
	this->calcularPosicionX(tiempo);
	this->calcularPosicionY(tiempo);

	setVelocidadInicial(nVel);
}


void Pelota::cargarPared(Pared* pared){
	listaParedes.push_back(pared);
}

void Pelota::cargarSolido(Solido* solido){
	listaSolidos.push_back(solido);
}

void Pelota::eliminarSolido(Solido* solido){
	std::list<Solido*>::iterator it;
	for (it=listaSolidos.begin(); it!=listaSolidos.end(); it++)
		if ((*it)->getPosicion()==solido->getPosicion()){
			listaSolidos.erase(it);
			return;
		}
}

void Pelota::buscarChoques(float tiempo){
	//Choques con solidos
	std::list<Solido*>::iterator itSolidos;
	for (itSolidos=listaSolidos.begin(); itSolidos!=listaSolidos.end(); itSolidos++)
		if (this->seChoca(*itSolidos))
			chocar(*itSolidos);

	//Choques con paredes
	//std::list<Pared*>::iterator itParedes;
	//for (itParedes=listaParedes.begin(); itParedes!=listaParedes.end(); itParedes++)
		//if (this->seChoca(*itParedes)) chocar(*itParedes,tiempo);

}

void  Pelota::buscarChoquesPared(){
	Velocidad velRebote;

	if ((float) (this->posActual.x+this->diametro/2) >=7.5f ||
		(float) (this->posActual.x-this->diametro/2) <=0.0f )
	{
		velRebote.setVelX(-this->velocidad.getVelX());
		velRebote.setVelY(this->velocidad.getVelY());
		
		tiempo=tiempoAnt+0.025;
		this->calcularPosicionX(tiempo);
		this->calcularPosicionY(tiempo);

		this->setVelocidadInicial(velRebote);
	}


	if ((float) (this->posActual.y+this->diametro/2) >=10.0f ||
		(float) (this->posActual.y-this->diametro/2) <=0.0f )
	{
		velRebote.setVelX(this->velocidad.getVelX());
		velRebote.setVelY(-this->velocidad.getVelY());

		tiempo=tiempoAnt+0.025;
		this->calcularPosicionX(tiempo);
		this->calcularPosicionY(tiempo);

		this->setVelocidadInicial(velRebote);
	}

}
	

void Pelota::dibujar_pelota(){
	GLfloat mat_ambient_esfera[] = {0.1, 0.1, 0.1, 1.0f};
	//GLfloat mat_diffuse_esfera[] = {0.1, 0.1, 0.1, 1.0f};//Gris oscuro
	GLfloat mat_diffuse_esfera[] = {0.3,0.3, 0.3, 1.0f}; //Gris clarito
	//GLfloat mat_diffuse_esfera[] = {0.1, 0.6, 0.1, 1.0f};//Verde
	GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_esfera);
	glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glTranslatef (this->getPosX(), this->getPosY(), 1.25*1/8);
		glutSolidSphere(1.25*1/8,25,25);

	glPopMatrix();

}
