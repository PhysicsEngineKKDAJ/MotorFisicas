#include "CParticleSystem.h"



// METODOS DE CParticleSystem
/**********************************************/
CParticleSystem::CParticleSystem(GLfloat mass, GLfloat varMass, GLfloat Kvd, int numParticles,
	GLfloat color[4], GLfloat varColor[4], GLfloat m_irl, GLfloat varLife, GLfloat tam, GLfloat varTam)
	: Kvd_(Kvd), particleMass_(mass), varMass_(varMass), numMAxParticles_(numParticles), m_irl_(m_irl),
	varLife_(varLife), tam_(tam), varTam_(varTam)
{
	colllisionCheckActive = false;

	color_[0] = color[0];
	color_[1] = color[1];
	color_[2] = color[2];
	color_[3] = color[3];

	varColor_[0] = varColor[0];
	varColor_[1] = varColor[1];
	varColor_[2] = varColor[2];
	varColor_[3] = varColor[3];

}

CParticleSystem::~CParticleSystem()
{
	delete aParticles;
	aParticles = NULL;
}
/**********************************************/