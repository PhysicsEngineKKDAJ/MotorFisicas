#ifndef _H_CopaDobleCono_H_
#define _H_CopaDobleCono_H_

#include "ObjetoCompuesto.h"


class CopaDobleCono : public ObjetoCompuesto
{
public:
	CopaDobleCono(GLfloat c, Color color);
	~CopaDobleCono();
};
#endif