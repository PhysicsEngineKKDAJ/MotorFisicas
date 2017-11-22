#ifndef _H_CParticleSystem_H_
#define	_H_CParticleSystem_H_

#include "Lista.h"
#include "Objeto3D.h"


class CParticleSystem : public Objeto3D	{

public:
	class CParticle{
		
	public:
		CParticle(GLfloat m, PuntoVector3D pos, PuntoVector3D vel, GLfloat tRestante, GLfloat tam, GLfloat color[4]);
		~CParticle();

		// ACCESO Y MODIFICACION DE ATRIBUTOS
		/**********************************************/
		PuntoVector3D GetPos() { return pos_; }
		PuntoVector3D GetVel() { return velocidad_; }
		inline void SetVel(PuntoVector3D v) { velocidad_ = v; }
		PuntoVector3D GetForce() { return fuerzas_; }
		inline void SetForce(PuntoVector3D f) { fuerzas_ = f; }

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// Necesito hacer sobrecarga de operadores en PV3D
		inline void AddForce(PuntoVector3D f) { fuerzas_ = fuerzas_ + f; /*fuerzas += f;*/}

		GLfloat GetLife() { return tRestante_; }
		GLfloat GetTam() { return tam_; }
		GLfloat * GetColor() { return color_; }
		GLfloat GetMass() { return m_; }

	private:

		GLfloat m_;					// Masa
		PuntoVector3D pos_;			// Posicion
		PuntoVector3D velocidad_;	// velocidad
		PuntoVector3D fuerzas_;		// Acumulador de fuerzas
		GLfloat tRestante_;			// Tiempo de vida restante
		GLfloat tam_;				// Tamaño
		GLfloat color_[4];			// Color

	};

public:
	CParticleSystem(GLfloat mass, GLfloat varMass, GLfloat Kvd, int numParticles, 
		GLfloat color[4], GLfloat varColor[4], GLfloat m_irl, GLfloat varLife, GLfloat tam, GLfloat varTam);
	virtual ~CParticleSystem();

	// ACCESO Y MODIFICACION DE ATRIBUTOS
	/**********************************************/
	inline int GetNumParticles() const { return aParticles->_length(); }
	GLfloat GetKvd() { return Kvd_; }
	inline void SetColllisionCheckActive(bool v) { colllisionCheckActive = v; }
	inline bool GetCollisionCheckActive() const { return colllisionCheckActive; }
	// CParticle * GetParticle(int i) { return aParticles; }
	inline void RemoveParticle(int i) {
		CParticle * p;
		aParticles->_get(i, p);
		aParticles->_remove(i);
		delete p;
	}

	GLfloat GetLife() { return m_irl_; }

	/**********************************************/
	
	// OPERACIONES CON PARTICULAS
	/**********************************************/
	void deleteParticle(CParticle * p1) { delete p1; }
	void copyParticle(CParticle *&p2, CParticle * p1) {
		p2 = new CParticle(*p1);
	}
	/**********************************************/

	// METODOS VIRTUALES PUROS
	/**********************************************/
	// En caso de que se produzca colision.
	// Particula y su posicion en la lista
	virtual void ParticleCollisionEvent(CParticle * particle, int pos) = 0;

	// En caso de cada paso de la simulacion
	virtual bool SimulateStepParticle(CParticle * particle, int pos, GLfloat DeltaTime) = 0;
	/**********************************************/

private:

protected:
	bool colllisionCheckActive;			// Indican si se resuelven las colisiones en el sistema
	tLista<CParticle*> *aParticles;		// Array de punteros a particulas
	GLfloat Kvd_;						// Constante de rozamiento
	GLfloat particleMass_;				// masa aproximada de las particulas
	GLfloat varMass_;					// Masa de las particulas
	int numMAxParticles_;				// Nº maximo de particulas
	GLfloat color_[4];					// Color de las particulas
	GLfloat varColor_[4];				// Variacion de color de las particulas
	GLfloat m_irl_;						// Vida de las particulas, -1 = no mueren
	GLfloat varLife_;					// Variacion de la vida
	GLfloat tam_;						// tamaño de las particulas
	GLfloat varTam_;						// Variacion del tamaño de las particulas
};
#endif