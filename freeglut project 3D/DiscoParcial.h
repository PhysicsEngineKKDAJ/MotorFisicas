#ifndef _H_DiscoParcial_H_
#define _H_DiscoParcial_H_

#include "ObjetoCuadrico.h"

/*
Los ángulos se miden en sentido horario, mirando desde
la parte positiva del eje Z, sobre el plano XY,
empezando en el eje Y.
*/
class DiscoParcial : public ObjetoCuadrico
{
public:
	DiscoParcial(GLdouble iR, GLdouble oR, int sl, int rg, GLdouble swt, GLdouble swa, Color c);
	~DiscoParcial();
	void dibuja();

private:
	GLdouble innerRadius, outerRadius, startAngle, sweepAngle;
	int slices, rings;

};

#endif
