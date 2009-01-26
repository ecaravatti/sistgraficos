
#include "gl/glaux.h"
#pragma comment (lib, "glaux.lib") 

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
		void setTex(int nroTex);
		int	 getSigTex();
private:
		Textura();
		int cargarTextura(int i);
		int crearTextura(UINT texture[], LPSTR strFileName, int i);
		bool texturasCargadas();
};

#endif