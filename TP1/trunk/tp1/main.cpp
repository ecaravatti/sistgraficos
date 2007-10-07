///
/// Sistemas Gráficos - 6671
/// ler cuatrimestre 2007
///
/// Esqueleto OpenGL
///
#include <GL\glut.h> 
#include <stdlib.h>
#include "Segmento.h"
#include "Circulo.h"
#include "Poligono.h"
#include "Pipeline2D.hpp"

#include <iostream>

char caption[]="Sistema Gráficos - 66.71 - 2007c1";



void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}




void init(void) 
{
	/// Incluir aquí todo lo que deba inicializare antes
	/// de entrar en el loop de OpenGL
}



void display()
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///


	/// Segmentos
	
	//Vertical
	//Segmento seg1(new Vertice(200,0), new Vertice(200, 400));
	//Horizontal
	Segmento seg2(new Vertice(0,200), new Vertice(400,200));
	//pendiente abs(m) < 1
	Segmento seg3(new Vertice(200,200), new Vertice(400,280));
	//pendiente abs(m) == 1
	Segmento seg4(new Vertice(200,200), new Vertice(400,400));
	//pendiente abs(m) > 1 (2.5)
	Segmento seg5(new Vertice(200,200), new Vertice(280,400));

	Segmento seg6(new Vertice(100,150), new Vertice(150,150));
	Segmento seg7(new Vertice(150,150), new Vertice(170,100));
	Segmento seg10(new Vertice(170,100), new Vertice(100,150));

	Segmento seg8(new Vertice(0,150), new Vertice(400,150));
	Segmento seg9(new Vertice(150,0), new Vertice(150,400));


	//Circulo
	Circulo cir1(new Vertice(200,200), 50); 
	Circulo cir2(new Vertice(250,200), 50);
	


	/// Poligonos rellenos
	//Poligono 1 3 vertices
	Vertice* pVertice = new Vertice[3];
	pVertice[0].set(100,150);
	pVertice[1].set(150,150);
	pVertice[2].set(170,100);
	Poligono p(pVertice, 3);
	
	//Poligono 2 5 vertices
	Vertice* pVertice2 = new Vertice[5];
	pVertice2[0].set(200,100);
	pVertice2[1].set(250,100);
	pVertice2[2].set(300,175);
	pVertice2[3].set(225,225);
	pVertice2[4].set(150,175);
	Poligono p2(pVertice2, 5);

	//Poligono 3 16 vertices relleno
	Vertice* pVertice3 = new Vertice[16];
	pVertice3[0].set(75,25);
	pVertice3[1].set(125,25);
	pVertice3[2].set(150,50);
	pVertice3[3].set(125,75);
	pVertice3[4].set(175,100);
	pVertice3[5].set(125,125);
	pVertice3[6].set(150,175);
	pVertice3[7].set(125,200);
	pVertice3[8].set(175,225);
	pVertice3[9].set(25,225);
	pVertice3[10].set(75,200);
	pVertice3[11].set(50,175);
	pVertice3[12].set(75,125);
	pVertice3[13].set(25,100);
	pVertice3[14].set(75,75);
	pVertice3[15].set(50,50);
	Poligono p3(pVertice3, 16);

	//Poligono 3 16 vertices contorno
	Vertice* pVertice4 = new Vertice[16];
	pVertice4[0].set(275,25);
	pVertice4[1].set(325,25);
	pVertice4[2].set(350,50);
	pVertice4[3].set(325,75);
	pVertice4[4].set(375,100);
	pVertice4[5].set(325,125);
	pVertice4[6].set(350,175);
	pVertice4[7].set(325,200);
	pVertice4[8].set(375,225);
	pVertice4[9].set(225,225);
	pVertice4[10].set(275,200);
	pVertice4[11].set(250,175);
	pVertice4[12].set(275,125);
	pVertice4[13].set(225,100);
	pVertice4[14].set(275,75);
	pVertice4[15].set(250,50);
	Poligono p4(pVertice4, 16);

	//Linea punteada inferior (10 puntos)
	Vertice* pVertice8 = new Vertice[10];
	pVertice8[0].set(175,100);
	pVertice8[1].set(180,100);
	pVertice8[2].set(185,100);
	pVertice8[3].set(190,100);
	pVertice8[4].set(195,100);
	pVertice8[5].set(200,100);
	pVertice8[6].set(205,100);
	pVertice8[7].set(210,100);
	pVertice8[8].set(215,100);
	pVertice8[9].set(220,100);
	pVertice8[10].set(225,100);

	//Linea punteada superior(10 puntos)
	Vertice* pVertice9 = new Vertice[10];
	pVertice9[0].set(175,225);
	pVertice9[1].set(180,225);
	pVertice9[2].set(185,225);
	pVertice9[3].set(190,225);
	pVertice9[4].set(195,225);
	pVertice9[5].set(200,225);
	pVertice9[6].set(205,225);
	pVertice9[7].set(210,225);
	pVertice9[8].set(215,225);
	pVertice9[9].set(220,225);
	pVertice9[10].set(225,225);

//----------------------------------------------------------------------
	//glBegin(GL_POINTS);
	//-------------------Para dibujar segmentos 
	/*
		seg1.dibujarBresenham();
		seg2.dibujarBresenham();
		seg3.dibujarBresenham();
		seg4.dibujarBresenham();
		seg5.dibujarBresenham();
		
		seg6.dibujarBresenham();
		seg7.dibujarBresenham();
		seg8.dibujarBresenham();
		seg9.dibujarBresenham();
		seg10.dibujarBresenham();
	*/
	
	//--------------------Para dibujar poligono relleno
	/*
		p.dibujarScanLine();
		p2.dibujarScanLine();
	*/

	//---------------------Para dibujar poligono relleno 16 vertices
	
		//p3.dibujarScanLine();
		//p4.dibujarContorno();
	
	//---------------------Para dibujar circulos
	/*
		cir1.dibujarContorno();
		cir2.dibujarContorno();
		cir1.dibujarRelleno();
	*/

	CPipeline2D pipeline;
	pipeline.ColorLinea(100,200,40);
	pipeline.ColorPunto(255,0,0);
	pipeline.ColorRelleno(130,0,160);

	pipeline.Primitiva2D(PRIM2D_PUNTO);
	pipeline.Dibujar(pVertice8, 10);
	pipeline.Dibujar(pVertice9, 10);
	
	pipeline.Primitiva2D(PRIM2D_POLIGONO);
	pipeline.Dibujar(pVertice3, 16);
	pipeline.Rotacion(100,225.0,90);
	pipeline.Dibujar(pVertice3, 16);
	pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,180);
	pipeline.Dibujar(pVertice3, 16);
	pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,270);
	pipeline.Dibujar(pVertice3, 16);

	pipeline.ColorLinea(30,70,190);
	pipeline.Traslacion(-100,300);
	pipeline.Primitiva2D(PRIM2D_CIRCULO);
	pipeline.Dibujar(pVertice,3);

	delete[] pVertice8;
	delete[] pVertice9;
	delete[] pVertice;
	delete[] pVertice2;
	delete[] pVertice3;
	delete[] pVertice4;

	//glEnd();
	
	///
  	glutSwapBuffers();
	///

}





void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
		exit (1);
		break;
	}
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
