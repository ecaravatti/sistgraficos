#include "textura.h"


// especificar los nombres de las imágenes
// Formato de las imágenes
// BMP de 24 bits
// Dimensiones que sean múltiplos de potencias de 2
// Ej: 8, 16, 32, 64, 128, 256, 512, etc

#define NTexturas sizeof(archsTex)/sizeof(char*)

char * archsTex[] = {
		"tex/paredes2.bmp",
		"tex/mat01.bmp",
		"tex/mat02.bmp",
		"tex/mat03.bmp",
		"tex/mat04.bmp",
		"tex/mat05.bmp",
		"tex/mat06.bmp",
		"tex/mat07.bmp",
		"tex/mat08.bmp",
		"tex/mat09.bmp",
		"tex/dibujo.bmp",
		"tex/Envroll.bmp",
		"tex/logo.bmp",
		"tex/Ball.bmp"
};

Textura* Textura::instance=NULL;

/*****************************************************************************************/

Textura::Textura():nroTextura(0){
	textura=new GLuint[NTexturas];
	carga=false;
}

/*****************************************************************************************/

int Textura::crearTextura(UINT textura[], LPSTR nombreStr, int i)
{
  AUX_RGBImageRec *Imagen;

  Imagen=auxDIBImageLoad(nombreStr);

  if ( Imagen ){
		glGenTextures(1, &textura[i]);

		glBindTexture(GL_TEXTURE_2D, textura[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
			Imagen->sizeX, 
			Imagen->sizeY, 
			0, GL_RGB, GL_UNSIGNED_BYTE, 
			Imagen->data);
		free(Imagen->data);
		free(Imagen);
		return 1;
	}
  else
		return 0;
}

/*****************************************************************************************/

int Textura::cargarTextura(int i){
	return crearTextura( textura, archsTex[i], i );
}

/*****************************************************************************************/

void Textura::cargarTexturas(){
	for (int i=0; i<NTexturas; i++ )
		cargarTextura(i);
	carga=true;
}

/*****************************************************************************************/

void Textura::activar(){
	if (!texturasCargadas()) cargarTexturas();
	glEnable( GL_TEXTURE_2D );
}

/*****************************************************************************************/

void Textura::desactivar(){
	glDisable( GL_TEXTURE_2D );
}

/*****************************************************************************************/

bool Textura::texturasCargadas(){
	return carga;
}

/*****************************************************************************************/

void Textura::setTex(int nroTex){
	if (nroTex>NTexturas)	nroTex=0;

	if (!texturasCargadas()) cargarTexturas();

	glBindTexture( GL_TEXTURE_2D, textura[nroTex] );
}

/*****************************************************************************************/

int Textura::getSigTex(){
	if (!texturasCargadas()) cargarTexturas();
	this->nroTextura++;
	if (nroTextura>NTexturas)
		nroTextura=0;
	return nroTextura;
}

/*****************************************************************************************/
