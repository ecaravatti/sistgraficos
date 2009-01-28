
#include "gl/glaux.h"
#pragma comment (lib, "glaux.lib") 

#ifndef __TEXTURA_H__
#define __TEXTURA_H__

class Textura{
private:
		//GLuint g_Textura[200];
		GLuint* textura;
		int nroTextura;
		static Textura* instance;
		bool carga;
public: 
		~Textura();
		//Devuelve la unica instancia (Singleton)
		static Textura* getInstance(){
			if (instance==NULL) instance=new Textura();
			return instance;
		}

		//Carga todas las texturas para su posterior utilizacion
		void cargarTexturas();

		//Activa las texturas
		void activar();

		//Desactiva texturas
		void desactivar();

		//Setea una nueva textura
		void setTex(int nroTex);

		//Devuelve la proxima textura para creacion de solidos
		int	 getSigTex();
private:
		// Constructor
		Textura();

		//Carga una unica textura
		int cargarTextura(int i);

		//Crea la textura y la mapea a memoria
		int crearTextura(UINT texture[], LPSTR nombreStr, int i);

		bool texturasCargadas();
};

#endif