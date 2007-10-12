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
#include <windows.h>

#include <iostream>

char caption[]="Sistema Gráficos - 66.71 - 2007c1";

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}


void init(int argc, char** argv) 
{
	CPipeline2D* pipeline = CPipeline2D::getInstancia();

	if (argc != 9)
	{
		printf("%s\n","La cantidad de parametros de entrada es incorrecta. Se tomarán los tamaños de viewport y ventana de mundo por defecto.");
		pipeline->Viewport(50, 50, 700, 500);
		pipeline->VentanaMundo(0, 0, 800, 800);
	}
	else
	{
		pipeline->Viewport(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
		pipeline->VentanaMundo(atof(argv[5]),atof(argv[6]),atof(argv[7]),atof(argv[8]));
	}
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


	


	
	//Poligono 1 3 vertices
	Vertice* pVertice = new Vertice[3];
	pVertice[0].set(100,150);
	pVertice[1].set(150,150);
	pVertice[2].set(170,100);
	//Poligono p(pVertice, 3);
	
	
	// Estrella de 24 vertices
	Vertice* pVertice2 = new Vertice[24];
	pVertice2[0].set(250,100);
	pVertice2[1].set(150,50);
	pVertice2[2].set(150,150);
	pVertice2[3].set(50,150);
	pVertice2[4].set(100,250);
	pVertice2[5].set(0,300);
	pVertice2[6].set(100,350);
	pVertice2[7].set(50,450);
	pVertice2[8].set(150,450);
	pVertice2[9].set(150,550);
	pVertice2[10].set(250,500);
	pVertice2[11].set(300,600);
	pVertice2[12].set(350,500);
	pVertice2[13].set(450,550);
	pVertice2[14].set(450,450);
	pVertice2[15].set(550,450);
	pVertice2[16].set(500,350);
	pVertice2[17].set(600,300);
	pVertice2[18].set(500,250);
	pVertice2[19].set(550,150);
	pVertice2[20].set(450,150);
	pVertice2[21].set(450,50);
	pVertice2[22].set(350,100);
	pVertice2[23].set(300,0);



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

	

	Vertice* pVertice11 = new Vertice[4];
	pVertice11[0].set(200,200);
	pVertice11[1].set(150,250);
	pVertice11[2].set(200,300);
	pVertice11[3].set(250,275);
	//Poligono p11(pVertice11, 4);

	




	

		
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





	CPipeline2D* pipeline = CPipeline2D::getInstancia();
	pipeline->CargarIdentidad();
	pipeline->ColorRelleno(100,100,0);
/*
	Vertice* v = new Vertice[4];

  // bosque!
	for(int x = -100; x<800;x+=75)
	{
		for(int y=-100; y<700;y+=225)
		{
			//Dibuja un pino
			pipeline->CargarIdentidad();
			pipeline->Traslacion(x,y);
	
			// coordenadas del tronco
			v[0].set(90,300-50);
			v[1].set(110,300-50);
			v[2].set(110,400-50);
			v[3].set(90,400-50);
	
			pipeline->Primitiva2D(PRIM2D_POLIGONO_RELLENO);
	
			pipeline->ColorRelleno(100,100,0);
			pipeline->ColorLinea(200,200,0);
			
			//Dibuja el tronco
			pipeline->Dibujar(v,4);
		
			// coordenadas de los triangulos
			v[0].set(100,100-50);
			v[1].set(150,200-50);
			v[2].set(50,200-50);

			//Dibuja los 3 triangulos del pino
			pipeline->ColorLinea(10,255,10);
			pipeline->ColorRelleno(0,255,0);
			pipeline->Dibujar(v,3);
	
			pipeline->ColorRelleno(0,230,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(v,3);
	
			pipeline->ColorRelleno(0,200,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(v,3);
		}
	} 

	delete[] v;
*/

	pipeline->CargarIdentidad();
	pipeline->ColorLinea(100,200,40);
	pipeline->ColorPunto(255,0,0);
	pipeline->ColorRelleno(130,0,160);

	//Dibuja unas lineas punteadas.
	pipeline->Primitiva2D(PRIM2D_PUNTO);
	pipeline->Dibujar(pVertice8, 10);
	pipeline->Dibujar(pVertice9, 10);


	// Dibuja poligono de 16 vértices (en color verde).
	pipeline->Primitiva2D(PRIM2D_POLIGONO);
	pipeline->Dibujar(pVertice3, 16);
	pipeline->Rotacion(100,225.0,90);
	pipeline->Dibujar(pVertice3, 16);
	pipeline->CargarIdentidad();
	pipeline->Rotacion(100,225.0,180);
	pipeline->Dibujar(pVertice3, 16);
	pipeline->CargarIdentidad();
	pipeline->Rotacion(100,225.0,270);
	pipeline->Dibujar(pVertice3, 16);

	// Dibuja círculos azules.
	pipeline->ColorLinea(30,70,190);
	pipeline->CargarIdentidad();
	pipeline->Traslacion(500,500);
	pipeline->Primitiva2D(PRIM2D_CIRCULO);
	for (int i = 0;i<120;i+=10)
	{
		pipeline->ColorLinea(0,0,5*i);
		pipeline->Rotacion(150,150,i);
		pipeline->Dibujar(pVertice,3);
	}

	// Dibuja Circulo violeta.
	pipeline->Primitiva2D(PRIM2D_CIRCULO_RELLENO);
	pipeline->CargarIdentidad();
	pipeline->Traslacion(150,250);
	pipeline->Escalado(1.5,1);
	pipeline->ColorLinea(200,200,000);
	pipeline->Dibujar(pVertice,3);

	// Dibuja polígono de 24 vértices (en color amarillo).
	pipeline->Primitiva2D(PRIM2D_POLIGONO);
	pipeline->CargarIdentidad();
	pipeline->Escalado(0.5,0.5);
	pipeline->Traslacion(550,0);
	pipeline->ColorLinea(160,160,60);

	for(int n =0; n<=400; n+=110)
	{
		pipeline->Dibujar(pVertice2,24);
		pipeline->Traslacion(n*2,n);
		pipeline->ColorLinea(160+n*0.2,170+n*0.2,60);
	}


	///////////////

	Vertice* v = new Vertice[4];

  
	for(int x = -100; x<300;x+=75)
	{
		for(int y=500; y<700;y+=225)
		{
			//Dibuja un pino
			pipeline->CargarIdentidad();
			pipeline->Traslacion(x,y);
	
			// coordenadas del tronco
			v[0].set(90,300-50);
			v[1].set(110,300-50);
			v[2].set(110,400-50);
			v[3].set(90,400-50);
	
			pipeline->Primitiva2D(PRIM2D_POLIGONO_RELLENO);
	
			pipeline->ColorRelleno(100,100,0);
			pipeline->ColorLinea(200,200,0);
			
			//Dibuja el tronco
			pipeline->Dibujar(v,4);
		
			// coordenadas de los triangulos
			v[0].set(100,100-50);
			v[1].set(150,200-50);
			v[2].set(50,200-50);

			//Dibuja los 3 triangulos del pino
			pipeline->ColorLinea(10,255,10);
			pipeline->ColorRelleno(0,255,0);
			pipeline->Dibujar(v,3);
	
			pipeline->ColorRelleno(0,230,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(v,3);
	
			pipeline->ColorRelleno(0,200,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(v,3);
		}
	} 

	delete[] v;


	/////////////7


	delete[] pVertice2;

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
   init (argc, argv);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   return 0;
}
