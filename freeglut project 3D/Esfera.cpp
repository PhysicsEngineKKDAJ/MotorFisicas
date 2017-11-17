#include "Esfera.h"


Esfera::Esfera(GLdouble r, int sl, int st,Color c) : ObjetoCuadrico(c),radio(r), slices(sl), stacks(st)
{

}


Esfera::~Esfera()
{
}

void Esfera::dibuja()
{
	ObjetoCuadrico::dibuja();
	glPushMatrix();
	glMultMatrixf(this->mT->getM());
		gluSphere(objCua, radio, slices, stacks);
	glPopMatrix();
}
