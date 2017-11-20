#ifndef _H_CParticleSystem_H_
#define	_H_CParticleSystem_H_

#include "Lista.h"
#include "ObjetoCompuesto.h"


class CParticleSystem : public ObjetoCompuesto {

public:
	class CParticle{
		
	public:
		CParticle(GLfloat m, PuntoVector3D pos, PuntoVector3D vel, GLfloat tRestante, GLfloat tam, GLfloat color[4]);
		~CParticle();

		// ACCESO Y MODIFICACION DE ATRIBUTOS
		/**********************************************/
		PuntoVector3D GetPos() { return pos; }
		PuntoVector3D GetVel() { return velocidad; }
		inline void SetVel(PuntoVector3D v) { velocidad = v; }
		PuntoVector3D GetForce() { return fuerzas; }
		inline void SetForce(PuntoVector3D f) { fuerzas = f; }

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// Necesito hacer sobrecarga de operadores en PV3D
		inline void AddForce(PuntoVector3D f) { fuerzas = fuerzas + f; /*fuerzas += f;*/}

		GLfloat GetLife() { return tRestante; }
		GLfloat GetTam() { return tam; }
		GLfloat * GetColor() { return color; }
		GLfloat GetMass() { return m; }

	private:

		GLfloat m;					// Masa
		PuntoVector3D pos;			// Posicion
		PuntoVector3D velocidad;	// velocidad
		PuntoVector3D fuerzas;		// Acumulador de fuerzas
		GLfloat tRestante;			// Tiempo de vida restante
		GLfloat tam;				// Tamaño
		GLfloat color[4];			// Color

	};

public:
	CParticleSystem(GLfloat mass, GLfloat varMass, GLfloat Kvd, int numParticles, 
		GLfloat color[4], GLfloat varColor[4], GLfloat m_irl, GLfloat varLife, GLfloat tam, GLfloat varTam);
	virtual ~CParticleSystem();

	// ACCESO Y MODIFICACION DE ATRIBUTOS
	/**********************************************/
	inline int GetNumParticles() const { return aParticles->_length(); }
	GLfloat GetKvd() { return Kvd; }
	inline void SetColllisionCheckActive(bool v) { colllisionCheckActive = v; }
	inline bool GetCollisionCheckActive() const { return colllisionCheckActive; }
	// CParticle * GetParticle(int i) { return aParticles; }
	inline void RemoveParticle(int i) {
		CParticle * p;
		aParticles->_get(i, p);
		aParticles->_remove(i);
		delete p;
	}

	GLfloat GetLife() { return m_irl; }
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
	tLista<CParticle*> *aParticles;		// Array de punteros a particulas
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