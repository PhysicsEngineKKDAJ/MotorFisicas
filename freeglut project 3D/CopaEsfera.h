#ifndef _H_CopaEsfera_H_
#define _H_CopaEsfera_H_

#include "ObjetoCompuesto.h"


class CopaEsfera : public ObjetoCompuesto
{
public:
	CopaEsfera(GLfloat c, Color color);
	~CopaEsfera();
};
#endif