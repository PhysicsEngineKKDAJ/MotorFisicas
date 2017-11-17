#include "ArbolEsfera1.h"
#include "CopaEsfera.h"
#include "Cilindro.h"

ArbolEsfera1::ArbolEsfera1(GLfloat h, GLfloat c) : ObjetoCompuesto(2)
{
	this->introduceObjeto(new CopaEsfera(c, Color{ 0.92, 0.54, 0.60 }));
	this->introduceObjeto(new Cilindro(0.4, 0.2, 5*h, 30, 30, Color{ 0.6, 0.3, 0.0 }));

	PuntoVector3D * aux = new PuntoVector3D(0.0f, 5.0f*h + 1.5f*c, 0.0f ,1);

	hijos[0]->traslada(aux);

	delete aux;
	hijos[1]->rota(-90.0f,1.0f,0.0f,0.0f);
}


ArbolEsfera1::~ArbolEsfera1()
{
}
