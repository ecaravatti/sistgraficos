// Pelota.cpp: implementation of the Pelota class.
//
//////////////////////////////////////////////////////////////////////

#include "Pelota.h"


Pelota* Pelota::instance=NULL;

/*****************************************************************************************/
Pelota::Pelota()
{
	posInicial.x = 3.75;
	posInicial.y = 1.0;
	posInicial.z = 0.0;
	posActual.x = 3.75;
	posActual.y = 1.0;
	posActual.z = 0.0;
	aceleracion = 0.3;
	diametro = 1.25*1/4;
	velocidadInicial = Velocidad(2.0f,2.0f);
	velocidad = Velocidad(2.0f,2.0f);
	tiempo=0;
}
/*****************************************************************************************/
Pelota::~Pelota()
{}
/*****************************************************************************************/
float Pelota::getPosX(){
	return posActual.x;
}
/*****************************************************************************************/
float Pelota::getPosY(){
	return posActual.y;
}
/*****************************************************************************************/
float Pelota::getVelocidad() {
	return velocidad.getModulo();
}
/*****************************************************************************************/
void Pelota::setPosInicial(Punto posInicial) {
	this->posInicial = posInicial;
}
/*****************************************************************************************/
void Pelota::setAngulo(int angulo) {
	velocidad.setVelocidad(getVelocidad(),angulo);
}
/*****************************************************************************************/
void Pelota::setVelocidadInicial(Velocidad v){
	float nvel=v.getModulo();
	this->velocidadInicial.setVelocidad(nvel,v.getAngulo());
	this->setAngulo(v.getAngulo());
	this->velocidad.setVelocidad(nvel,v.getAngulo());
	this->posInicial=posActual;
	tiempo=0;
	tiempoAnt=0;
}
/*****************************************************************************************/
void Pelota::calcularPosicionX(float t){
	posActual.x = (posInicial.x + velocidadInicial.getVelX()*(t) -0.5*aceleracion*cos(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t,2));
}
/*****************************************************************************************/
void Pelota::calcularPosicionY(float t){
	posActual.y = (posInicial.y + velocidadInicial.getVelY()*(t) -0.5*aceleracion*sin(Velocidad::toRadians(velocidadInicial.getAngulo()))*pow(t,2));
}
/*****************************************************************************************/
void Pelota::calcularVelocidad(float t){
	velocidad.setVelocidad(velocidadInicial.getModulo()-aceleracion*(t),velocidadInicial.getAngulo());
}
/*****************************************************************************************/
bool Pelota::seChoca(Solido* solido){
	if (posActual.distancia(solido->getPosicion()) <= (diametro/2 + solido->getDiametro()/2)) 
		return true;
	return false;
}
/*****************************************************************************************/
void Pelota::mover(){
	tiempoAnt=tiempo;
	tiempo+=0.05;
	if (getVelocidad()>0){ 
				calcularPosicionX(tiempo); 
				calcularPosicionY(tiempo); 
				calcularVelocidad(tiempo);
	}
	buscarChoquesSolidos();
	buscarChoquesPared();
}
/*****************************************************************************************/
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
/*****************************************************************************************/
void Pelota::cargarSolido(Solido* solido){
	listaSolidos.push_back(solido);
}
/*****************************************************************************************/
void Pelota::buscarChoquesSolidos(){
	//Choques con solidos
	std::list<Solido*>::iterator itSolidos;
	for (itSolidos=listaSolidos.begin(); itSolidos!=listaSolidos.end(); itSolidos++)
		if (this->seChoca(*itSolidos))
			chocar(*itSolidos);
}
/*****************************************************************************************/
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
/*****************************************************************************************/
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
/*****************************************************************************************/

