#ifndef _H_Rueda_H_
#define _H_Rueda_H_

#include"ObjetoCompuesto.h"


class Rueda : public ObjetoCompuesto
{
public:
	Rueda(GLfloat radio, Color color);
	~Rueda();
};
#endif