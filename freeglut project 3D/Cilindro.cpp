#include "Cilindro.h"


Cilindro::Cilindro(GLdouble rB, GLdouble rT, GLdouble a, int sl, int st,Color c): ObjetoCuadrico(c),
	radioBase(rB), radioTop(rT), altura(a), slices(sl), stacks(st)
{

}


Cilindro::~Cilindro()
{
}

void Cilindro::dibuja()
{
	ObjetoCuadrico::dibuja();
	glPushMatrix();
	glMultMatrixf(this->mT->getM());
		gluCylinder(objCua, radioBase, radioTop, altura,slices,stacks);
	glPopMatrix();
}
