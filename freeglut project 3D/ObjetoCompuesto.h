#ifndef _H_ObjetoCompuesto_H_
#define _H_ObjetoCompuesto_H_
#include "Objeto3D.h"

class ObjetoCompuesto : public Objeto3D
{
public:
	ObjetoCompuesto(int nHijos);
	virtual ~ObjetoCompuesto();

	//...
	void dibuja();
	void introduceObjeto(Objeto3D* objeto);

protected:
	int numHijos;
	Objeto3D** hijos;

};

#endif

