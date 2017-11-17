#ifndef _H_Cilindro_H_
#define _H_Cilindro_H_

#include "ObjetoCuadrico.h"

//Se construye sobre el eje Z
class Cilindro : public ObjetoCuadrico
{
public:
	Cilindro(GLdouble rB, GLdouble rT, GLdouble a, int sl, int st,Color c);
	~Cilindro();
	void dibuja();

private:
	GLdouble radioBase, radioTop, altura;
	int slices, stacks;//Lados, rodajas
};

#endif