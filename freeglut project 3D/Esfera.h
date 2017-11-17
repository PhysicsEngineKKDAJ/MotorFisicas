#ifndef _H_Esfera_H_
#define _H_Esfera_H_

#include "ObjetoCuadrico.h"

class Esfera : public ObjetoCuadrico
{
public:
	Esfera(GLdouble r, int sl, int st,Color c);
	~Esfera();
	void dibuja();

private:
	GLdouble radio;
	int slices, stacks;//Meridianos, paralelos
};

#endif