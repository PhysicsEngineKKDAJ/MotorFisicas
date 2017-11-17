#include "Coche.h"
//#include <gl/GL.h>

#include <GL/freeglut.h>
#include <gl/GLU.h>
#include"Cubo.h"
#include "Rueda.h"
#include "Cilindro.h"

Coche::Coche() : ObjetoCompuesto(7)
{
	//CUBO
	this->introduceObjeto(new Cubo(2, Color{ 1.0, 0.0, 0.0 }));

	//---------------RUEDAS------------------
	Color colorRueda = Color{ 0.0, 0.0, 1.0 };
	GLfloat radioRueda = 0.5f;

	this->introduceObjeto(new Rueda(radioRueda, colorRueda));
	PuntoVector3D * aux = new PuntoVector3D(-0.7f, -0.7f, 1.0f, 1);
	hijos[1]->traslada(aux);
	delete aux;

	this->introduceObjeto(new Rueda(radioRueda, colorRueda));
	aux = new PuntoVector3D(0.7f, -0.7f, 1.0f, 1);
	hijos[2]->traslada(aux);
	delete aux;

	this->introduceObjeto(new Rueda(radioRueda, colorRueda));
	aux = new PuntoVector3D(-0.7f, -0.7f, -1.0f, 1);
	hijos[3]->traslada(aux);
	hijos[3]->rota(180.0f, 0.0f, 1.0f, 0.0f);
	delete aux;

	this->introduceObjeto(new Rueda(radioRueda, colorRueda));
	aux = new PuntoVector3D(0.7f, -0.7f, -1.0f, 1);
	hijos[4]->traslada(aux);
	hijos[4]->rota(180.0f, 0.0f, 1.0f, 0.0f);
	delete aux;

	//---------------RUEDAS------------------

	//---------------FAROS------------------

	Color colorFaros = Color{ 1.0, 1.0, 0.0 };

	this->introduceObjeto(new Cilindro(0.2, 0.3, 0.4, 30, 30, colorFaros));
	aux = new PuntoVector3D(1.0f, -0.2f, 0.5f, 1);
	hijos[5]->traslada(aux);
	hijos[5]->rota(90.0f, 0.0f, 1.0f, 0.0f);
	delete aux;

	this->introduceObjeto(new Cilindro(0.2, 0.3, 0.4, 30, 30, colorFaros));
	aux = new PuntoVector3D(1.0f, -0.2f, -0.5f, 1);
	hijos[6]->traslada(aux);
	hijos[6]->rota(90.0f, 0.0f, 1.0f, 0.0f);
	delete aux;

	//---------------FAROS------------------
}

Coche::~Coche()
{
}
