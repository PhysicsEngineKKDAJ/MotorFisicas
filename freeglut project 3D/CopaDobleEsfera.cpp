#include "CopaDobleEsfera.h"
#include "Esfera.h"

CopaDobleEsfera::CopaDobleEsfera(GLfloat c, Color color) :ObjetoCompuesto(2)
{
	this->introduceObjeto(new Esfera(1.2* c, 30, 30, color));
	this->introduceObjeto(new Esfera(1.0 * c, 30, 30, color));

	PuntoVector3D * aux = new PuntoVector3D(-0.5f*c,0.0f, 0.5f*c, 1);

	hijos[0]->traslada(aux);

	delete aux;

	aux = new PuntoVector3D(0.5f*c, 0.0f, -0.5f*c, 1);

	hijos[1]->traslada(aux);

	delete aux;
}


CopaDobleEsfera::~CopaDobleEsfera()
{
}
