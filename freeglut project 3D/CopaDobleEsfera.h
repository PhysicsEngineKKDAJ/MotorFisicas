#ifndef _H_CopaDobleEsfera_H_
#define _H_CopaDobleEsfera_H_

#include "ObjetoCompuesto.h"


class CopaDobleEsfera : public ObjetoCompuesto
{
public:
	CopaDobleEsfera(GLfloat c, Color color);
	~CopaDobleEsfera();
};
#endif