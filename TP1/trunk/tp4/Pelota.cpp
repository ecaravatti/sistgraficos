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

//	setters	
void Pelota::setPosInicial(Punto posInicial) {
	this->posInicial = posInicial;
}

void Pelota::setAngulo(int angulo) {
	this->angulo = angulo;
	velocidad.setVelocidad(getVelocidad(),angulo);
}

void Pelota::setPosInicialX(double px){ 
	posInicial.x = px;
}

void Pelota::setPosInicialY(double py){ 
	posInicial.y = py;
}

void Pelota::setPosX(double x){
	posActual.x = x;
}

void Pelota::setPosY(double y){
	posActual.y = y;
}

void Pelota::setVelocidadInicial(double velocidad_i) {
		if (velocidad_i < 0)
			velocidad_i = 0;
		if (velocidad_i>	calcularVelocidadMaxima())	
			velocidad_i = calcularVelocidadMaxima();
		
		this->velocidadInicial.setVelocidad(velocidad_i,angulo);
}

void Pelota::setVelocidad(double velocidad) {
		if (velocidad < 0)
			velocidad = 0;
		if (velocidad>	calcularVelocidadMaxima())	
			velocidad = calcularVelocidadMaxima();
		this->velocidad.setVelocidad(velocidad,angulo);
}

	
void Pelota::setVectorVelocidad(Velocidad v){
	velocidad=v;
}
	
void Pelota::setTiempoRebote(double tiempoRebote) {
	this->tiempoRebote = tiempoRebote;
} 
	

//////////////////////////////////////////////////////////////////////////////////////////////////
/* VER ESTOS METODOS Q LOS TIENE Q HEREDAR!!!
//	métodos abstractos
	
*/

/**
 * Calcula la velocidad de reflexión de la esfera luego de que choca con una pared. Para esto
 * tambien le asigna un nuevo ángulo que le da la direccion de movimiento a la esfera.
 * Esta redefinido para cada clase de esfera.
 * @param int <b>angIncidencia</b> angulo de incidencia del choque, medido desde la normal a 
 * la pared.
 * @param int <b> variacion </b> es la variacion en grados al angulo de reflexión, causada por la
 * irregularidad de la pared.
 * @param Punto <b> dirPared </b> es la direccion de la pared contra la que se choca, sirve para calcular 
 * el angulo de reflexión.
 * @return double que es el módulo de la velocidad de reflexión de la esfera.
 */ /*
public abstract double CalcularVelocidadReflexion(int angIncidencia,int variacion, Punto dirPared);
*/
// otros métodos
	
/**
 * Calcula la posicion en la coordenada X luego de un tiempo "t"
 * @param double t 
 */
//TODO: ver lo del tiempo de rebote!!!
void Pelota::calcularPosicionX(double t){
	posActual.x = (posInicial.x + velocidadInicial.getVelX()*(t-tiempoRebote) +0.5*aceleracion*cos(Velocidad::toRadians(angulo))*pow(t-tiempoRebote,2));
}

/**
 * Calcula la posicion en la coordenada Y luego de un tiempo "t"
 * @param double t
 */
void Pelota::calcularPosicionY(double t){
	posActual.y = (posInicial.y + velocidadInicial.getVelY()*(t-tiempoRebote) +0.5*aceleracion*sin(Velocidad::toRadians(angulo))*pow(t-tiempoRebote,2));
}
	
	
void Pelota::calcularVelocidad(double t){
	velocidad.setVelocidad(velocidadInicial.getVelocidad()+aceleracion*(t-tiempoRebote),angulo);
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
	double x,y; //son las coordenadas de la direccion de la recta a calcular.
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
	double t = (x*(p->getOrigen().y-posActual.y)+ y*(posActual.x-p->getOrigen().x))/(y*p->getDireccion().x-x*p->getDireccion().y);
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
 * @param double <b>tiempo</b>
 */
void Pelota::mover(double tiempo){
	 calcularPosicionX(tiempo); 
	 calcularPosicionY(tiempo); 
	 calcularVelocidad(tiempo);
}
	
/**
 * Calcula el ángulo de incidencia cuando la esfera choca contra una pared.
 * @param Punto p es la dirección de la pared contra la que se choca.
 * @return El angulo de incidencia del choque en grados. 
 */
int Pelota::calcularAnguloIncidencia(Punto p){
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
void Pelota::chocar(Pared* p, double t){
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
	
	setVelocidadInicial(getVelocidad());
}
	
/**
 * Calcula la velocidad máxima para que la esfera no avance mas de su
 * diametro en 0,1 segundos.
 * @return double - La velocidad maxima calculada
 */
double Pelota::calcularVelocidadMaxima(){
	return((this->getDiametro()-0.005*this->getAceleracion())/0.1);
}
	
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
 * @return double que es el módulo de la velocidad de reflexión de la esfera.
 */
double Pelota::calcularVelocidadReflexion(int angIncidencia,Punto dirPared){
	int angReflexion = calcularAnguloReflexion(angIncidencia);
	anguloReflexionASistFijo(dirPared,angReflexion);
	return(getVelocidad()*(sin((Velocidad::toRadians(angIncidencia))/(sin(Velocidad::toRadians(angReflexion))))));
}

/**
 * Este metodo resuelve el choque entre esferas.
 * @param Esfera e: Esfera contra la que choca
 * @param double tiempo: Tiempo en el que se produce la colision
 */
void Pelota::chocar(Solido* solido, double tiempo) {
//	EstrategiaChoque estrategia= new EstrategiaChoqueEstandar(this,pelota,tiempo);
//	estrategia.chocar();	
	
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

void Pelota::buscarChoques(double tiempo){
	//Choques con solidos
	std::list<Solido*>::iterator itSolidos;
	for (itSolidos=listaSolidos.begin(); itSolidos!=listaSolidos.end(); itSolidos++)
		if (this->seChoca(*itSolidos)) chocar(*itSolidos,tiempo);

	//Choques con paredes
	std::list<Pared*>::iterator itParedes;
	for (itParedes=listaParedes.begin(); itParedes!=listaParedes.end(); itParedes++)
		if (this->seChoca(*itParedes)) chocar(*itParedes,tiempo);

}