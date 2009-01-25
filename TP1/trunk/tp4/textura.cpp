#include "textura.h"


// especificar los nombres de las imágenes
// Formato de las imágenes
// BMP de 24 bits
// Dimensiones que sean múltiplos de potencias de 2
// Ej: 8, 16, 32, 64, 128, 256, 512, etc

char * texturefiles[] = {
	/*"Envroll.bmp",*//*"paredes.bmp",*/"logo.bmp",
	"dibujo.bmp",
};



// El siguiente código no cambia

#define NTextures sizeof(texturefiles)/sizeof(char*)

UINT g_Texture[200];
GLuint	texture[NTextures];

int CreateTexture2(UINT texture[], LPSTR strFileName, int i)
{
  AUX_RGBImageRec *TextureImage;

  TextureImage=auxDIBImageLoad(strFileName);

  if ( TextureImage )
	{

		glGenTextures(1, &texture[i]);

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
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

int CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
  return CreateTexture2(textureArray,strFileName,textureID);
}

int LoadTexture(int i)	
{
	return CreateTexture2( texture, texturefiles[i], i );
}

void LoadTextures()
{
	for (int i=0; i<NTextures; i++ )
		LoadTexture(i);
}

// FINALIZA TEXTURAS

