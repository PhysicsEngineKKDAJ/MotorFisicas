#include "CopaCono.h"
#include "Cilindro.h"

CopaCono::CopaCono(GLfloat c, Color color) : ObjetoCompuesto(1)
{
	this->introduceObjeto(new Cilindro(2.0*c, 0, 7.0*c, 30, 30, color));
	hijos[0]->rota(-90.0f, 1.0f, 0.0f, 0.0f);//Rotación de la copa
}


CopaCono::~CopaCono()
{
}
