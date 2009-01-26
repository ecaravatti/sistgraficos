#include "textura.h"


// especificar los nombres de las imágenes
// Formato de las imágenes
// BMP de 24 bits
// Dimensiones que sean múltiplos de potencias de 2
// Ej: 8, 16, 32, 64, 128, 256, 512, etc

#define NTextures sizeof(texturefiles)/sizeof(char*)

char * texturefiles[] = {
	"paredes2.bmp",
	"dibujo.bmp",
	"Envroll.bmp",
	"logo.bmp",
	"Ball.bmp"
};

Textura* Textura::instance=NULL;

Textura::Textura():nroTextura(0){
	texture=new GLuint[NTextures];
	carga=false;
}

int Textura::crearTextura(UINT texture[], LPSTR strFileName, int i)
{
  AUX_RGBImageRec *TextureImage;

  TextureImage=auxDIBImageLoad(strFileName);

  if ( TextureImage )
	{

		glGenTextures(1, &texture[i]);

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
			TextureImage->sizeX, 
			TextureImage->sizeY, 
			0, GL_RGB, GL_UNSIGNED_BYTE, 
			TextureImage->data);
		free(TextureImage->data);
		free(TextureImage);
		return 1;
	}
  else
		return 0;
}

int Textura::cargarTextura(int i)	
{
	return crearTextura( texture, texturefiles[i], i );
}

void Textura::cargarTexturas()
{
	for (int i=0; i<NTextures; i++ )
		cargarTextura(i);
	carga=true;
}
void Textura::activar(){
	if (!texturasCargadas()) cargarTexturas();
	//nroTextura=0;
	glEnable( GL_TEXTURE_2D );
	//glBindTexture( GL_TEXTURE_2D, texture[0] );
	//sigTextura();
}
void Textura::desactivar(){
	glDisable( GL_TEXTURE_2D );
}
bool Textura::texturasCargadas(){
	return carga;
}
void Textura::setTex(int nroTex){
	if (nroTex>NTextures)	nroTex=0;

	if (!texturasCargadas()) cargarTexturas();

	glBindTexture( GL_TEXTURE_2D, texture[nroTex] );
}
/*
void Textura::sigTextura(){
	if (!texturasCargadas()) cargarTexturas();
	this->nroTextura++;
	if (nroTextura>NTextures)
		nroTextura=0;
	glBindTexture( GL_TEXTURE_2D, texture[nroTextura] );
}*/
int Textura::getSigTex(){
	if (!texturasCargadas()) cargarTexturas();
	this->nroTextura++;
	if (nroTextura>NTextures)
		nroTextura=0;
	return nroTextura;
}