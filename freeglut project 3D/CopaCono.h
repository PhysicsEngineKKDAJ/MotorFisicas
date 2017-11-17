#ifndef _H_CopaCono_H_
#define _H_CopaCono_H_

#include "ObjetoCompuesto.h"


class CopaCono : public ObjetoCompuesto
{
public:
	CopaCono(GLfloat c, Color color);
	~CopaCono();
};
#endif