#ifndef Cubo_H_
#define Cubo_H_

#include "Malla.h"

class CuboRevolucion : public Malla {
public:
	CuboRevolucion(GLfloat l, Color c);
	~CuboRevolucion(void);
private:
	GLfloat arista;
};
#endif
