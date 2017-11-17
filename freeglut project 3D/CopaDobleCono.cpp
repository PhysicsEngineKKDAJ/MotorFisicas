#include "CopaDobleCono.h"
#include "Cilindro.h"

CopaDobleCono::CopaDobleCono(GLfloat c, Color color) : ObjetoCompuesto(2)
{
	this->introduceObjeto(new Cilindro(2.0*c, 0.0f, 5.0*c, 30, 30, color));
	this->introduceObjeto(new Cilindro(2.0*c, 0.0f, 5.0*c, 30, 30, color));

	PuntoVector3D* aux = new PuntoVector3D(0.0f, c*2.0f, 0.0f, 1);
	hijos[1]->traslada(aux);
	delete aux;

	hijos[0]->rota(-90.0f, 1.0f, 0.0f, 0.0f);//Rotación de la copa
	hijos[1]->rota(-90.0f, 1.0f, 0.0f, 0.0f);//Rotación del tronco
}


CopaDobleCono::~CopaDobleCono()
{
}
