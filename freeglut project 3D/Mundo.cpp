#include "Mundo.h"


Mundo::Mundo(GLfloat x, GLfloat y, GLfloat z, PuntoVector3D gravedad)
	: xLength(x), yLength (y), zLength(z), gravityVector(gravedad)
{
}


Mundo::~Mundo()
{
}
