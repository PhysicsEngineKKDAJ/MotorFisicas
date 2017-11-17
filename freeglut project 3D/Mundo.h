#include "ObjetoCompuesto.h"
#include <list>

//Es un contenedor para todos los objetos y características del mundo.
//Ofrece métodos de modificación
class Mundo
{
public:
	Mundo(GLfloat x, GLfloat y, GLfloat z, PuntoVector3D gravedad);
	~Mundo();

	inline GLfloat getWorldXLength()  { return xLength; };
	inline GLfloat getWorldYLength()  { return yLength; };
	inline GLfloat getWorldZLength()  { return zLength; };
	inline PuntoVector3D getGravity()  { return gravityVector; };
	inline void setGravity(GLfloat x, GLfloat y, GLfloat z){ gravityVector = PuntoVector3D(x, y, z, 1); };

	//----------------------MUROS-------------------------
	//Planos que delimitan el mundo
	//CAMBIAR OBJETO3D POR WALL
	inline void addWall(Objeto3D* w){ walls.push_back(w); };
	inline void removeWall(Objeto3D* w){ walls; };//COMPLETAR: REMOVER PASANDO EL MURO	inline void removeWall(unsigned int pos){ walls; };//COMPLETAR: REMOVER PASANDO UN INDICE	inline unsigned int getNumWalls(){ return walls.size(); };	//----------------------MUROS-------------------------

	//---------------------PARTICLE SYSTEM-------------------------
	//CAMBIAR OBJETO3D POR PARTICLE SYSTEM
	inline void addParticleSystem(Objeto3D* p){ particleSystems.push_back(p); };
	inline void removeParticleSystem(Objeto3D* p){ particleSystems; };//COMPLETAR: REMOVER PASANDO EL MURO	inline void removeParticleSystem(unsigned int pos){ particleSystems; };//COMPLETAR: REMOVER PASANDO UN INDICE	inline unsigned int getNumParticleSystems(){ return particleSystems.size(); };
	//---------------------PARTICLE SYSTEM-------------------------

	//---------------------CUERPOS RÍGIDOS----------------
	//CAMBIAR OBJETO3D POR RIGIDBODY
	inline void addRigidBody(Objeto3D* b){ rigidBodies.push_back(b); };
	inline unsigned int getNumRigidBodies(){ return rigidBodies.size(); };
	inline void removeRigidBody(unsigned int pos){ rigidBodies; };//COMPLETAR: REMOVER PASANDO UN INDICE	inline void removeRigidBody(Objeto3D* b){ rigidBodies.remove(b); };//COMPLETAR: REMOVER PASANDO EL MURO
	//---------------------CUERPOS RÍGIDOS----------------

	//---------------------WORLD SPRINGS------------------------
	//Uniones elasticas entre un punti fijo del espacio y un vertice de un determinado cuerpo
	//IMPLEMENTAR
	//---------------------WORLD SPRINGS-------------------------

	//---------------------BODY SPRINGS------------------------
	//Uniones elásticas entre dos sólidos
	//IMPLEMENTAR
	//---------------------BODY SPRINGS-------------------------

	//---------------------PARTICLE SPRINGS------------------------
	//Uniones elásticas entre dos partículas o una partícula y un punto del espacio
	//IMPLEMENTAR
	//---------------------PARTICLE SPRINGS------------------------

private:
	GLfloat xLength, yLength, zLength;
	PuntoVector3D gravityVector;

	std::list<Objeto3D*> walls; 	//Lista de objetos que contiene
	std::list<Objeto3D*> rigidBodies; 	//Lista de objetos que contiene 
	std::list<Objeto3D*> particleSystems; 	//Lista de objetos que contiene 

};

