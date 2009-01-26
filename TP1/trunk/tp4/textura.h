
#include "gl/glaux.h"
#pragma comment (lib, "glaux.lib") 

//extern GLuint	texture[];
//extern GLuint	g_Texture[];

//int CreateTexture2(UINT texture[], LPSTR strFileName, int i);
//int LoadTexture(int i);
//void LoadTextures();


// especificar los nombres de las imágenes
// Formato de las imágenes
// BMP de 24 bits
// Dimensiones que sean múltiplos de potencias de 2
// Ej: 8, 16, 32, 64, 128, 256, 512, etc

/*char * texturefiles[] = {
	"paredes2.bmp",
	"dibujo.bmp",
	"Envroll.bmp",
	"logo.bmp",
	"Ball.bmp"
};

#define NTextures sizeof(texturefiles)/sizeof(char*)
*/
#ifndef __TEXTURA_H__
#define __TEXTURA_H__

class Textura{
private:
		GLuint g_Texture[200];
		GLuint* texture;
		int nroTextura;
		static Textura* instance;
		bool carga;
public: 
		~Textura();
		static Textura* getInstance(){
			if (instance==NULL) instance=new Textura();
			return instance;
		}
		void cargarTexturas();
		void activar();
		void desactivar();
		//void sigTextura();
		void setTex(int nroTex);
		int	 getSigTex();
private:
		Textura();
		int cargarTextura(int i);
		int crearTextura(UINT texture[], LPSTR strFileName, int i);
		bool texturasCargadas();
};

#endif