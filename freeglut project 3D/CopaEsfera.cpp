#include "CopaEsfera.h"
#include "Esfera.h"

CopaEsfera::CopaEsfera(GLfloat c, Color color) : ObjetoCompuesto(1)
{
	this->introduceObjeto(new Esfera(1.5 * c, 30, 30, color));
	hijos[0]->rota(-90.0f, 1.0f, 0.0f, 0.0f);//Rotación de la copa
}


CopaEsfera::~CopaEsfera()
{
}
