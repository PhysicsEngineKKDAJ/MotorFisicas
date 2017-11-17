#include "ArbolEsfera2.h"
#include "CopaDobleEsfera.h"
#include "Cilindro.h"

ArbolEsfera2::ArbolEsfera2(GLfloat h, GLfloat c) : ObjetoCompuesto(2)
{
	//COPA
	this->introduceObjeto(new CopaDobleEsfera(c, Color{ 1.0, 0.64, 0.12 }));

	//TRONCO
	this->introduceObjeto(new Cilindro(0.4, 0.2, 5.0*h, 30, 30, Color{ 0.6, 0.3, 0.0 }));

	PuntoVector3D * aux = new PuntoVector3D(0.0f, h*5.0f, 0.0f, 1);
	hijos[0]->traslada(aux);
	delete aux;

	hijos[1]->rota(-90.0f, 1.0f, 0.0f, 0.0f);
}


ArbolEsfera2::~ArbolEsfera2()
{
}
