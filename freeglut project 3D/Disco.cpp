#include "Disco.h"


Disco::Disco(GLdouble iR, GLdouble oR, int sl, int rg, Color c) : ObjetoCuadrico(c),
innerRadius(iR), outerRadius(oR), slices(sl), rings(rg)
{
}


Disco::~Disco()
{
}

void Disco::dibuja()
{
	ObjetoCuadrico::dibuja();
	glPushMatrix();
	glMultMatrixf(this->mT->getM());
		gluDisk(objCua, innerRadius, outerRadius, slices, rings);
	glPopMatrix();
}