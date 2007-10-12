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

/**************************************************************/
/* Inicializo el pipeline2D									  */
/**************************************************************/
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
}



void display()
{
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	///

	CPipeline2D* pipeline = CPipeline2D::getInstancia();
	pipeline->CargarIdentidad();
	pipeline->ColorLinea(100,200,40);
	pipeline->ColorPunto(255,0,0);
	pipeline->ColorRelleno(130,0,160);

/**************************************************************/
/* Dibuja unas lineas punteadas.							  */
/**************************************************************/
	//Linea punteada superior (10 puntos)
	Vertice* lineaPunteada1 = new Vertice[11];
	lineaPunteada1[0].set(175,190);
	lineaPunteada1[1].set(180,190);
	lineaPunteada1[2].set(185,190);
	lineaPunteada1[3].set(190,190);
	lineaPunteada1[4].set(195,190);
	lineaPunteada1[5].set(200,190);
	lineaPunteada1[6].set(205,190);
	lineaPunteada1[7].set(210,190);
	lineaPunteada1[8].set(215,190);
	lineaPunteada1[9].set(220,190);
	lineaPunteada1[10].set(225,190);

	// Linea puenteada inferior (11 puntos)
	Vertice* lineaPunteada2 = new Vertice[11];
	lineaPunteada2[0].set(0,50);
	lineaPunteada2[1].set(5,50);
	lineaPunteada2[2].set(10,50);
	lineaPunteada2[3].set(15,50);
	lineaPunteada2[4].set(20,50);
	lineaPunteada2[5].set(25,50);
	lineaPunteada2[6].set(30,50);
	lineaPunteada2[7].set(35,50);
	lineaPunteada2[8].set(40,50);
	lineaPunteada2[9].set(45,50);
	lineaPunteada2[10].set(50,50);

	pipeline->Primitiva2D(PRIM2D_PUNTO);
	pipeline->Dibujar(lineaPunteada2, 10);
	pipeline->Dibujar(lineaPunteada1, 10);

/**************************************************************/
/* Dibuja poligono de 16 vértices (en color verde).			  */
/**************************************************************/
	Vertice* poligono16V = new Vertice[16];
	poligono16V[0].set(75,25);
	poligono16V[1].set(125,25);
	poligono16V[2].set(150,50);
	poligono16V[3].set(125,75);
	poligono16V[4].set(175,100);
	poligono16V[5].set(125,125);
	poligono16V[6].set(150,175);
	poligono16V[7].set(125,200);
	poligono16V[8].set(175,225);
	poligono16V[9].set(25,225);
	poligono16V[10].set(75,200);
	poligono16V[11].set(50,175);
	poligono16V[12].set(75,125);
	poligono16V[13].set(25,100);
	poligono16V[14].set(75,75);
	poligono16V[15].set(50,50);

	pipeline->Primitiva2D(PRIM2D_POLIGONO);
	pipeline->Dibujar(poligono16V, 16);
	pipeline->Rotacion(100,225.0,90);
	pipeline->Dibujar(poligono16V, 16);
	pipeline->CargarIdentidad();
	pipeline->Rotacion(100,225.0,180);
	pipeline->Dibujar(poligono16V, 16);
	pipeline->CargarIdentidad();
	pipeline->Rotacion(100,225.0,270);
	pipeline->Dibujar(poligono16V, 16);

/**************************************************************/
/* Dibuja círculos azules.									  */
/**************************************************************/
	Vertice* circulos = new Vertice[2];
	circulos[0].set(100,150);
	circulos[1].set(150,150);

	pipeline->CargarIdentidad();
	pipeline->Traslacion(430,350);
	pipeline->Primitiva2D(PRIM2D_CIRCULO);
	for (int i = 0;i<120;i+=10)
	{
		pipeline->ColorLinea(0,0,5*i);
		pipeline->Rotacion(150,150,i);
		pipeline->Dibujar(circulos,2);
	}

/**************************************************************/
/* Dibuja el Sol.											  */
/**************************************************************/
	pipeline->Primitiva2D(PRIM2D_CIRCULO_RELLENO);
	pipeline->CargarIdentidad();
	pipeline->Traslacion(150,250);
	pipeline->Escalado(1.5,1);
	pipeline->ColorLinea(200,200,000);
	pipeline->Dibujar(circulos,2);

/**************************************************************/
/* Dibuja unas estrellas de 24 vértices (en color amarillo).  */
/**************************************************************/
	Vertice* estrella = new Vertice[24];
	estrella[0].set(250,100);
	estrella[1].set(150,50);
	estrella[2].set(150,150);
	estrella[3].set(50,150);
	estrella[4].set(100,250);
	estrella[5].set(0,300);
	estrella[6].set(100,350);
	estrella[7].set(50,450);
	estrella[8].set(150,450);
	estrella[9].set(150,550);
	estrella[10].set(250,500);
	estrella[11].set(300,600);
	estrella[12].set(350,500);
	estrella[13].set(450,550);
	estrella[14].set(450,450);
	estrella[15].set(550,450);
	estrella[16].set(500,350);
	estrella[17].set(600,300);
	estrella[18].set(500,250);
	estrella[19].set(550,150);
	estrella[20].set(450,150);
	estrella[21].set(450,50);
	estrella[22].set(350,100);
	estrella[23].set(300,0);

	pipeline->Primitiva2D(PRIM2D_POLIGONO);
	pipeline->CargarIdentidad();
	pipeline->Escalado(0.5,0.5);
	pipeline->Traslacion(550,0);
	pipeline->ColorLinea(160,160,60);

	for(int n =0; n<=400; n+=110)
	{
		pipeline->Dibujar(estrella,24);
		pipeline->Traslacion(n*2,n);
		pipeline->ColorLinea(160+n*0.2,170+n*0.2,60);
	}

/**************************************************************/	
/* Dibuja unos pinos.										  */
/**************************************************************/
	Vertice* pino = new Vertice[4];
  
	for(int x = -100; x<300;x+=75)
	{
		for(int y=500; y<700;y+=225)
		{
			//Cada iteración dibuja un pino
			pipeline->CargarIdentidad();
			pipeline->Traslacion(x,y);
	
			// coordenadas del tronco
			pino[0].set(90,300-50);
			pino[1].set(110,300-50);
			pino[2].set(110,400-50);
			pino[3].set(90,400-50);
	
			pipeline->Primitiva2D(PRIM2D_POLIGONO_RELLENO);
	
			pipeline->ColorRelleno(100,100,0);
			pipeline->ColorLinea(200,200,0);
			
			//Dibuja el tronco
			pipeline->Dibujar(pino,4);
		
			// coordenadas de los triangulos
			pino[0].set(100,100-50);
			pino[1].set(150,200-50);
			pino[2].set(50,200-50);

			//Dibuja los 3 triangulos del pino
			pipeline->ColorLinea(10,255,10);
			pipeline->ColorRelleno(0,255,0);
			pipeline->Dibujar(pino,3);
	
			pipeline->ColorRelleno(0,230,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(pino,3);
	
			pipeline->ColorRelleno(0,200,0);
			pipeline->Traslacion(0,50);
			pipeline->Dibujar(pino,3);
		}
	} 

/**************************************************************/
/* Dibuja una casa.											  */
/**************************************************************/
	pipeline->ColorLinea(60,0,0);
	Vertice* casa = new Vertice[6];
	casa[0].set(0,20);
	casa[1].set(15,30);
	casa[2].set(60,30);
	casa[3].set(60,50);
	casa[4].set(15,50);
	casa[5].set(0,40);

	pipeline->CargarIdentidad();
	pipeline->ColorRelleno(240,255,255);
	pipeline->Escalado(4,4);
	pipeline->Traslacion(120,150);
	pipeline->Dibujar(casa,6);

	//Dibuja el techo
	casa[0].set(0,20);
	casa[1].set(10,10);
	casa[2].set(55,10);
	casa[3].set(60,30);
	casa[4].set(15,30);
	
	pipeline->ColorRelleno(240,0,30);
	pipeline->Dibujar(casa,5);

	// Dibuja la chimenea.
	casa[0].set(40,0);
	casa[1].set(45,10);
	casa[2].set(50,10);
	casa[3].set(50,25);
	casa[4].set(45,25);
	casa[5].set(40,15);

	pipeline->ColorRelleno(220,0,30);
	pipeline->Dibujar(casa,6);

	casa[0].set(40,0);
	casa[1].set(45,0);
	casa[2].set(50,10);
	casa[3].set(45,10);

	pipeline->ColorRelleno(200,0,30);
	pipeline->Dibujar(casa,4);


	// Dibuja la puerta.
	casa[0].set(3,42);
	casa[1].set(3,26);
	casa[2].set(11,32);
	casa[3].set(11,48);

	pipeline->ColorRelleno(80,50,0);
	pipeline->Dibujar(casa,4);

	// Dibuja la ventana
	casa[0].set(25,42);
	casa[1].set(25,35);
	casa[2].set(50,35);
	casa[3].set(50,42);

	pipeline->ColorRelleno(0,0,20);
	pipeline->Dibujar(casa,4);


	delete[] lineaPunteada1;
	delete[] lineaPunteada2;
	delete[] poligono16V;
	delete[] circulos;
	delete[] estrella;
	delete[] pino;
	delete[] casa;

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
