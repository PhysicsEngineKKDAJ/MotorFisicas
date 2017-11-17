#ifndef _H_Disco_H_
#define _H_Disco_H_

#include "ObjetoCuadrico.h"
class Disco : public ObjetoCuadrico
{
public:
	Disco(GLdouble iR, GLdouble oR, int sl, int rg, Color c);
	~Disco();
	void dibuja();

private:
	GLdouble innerRadius, outerRadius;
	int slices, rings; //nºlados, nºanillos
};

#endif