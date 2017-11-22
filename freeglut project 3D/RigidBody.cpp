#include "RigidBody.h"

const int NumberOfConfigurations = 2;

RigidBody::RigidBody()
{
	aBodyBoundingVertices = new tLista<PuntoVector3D>;
	aConfigurations = new CConfig*[NumberOfConfigurations];

	for (unsigned int i = 0; i<NumberOfConfigurations; i++)
		aConfigurations[i] = new CConfig();

	boundingBox = NULL;
	inmovil = false;
	dormido = false;
}

RigidBody::RigidBody(CGeoBox* box)
{
	aBodyBoundingVertices = new tLista<PuntoVector3D>;
	aConfigurations = new CConfig*[NumberOfConfigurations];
	boundingBox = box;

	for (unsigned int i = 0; i<NumberOfConfigurations; i++)
		aConfigurations[i] = new CConfig();

	inmovil = false;
	dormido = false;
}

RigidBody::~RigidBody()
{
	delete aBodyBoundingVertices;
	for (unsigned int i = 0; i<NumberOfConfigurations; i++)
		delete aConfigurations[i];
	delete aConfigurations;
	if (boundingBox != NULL)
	{
		delete boundingBox;
		boundingBox = NULL;
	}
}

RigidBody::CConfig::CConfig()
{
	aBoundingVertices = new tLista<PuntoVector3D>;
}
RigidBody::CConfig::CConfig(const CConfig& c)
{
	CMVelocity = c.CMVelocity;
	AngularMomentum = c.AngularMomentum;

	CMPosition = c.CMPosition;
	Orientation = c.Orientation;

	// auxiliary quantities
	InverseWorldInertiaTensor = c.InverseWorldInertiaTensor;
	AngularVelocity = c.AngularVelocity;

	CMForce = c.CMForce;
	Torque = c.Torque;

	aBoundingVertices = new tLista<PuntoVector3D>(*c.aBoundingVertices);
}
RigidBody::CConfig::~CConfig()
{
	delete aBoundingVertices;
	aBoundingVertices = NULL;
}

void RigidBody::Integrate(float DeltaTime, unsigned int ConfIndex, unsigned int TargetIndex)
{

	RigidBody::CConfig* Source = GetConfiguration(ConfIndex);
	RigidBody::CConfig* Target = GetConfiguration(TargetIndex);



	Target->SetCMPosition(Source->GetCMPosition() +
		DeltaTime * Source->GetCMVelocity());

	Target->SetOrientation(Source->GetOrientation() +
		DeltaTime *
		matriz3x3(Source->GetAngularVelocity(), matrix3x3::SkewSymmetric) *
		Source->GetOrientation());

	Target->SetCMVelocity(Source->GetCMVelocity() +
		(DeltaTime * GetOneOverMass()) * Source->GetCMForce());

	Target->SetAngularMomentum(Source->GetAngularMomentum() +
		DeltaTime * Source->GetTorque());

	matriz3x3 m = Target->GetOrientation();
	OrthonormalizeOrientation(m);
	Target->SetOrientation(m);

	// compute auxiliary quantities

	Target->SetInverseWorldInertiaTensor(Target->GetOrientation() *
		GetInverseBodyInertiaTensor() *
		Transpose(Target->GetOrientation()));

	Target->SetAngularVelocity(Target->GetInverseWorldInertiaTensor() *
		Target->GetAngularMomentum());
}

void RigidBody::CalculateVertices(int ConfigurationIndex)
{
	PuntoVector3D vAux;
	RigidBody::CConfig *Configuration = this->GetConfiguration(ConfigurationIndex);
	matriz3x3 const &A = Configuration->GetOrientation();
	PuntoVector3D const &R = Configuration->GetCMPosition();


	for (int unsigned i = 0; i < this->GetNumberOfBoundingVertices(); i++)
	{
		*Configuration->GetBoundingVertice(i) =
			R + A * this->GetBodyBoundingVertice(i);
	}
}

PuntoVector3D RigidBody::GetBodyBoundingVertice(const int& i)
{
	PuntoVector3D s;
	aBodyBoundingVertices->_get(i, s);
	return s;
}

PuntoVector3D* RigidBody::CConfig::GetBoundingVertice(const int& i)
{
	PuntoVector3D* v;
	aBoundingVertices->_getPointer(i, v);
	return v;
}

void RigidBody::AddBodyBoundingVertice(vector_3 v)
{
	aBodyBoundingVertices->_add(v);
	for (int i = 0; i<NumberOfConfigurations; i++)
		aConfigurations[i]->aBoundingVertices->_add(v);

}
