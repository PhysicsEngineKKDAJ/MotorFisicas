#ifndef _H_Escena_H_
#define _H_Escena_H_

#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

#include "Coche.h"
#include "ObjetoCompuesto.h"
#include <vector>
#include "Camara.h"
#include "QuadTree.h"

enum movCoche{ ArribaIz, AbajoIz, ArribaDe, AbajoDe };

// Viewport size

class Escena : public ObjetoCompuesto {
public:
	Escena(int n);
	~Escena();

	void dibuja();

	inline GLfloat getAngX()const{ return angX; };
	inline GLfloat getAngY()const{ return angY; };
	inline GLfloat getAngZ()const{ return angZ; };

	inline void setAngX(GLfloat x) { angX = x; };
	inline void setAngY(GLfloat y) { angY = y; };
	inline void setAngZ(GLfloat z) { angZ = z; };

	void moverCoche(movCoche avanza);

	void resize(int newWidth, int newHeight);
	void giraX(GLfloat ang) { camera->giraX(ang); };
	void roll(GLfloat ang){ camera->roll(ang); };
	inline void cambiarModo(){ isCulled = !isCulled; };

private:
	int WIDTH = 500, HEIGHT = 500;
	int nArbolesTalados;
	int numArboles;
	const GLfloat angGiro = 15;
	GLfloat angX, angY, angZ;

	Camara *camera;
	bool isCulled;

	void dibujaEjes();
	void rotaEscena();

	bool colisionCocheArbol(Objeto3D* arbol);

	QuadTree *treeQuadtree;
};
#endif
