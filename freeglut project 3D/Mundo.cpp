#include "Mundo.h"


Mundo::Mundo(GLfloat x, GLfloat y, GLfloat z, PuntoVector3D gravedad)
	: tam(x, y, z, 0), gravityVector(gravedad)
{
}


Mundo::~Mundo()
{
}
