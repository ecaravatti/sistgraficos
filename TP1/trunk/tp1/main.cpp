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
	Segmento seg1(new Vertice(200,0), new Vertice(200, 400));
	//Horizontal
	Segmento seg2(new Vertice(0,250), new Vertice(400,250));
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
	//Poligono p(pVertice, 3);
	
	//Poligono 2 5 vertices
	Vertice* pVertice2 = new Vertice[5];
	pVertice2[0].set(200,100);
	pVertice2[1].set(250,100);
	pVertice2[2].set(300,175);
	pVertice2[3].set(225,225);
	pVertice2[4].set(150,175);
	//Poligono p2(pVertice2, 5);

	//Poligono 3 16 vertices relleno
	

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
	//Poligono p4(pVertice4, 16);

	//Linea punteada superior(10 puntos)
	Vertice* pVertice9 = new Vertice[11];
	pVertice9[0].set(175,190);
	pVertice9[1].set(180,190);
	pVertice9[2].set(185,190);
	pVertice9[3].set(190,190);
	pVertice9[4].set(195,190);
	pVertice9[5].set(200,190);
	pVertice9[6].set(205,190);
	pVertice9[7].set(210,190);
	pVertice9[8].set(215,190);
	pVertice9[9].set(220,190);
	pVertice9[10].set(225,190);

	Vertice* pVertice10 = new Vertice[8];
	pVertice10[0].set(25,25);
	pVertice10[1].set(125,25);
	pVertice10[2].set(62,75);
	pVertice10[3].set(62,100);
	pVertice10[4].set(125,150);
	pVertice10[5].set(25,150);
	pVertice10[6].set(62,100);
	pVertice10[7].set(62,75);
	//Poligono p10(pVertice10, 8);

	Vertice* pVertice11 = new Vertice[4];
	pVertice11[0].set(200,200);
	pVertice11[1].set(150,250);
	pVertice11[2].set(200,300);
	pVertice11[3].set(250,275);
	//Poligono p11(pVertice11, 4);

	Vertice* pVertice12 = new Vertice[12];
	pVertice12[0].set(70,40);
	pVertice12[1].set(100,100);
	pVertice12[2].set(150,70);
	pVertice12[3].set(170,140);
	pVertice12[4].set(190,110);
	pVertice12[5].set(210,150);
	pVertice12[6].set(180,240);
	pVertice12[7].set(170,180);
	pVertice12[8].set(160,200);
	pVertice12[9].set(90,200);
	pVertice12[10].set(80,250);
	pVertice12[11].set(50,120);
	//Poligono p12(pVertice12, 12);

	Vertice* pVertice20=new Vertice[4];
	pVertice20[0].set(100,100);
	pVertice20[1].set(300,100);
	pVertice20[2].set(300,300);
	pVertice20[3].set(100,300);
	//Poligono p20(pVertice20, 4);


	Segmento s1(new Vertice(0,100), new Vertice(400,100));
	Segmento s2(new Vertice(0,300), new Vertice(400,300));
//----------------------------------------------------------------------
//glBegin(GL_POINTS);
	//-------------------Para dibujar segmentos 
	
	//	seg1.clipping(150, 250, 100, 300);
		//seg1.dibujarBresenham();
		//s1.dibujarBresenham();
		//s2.dibujarBresenham();
		

	
	//	seg2.clipping(50,150,100,400);
		//seg2.dibujarBresenham();
	
	/*	
		seg3.clipping(250,350,200,300);
		seg3.dibujarBresenham();
	*/
		//seg4.dibujarBresenham();
		//seg5.dibujarBresenham();
		
		//seg6.dibujarBresenham();
		//seg7.dibujarBresenham();
		//seg8.dibujarBresenham();
		//seg9.dibujarBresenham();
		//seg10.dibujarBresenham();
	
	
	//--------------------Para dibujar poligono relleno
		
	/*
		p.dibujarScanLine();
		p.dibujarContorno();
		

		p2.dibujarScanLine();
	
	*/	
	//---------------------Para dibujar poligono relleno 16 vertices
	
	
		//p3.dibujarScanLine();	
		//p4.dibujarContorno();

		//p10.dibujarContorno();
		//p10.dibujarScanLine();
		
		//p11.dibujarScanLine();
		//p11.dibujarContorno();
		//p11.dibujarScanLine();

		//p12.dibujarContorno();
		//p12.dibujarScanLine();
		
	

	//---------------------Para dibujar circulos
	/*
		cir1.dibujarContorno();
		cir2.dibujarContorno();
		cir1.dibujarRelleno();
	*/

	/*
	p.clipping(new Vertice(100,100), new Vertice(150,150));
	p.dibujarScanLine();
	p.dibujarContorno();
	p.dibujarScanLine();
	*/
	
	/*
	p.dibujarContorno();
	p.clipping(new Vertice(150,100), new Vertice(200,150));
	p.dibujarContorno();
	p.dibujarScanLine();
	*/
	
	
	//p12.dibujarContorno();
	/*p12.clipping(new Vertice(0, 0), new Vertice(80,100));
	p12.dibujarScanLine();
	*/
	
	/*
	p11.dibujarContorno();
	p11.clipping(new Vertice(200,200), new Vertice(225,250));
	p11.dibujarScanLine();
	p11.dibujarContorno();
	*/
	
	//p20.dibujarContorno();
	//p20.clipping(new Vertice(100,200), new Vertice(300,530));	
	//p20.dibujarContorno();

	//pipeline.Viewport(100,300,200,230);
	

//glEnd();

//Linea punteada inferior (10 puntos)
	Vertice* pVertice8 = new Vertice[11];
	pVertice8[0].set(0,50);
	pVertice8[1].set(5,50);
	pVertice8[2].set(10,50);
	pVertice8[3].set(15,50);
	pVertice8[4].set(20,50);
	pVertice8[5].set(25,50);
	pVertice8[6].set(30,50);
	pVertice8[7].set(35,50);
	pVertice8[8].set(40,50);
	pVertice8[9].set(45,50);
	pVertice8[10].set(50,50);
	
	
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

/*
	CPipeline2D pipeline;
	pipeline.VentanaMundo(0,0,200,200);
	pipeline.Viewport(100,200,200,200);

	pipeline.Viewport(100,100,200,230);

	pipeline.ColorLinea(100,200,40);
	pipeline.ColorPunto(255,0,0);
	pipeline.ColorRelleno(130,0,160);

	pipeline.Primitiva2D(PRIM2D_PUNTO);
	pipeline.Dibujar(pVertice8, 11);
	pipeline.Dibujar(pVertice9, 10);
	
	pipeline.Primitiva2D(PRIM2D_POLIGONO);
	pipeline.Dibujar(pVertice20,4);

*/

	//pipeline.Primitiva2D(PRIM2D_PUNTO);
	//pipeline.Dibujar(new Vertice(200,250),1);

	//pipeline.Dibujar(pVertice20,4);
	//pipeline.Dibujar(pVertice3, 16);


	//pipeline.Rotacion(100,225.0,90);
	
	//pipeline.Dibujar(pVertice3, 16);
	/*pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,180);
	
	
	pipeline.Dibujar(pVertice3, 16);
	pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,270);
	
	
	pipeline.Dibujar(pVertice3, 16);
*/
	// Para dibujar circulos
/*	pipeline.ColorLinea(30,70,190);
	pipeline.Traslacion(-100,300);
	pipeline.Primitiva2D(PRIM2D_CIRCULO);
	pipeline.Dibujar(pVertice,3);
	pipeline.Escalado(2,1);
	pipeline.ColorLinea(100,0,100);
	pipeline.Dibujar(pVertice,3);
	*/
/*
	delete[] pVertice8;
	delete[] pVertice9;
	delete[] pVertice;
	delete[] pVertice2;
	delete[] pVertice3;
	delete[] pVertice4;
*/	

	CPipeline2D pipeline;
	pipeline.VentanaMundo(0,0,800,800);
	pipeline.Viewport(100,100,500,500);
	pipeline.CargarIdentidad();
	pipeline.ColorLinea(100,200,40);
	pipeline.ColorPunto(255,0,0);
	pipeline.ColorRelleno(130,0,160);

	pipeline.Primitiva2D(PRIM2D_PUNTO);
	pipeline.Dibujar(pVertice8, 10);
	pipeline.Dibujar(pVertice9, 10);
	pipeline.Primitiva2D(PRIM2D_POLIGONO);

	//pipeline.Dibujar(pVertice20,4);
	pipeline.Dibujar(pVertice3, 16);

	pipeline.Rotacion(100,225.0,90);
	
	pipeline.Dibujar(pVertice3, 16);
	pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,180);
	
	
	pipeline.Dibujar(pVertice3, 16);
	pipeline.CargarIdentidad();
	pipeline.Rotacion(100,225.0,270);
	
	
	pipeline.Dibujar(pVertice3, 16);

	// Para dibujar circulos
	pipeline.ColorLinea(30,70,190);
	pipeline.Traslacion(-100,300);
	pipeline.Primitiva2D(PRIM2D_CIRCULO);
	pipeline.Dibujar(pVertice,3);
	pipeline.Escalado(2,1);
	pipeline.ColorLinea(100,0,100);
	pipeline.Dibujar(pVertice,3);

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
   glutInitWindowSize (800,600); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (caption);
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
