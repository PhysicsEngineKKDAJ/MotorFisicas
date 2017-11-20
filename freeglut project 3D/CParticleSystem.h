#ifndef _H_CParticleSystem_H_
#define	_H_CParticleSystem_H_

#include "Lista.h"
#include "ObjetoCompuesto.h"
// #include "CParticle.h"

class CParticleSystem : public ObjetoCompuesto {
public:
	CParticleSystem(GLfloat mass, GLfloat varMass, GLfloat Kvd, int numParticles, 
		GLfloat color[4], GLfloat varColor[4], GLfloat m_irl, GLfloat varLife, GLfloat tam, GLfloat varTam);
	virtual ~CParticleSystem();

	// ACCESO Y MODIFICACION DE ATRIBUTOS
	/**********************************************/
	inline int GetNumParticles() const;
	GLfloat GetKvd();
	void SetColllisionCheckActive(bool v);
	inline bool GetCollisionCheckActive() const;
	CParticle * GetParticle(int i);
	void RemoveParticle(int i);
	GLfloat GetLife();
	/**********************************************/

	// METODOS VIRTUALES PUROS
	/**********************************************/
	// En caso de que se produzca colision.
	// Particula y su posicion en la lista
	virtual void ParticleCollisionEvent(CParticle * particle, int pos) = 0;

	// En caso de cada paso de la simulacion
	virtual bool SimulateStepParticle(CParticle * particle, int pos, GLfloat DeltaTime) = 0;

private:

protected:
	bool colllisionCheckActive;			// Indican si se resuelven las colisiones en el sistema
	tLista<CParticle*> *aPArticles;		// Array de punteros a particulas
	GLfloat Kvd;						// Constante de rozamiento
	GLfloat particleMass;				// masa aproximada de las particulas
	GLfloat varMass;					// Masa de las particulas
	int numMAxParticles;				// Nº maximo de particulas
	GLfloat color[4];					// Color de las particulas
	GLfloat varColor[4];				// Variacion de color de las particulas
	GLfloat m_irl;						// Vida de las particulas, -1 = no mueren
	GLfloat varLife;					// Variacion de la vida
	GLfloat tam;						// tamaño de las particulas
	GLfloat varTam;						// Variacion del tamaño de las particulas
};
#endif