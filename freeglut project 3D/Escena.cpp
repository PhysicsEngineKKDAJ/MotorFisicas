#include "Escena.h"
#include <time.h>       /* time */
#include "ArbolEsfera1.h"
#include "ArbolEsfera2.h"
#include "ArbolCono1.h"
#include "ArbolCono2.h"
#include "Coche.h"
#include "Cubo.h"



Escena::Escena(int n) : numArboles (n),ObjetoCompuesto(n), angX(0.0f), angY(0.0f), angZ(0.0f)
{
	//------------Cámara--------------
	camera = new Camara(WIDTH, HEIGHT);

	camera->setPos();

	// Scene visible area and projection  
	camera->setVV();

	// Viewport set up
	glViewport(0, 0, WIDTH, HEIGHT);
	//------------Cámara--------------

	isCulled = true;

	srand(time(NULL));

	//Construcciones de todos los objetos (arbolitos)
	this->introduceObjeto(new Coche());
	PuntoVector3D * aux;

	int indice = sqrt(numArboles) / 2;
	//Construcción del bosque de árboles
	for (int i = -indice; i <= indice; i++)
	{
		for (int j = -indice; j <= indice; j++)
		{
			//Creo arbol
			if (rand() % 4 == 0)
			{
				int tipo = rand() % 4;//Tipo
				GLfloat h = rand() % 11;//Altura
				GLfloat c = rand() % 11;//Copa

				aux = new PuntoVector3D(i * 3.0f, 0.0f, j * 3.0f, 1);
				switch (tipo)
				{
					//Arbol Esfera 1
				case 0:
					this->introduceObjeto(new ArbolEsfera1(h*0.1f + 0.5f,c*0.1f + 0.5f));
					hijos[numHijos-1]->traslada(aux);
					break;

				case 1:
					this->introduceObjeto(new ArbolEsfera2(h*0.1f + 0.5f, c*0.1f + 0.5f));
					hijos[numHijos-1]->traslada(aux);
					break;

				case 2:
					this->introduceObjeto(new ArbolCono1(h*0.1f + 0.5f, c*0.1f + 0.5f));
					hijos[numHijos-1]->traslada(aux);
					break;

				case 3:
					this->introduceObjeto(new ArbolCono2(h*0.1f + 0.5f, c*0.1f + 0.5f));
					hijos[numHijos-1]->traslada(aux);
					break;

				}
				delete aux;

			}

		}
	}
	nArbolesTalados = 0;

	treeQuadtree = new QuadTree(); 
	treeQuadtree->initialize(-(indice*3),-(indice*3),indice*3*2,hijos, numHijos);
}


Escena::~Escena()
{
	delete camera;
}

bool Escena::colisionCocheArbol(Objeto3D* arbol)
{
	GLfloat* mCochecito = hijos[0]->getmT()->getM();
	GLfloat* mArbol = arbol->getmT()->getM();

	return ((sqrt(pow((mCochecito[12] - mArbol[12]), 2) + pow((mCochecito[14] - mArbol[14]), 2))) < 1); //HAY COLISION
}

void Escena::dibuja(){
	// Rotating the scene
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	rotaEscena();

	dibujaEjes();

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	glMultMatrixf(this->mT->getM());

	hijos[0]->dibuja();

	if (!isCulled){
		for (int i = 1; i < numHijos; i++)
		{
			if (hijos[i]->esVisible())
				hijos[i]->dibuja();
		}

	}
	else{
		int x1, z1, x3, z3;
		//AbajoIzquierda
		x1 = camera->eye->getX() + camera->xLeft;
		z1 = camera->eye->getZ() + camera->yBot;

		//ArribaDerecha
		x3 = camera->eye->getX() + camera->xRight;
		z3 = camera->eye->getZ() + camera->yTop;

		treeQuadtree->drawTrees(x1, z1, x3, z3);
	}
	glDisable(GL_CULL_FACE);

	glPopMatrix();

}

void Escena::dibujaEjes(){

	glLineWidth(1.5f);
	// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();


}

void Escena::rotaEscena(){
	// Rotating the scene
	glRotatef(angX, 1.0f, 0.0f, 0.0f);
	glRotatef(angY, 0.0f, 1.0f, 0.0f);
	glRotatef(angZ, 0.0f, 0.0f, 1.0f);

}

void Escena::moverCoche(movCoche avanza)
{
	if (nArbolesTalados != (numHijos - 1))
	{
		PuntoVector3D* curva;
		GLfloat ang = 0.0f;

		switch (avanza)
		{
		case ArribaDe:
			curva = new PuntoVector3D(1.0f, 0.0f, 0.0f, 1);
			ang = -angGiro;
			break;

		case AbajoDe:
			curva = new PuntoVector3D(-1.0f, 0.0f, 0.0f, 1);
			ang = angGiro;
			break;


		case ArribaIz:
			curva = new PuntoVector3D(1.0f, 0.0f, 0.0f, 1);
			ang = angGiro;
			break;

		case AbajoIz:
			curva = new PuntoVector3D(-1.0f, 0.0f, 0.0f, 1);
			ang = -angGiro;
			break;
		}
		hijos[0]->rota(ang, 0.0f, 1.0f, 0.0f);
		hijos[0]->traslada(curva);

		GLfloat* mCochecito = hijos[0]->getmT()->getM();
		camera->setEye(hijos[0]->getmT()->getM()[12], hijos[0]->getmT()->getM()[14]);

		delete curva;

		for (int i = 1; i < numHijos; i++)
		{
			if (hijos[i]->esVisible() && colisionCocheArbol(hijos[i]))
			{
				hijos[i]->setInvisible();
				nArbolesTalados++;
			}
		}

	}
}

void Escena::resize(int newWidth, int newHeight) {
	WIDTH = newWidth;
	HEIGHT = newHeight;
	glViewport(0, 0, WIDTH, HEIGHT);

	camera->setVV(WIDTH, HEIGHT);
}