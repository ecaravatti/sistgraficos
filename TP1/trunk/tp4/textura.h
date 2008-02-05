
#include "gl/glaux.h"
#pragma comment (lib, "glaux.lib") 

extern GLuint	texture[];
extern GLuint	g_Texture[];

int CreateTexture2(UINT texture[], LPSTR strFileName, int i);
int LoadTexture(int i);
void LoadTextures();

