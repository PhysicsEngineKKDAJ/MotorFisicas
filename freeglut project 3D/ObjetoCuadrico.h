#ifndef _H_ObjetoCuadrico_H_
#define _H_ObjetoCuadrico_H_

#include "Objeto3D.h"

class ObjetoCuadrico : public Objeto3D
{
public:
	ObjetoCuadrico(Color c);
	virtual ~ObjetoCuadrico();

	virtual void dibuja();//Solamente aplica el color y carga la matriz ModelView

protected:
	//Se proporcionan con la librería GLU
	GLUquadricObj* objCua;
};
#endif
