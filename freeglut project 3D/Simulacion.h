#pragma once
#include "CCollisionEngine.h"

class Simulacion
{
public:

	Simulacion(CWorld* pWorld);
	Simulacion();

	~Simulacion(void);
	virtual void Simulate(float DeltaTime) = 0;
	inline void SetMaxTimeStep(float d){ MaxTimeStep = d; };
	inline void SetDep(float d){ MaxTimeStep = d; };
	inline void SetDepthEpsilon(float d){ pCollEngine->SetDepthEpsilon(d); };
	inline void SetParticleDepthEpsilon(float d){ pCollEngine->SetParticleDepthEpsilon(d); };

protected:

	CWorld * pWorld;	//Puntero al mundo
	CCollisionEngine * pCollEngine;	//Puntero al motor de colisiones
	float MaxTimeStep;
	float LastTime;
	void CalculateVertices(int ConfigurationIndex);
};

