#include "DiscoParcial.h"


DiscoParcial::DiscoParcial(GLdouble iR, GLdouble oR, int sl, int rg, GLdouble swt, GLdouble swa, Color c) : ObjetoCuadrico(c),
innerRadius(iR), outerRadius(oR), slices(sl), rings(rg), startAngle(swt), sweepAngle(swa)
{
}


DiscoParcial::~DiscoParcial()
{
}

void DiscoParcial::dibuja()
{
	ObjetoCuadrico::dibuja();
	glPushMatrix();
	glMultMatrixf(this->mT->getM());
		gluPartialDisk(objCua, innerRadius, outerRadius, slices, rings,startAngle, sweepAngle);
	glPopMatrix();
}