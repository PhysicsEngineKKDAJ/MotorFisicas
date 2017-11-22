#include "Muro.h"


Muro::Muro()
{
}

Muro::Muro(PuntoVector3D Normal, float d)
{
	this->Normal = Normal;
	this->d = d;
}
Muro::Muro(const Muro& w)
{
	this->Normal = PuntoVector3D(w.Normal);
	this->d = w.d;
}

Muro::~Muro()
{
}
