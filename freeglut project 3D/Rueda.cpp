#include "Rueda.h"
#include "Cilindro.h"
#include "Disco.h"

Rueda::Rueda(GLfloat radio, Color color) : ObjetoCompuesto(2)
{
	this->introduceObjeto(new Cilindro(radio, radio, radio, 30, 30,color));
	this->introduceObjeto(new Disco(0.0, radio, 30, 30, color));

	PuntoVector3D* aux = new PuntoVector3D(0.0f, 0.0f, radio, 1);
	hijos[1]->traslada(aux);
	delete aux;
}


Rueda::~Rueda()
{
}
