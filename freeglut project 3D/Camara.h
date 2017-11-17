#ifndef _H_Camara_H_
#define _H_Camara_H_

#include <GL/freeglut.h>
#include <cmath>
#include "PuntoVector3D.h"


class Camara {
public:
	Camara(GLdouble aw, GLdouble ah) : 
		xRight(10), xLeft(-xRight), yTop(10), yBot(-yTop), nearVal(30), farVal(200)
	{
		eye = new PuntoVector3D(0.0, 50.0, 0.0, 1);
		look = new PuntoVector3D(0.0, 0.0, 0.0, 1);
		up = new PuntoVector3D(1.0, 1.0, 0.0, 1);
	};
	~Camara() 
	{
		delete eye;
		delete look;
		delete up;
	};

	void setPos(PuntoVector3D* ay, PuntoVector3D *al, PuntoVector3D* ap);
	void setPos();

	void setVV(GLdouble aw, GLdouble ah);
	void setVV();
	//void setVV(GLdouble xL, GLdouble xR, GLdouble yT, GLdouble yB, GLdouble nV, GLdouble fV) { nearVal = nV; farVal = fV; setVV(xL, xR, yT, yB, nV, fV); };

	void setEye(GLfloat x, GLfloat z);

	void giraX(GLfloat ang);
	void roll(GLfloat ang);
	//void setEZ();
	//void set3D();
public:
	//Ojo punto donde la colocamos
	//Look 
	//Up. Lo habitual es 0,1,0. La y es la vertical
	// Camera parameters
	PuntoVector3D *eye,* look, *up;

	// Viewing frustum parameters
	GLdouble xRight, xLeft, yTop, yBot, nearVal, farVal;

	PuntoVector3D *n,*u, *v ; 
	//n = (eye-look).normalizar();
	//u = (up x n).normalizar();
	//v = n * u

	//Los movimientos de la cámara se pueden realizar de dos formas, moviendo eye,etc.
	//O transformando el sistema de referencias de la cámara con la matriz
	void setModelViewMatrix();//Pasa del sistema global al sistema de camara
	void calcularNUV();
};

#endif
