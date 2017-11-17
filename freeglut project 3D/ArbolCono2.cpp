#include "ArbolCono2.h"
#include "CopaDobleCono.h"
#include "Cilindro.h"

ArbolCono2::ArbolCono2(GLfloat h, GLfloat c) : ObjetoCompuesto(2)
{
	//COPA
	this->introduceObjeto(new CopaDobleCono(c, Color{ 0.0, 0.4, 0.0 }));

	//TRONCO
	this->introduceObjeto(new Cilindro(0.5, 0.3, 5.0*h, 30, 30, Color{ 0.6, 0.3, 0.0 }));

	PuntoVector3D * aux = new PuntoVector3D(0.0f, 5.0f*h , 0.0f, 1);

	hijos[0]->traslada(aux);
	delete aux;

	hijos[1]->rota(-90.0f, 1.0f, 0.0f, 0.0f);//Rotación del tronco
}

ArbolCono2::~ArbolCono2()
{
}