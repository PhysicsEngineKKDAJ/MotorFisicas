#ifndef _H_TAfin_H_
#define _H_TAfin_H_

#include <Windows.h>
#include <gl/GL.h>

#include "PuntoVector3D.h"

//Contiene la matriz por la que es necesario POSTmultiplicar la de modelado vista antes de dibujarlo
class TAfin
{
public:
	TAfin();
	~TAfin();

	void traslada(PuntoVector3D * v);
	void rota(GLfloat a, GLfloat x, GLfloat y, GLfloat z);//En sentido antihorario
	void escala(PuntoVector3D * v);

	void postMultiplica(GLfloat* m1);

	inline GLfloat * getM() const { return m; };

private:
	GLfloat *m; //Matriz: Enumerados por columnas
	//...

};
#endif
