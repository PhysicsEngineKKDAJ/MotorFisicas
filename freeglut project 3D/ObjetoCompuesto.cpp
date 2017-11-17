#include "ObjetoCompuesto.h"


ObjetoCompuesto::ObjetoCompuesto(int nHijos)
{
	hijos = new Objeto3D* [nHijos];
	numHijos = 0;
}


ObjetoCompuesto::~ObjetoCompuesto()
{
	for (int i = 0; i < numHijos; i++)
		delete(hijos[i]);

}

void ObjetoCompuesto::introduceObjeto(Objeto3D* obj) {
	hijos[numHijos] = obj;
	numHijos++;
}

void ObjetoCompuesto::dibuja() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(this->mT->getM());
	for (int i = 0; i<numHijos; i++)
		hijos[i]->dibuja();
	glPopMatrix();
}