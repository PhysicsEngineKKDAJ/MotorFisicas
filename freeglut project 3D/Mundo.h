#include "ObjetoCompuesto.h"

//Es un contenedor para todos los objetos y características del mundo.
//Ofrece métodos de modificación
class Mundo
{
public:
	Mundo(GLfloat x, GLfloat y, GLfloat z, PuntoVector3D gravedad);
	~Mundo();

	inline GLfloat getWorldXLength()  { return tam.getX(); };
	inline GLfloat getWorldYLength()  { return tam.getY(); };
	inline GLfloat getWorldZLength()  { return tam.getZ(); };
	inline PuntoVector3D getGravity()  { return gravityVector; };
	inline int getNumWalls(){ return numWalls; };
	inline void setGravity(GLfloat x, GLfloat y, GLfloat z){ gravityVector = PuntoVector3D(x, y, z, 1); };

	//Planos que delimitan el mundo
	inline void addWall(){};//COMPLETAR

private:
	PuntoVector3D tam;
	PuntoVector3D gravityVector;

	int numWalls;
	Objeto3D** objects; 	//Lista de objetos que contiene (muros, rígidos, springs, particlesystems y fuerzas)

};

