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

CRigidBody::CRigidBody(CGeoBox* box)
{
	aBodyBoundingVertices = new tLista<vector_3>;
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

CRigidBody::CConfig::CConfig()
{
	aBoundingVertices = new tLista<vector_3>;
}
CRigidBody::CConfig::CConfig(const CConfig& c)
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

	aBoundingVertices = new tLista<vector_3>(*c.aBoundingVertices);
}
CRigidBody::CConfig::~CConfig()
{
	delete aBoundingVertices;
	aBoundingVertices = NULL;
}

void CRigidBody::Integrate(real DeltaTime, unsigned int ConfIndex, unsigned int TargetIndex)
{

	CRigidBody::CConfig* Source = GetConfiguration(ConfIndex);
	CRigidBody::CConfig* Target = GetConfiguration(TargetIndex);



	Target->SetCMPosition(Source->GetCMPosition() +
		DeltaTime * Source->GetCMVelocity());

	Target->SetOrientation(Source->GetOrientation() +
		DeltaTime *
		matrix_3x3(Source->GetAngularVelocity(), matrix_3x3::SkewSymmetric) *
		Source->GetOrientation());

	Target->SetCMVelocity(Source->GetCMVelocity() +
		(DeltaTime * GetOneOverMass()) * Source->GetCMForce());

	Target->SetAngularMomentum(Source->GetAngularMomentum() +
		DeltaTime * Source->GetTorque());

	matrix_3x3 m = Target->GetOrientation();
	OrthonormalizeOrientation(m);
	Target->SetOrientation(m);

	// compute auxiliary quantities

	Target->SetInverseWorldInertiaTensor(Target->GetOrientation() *
		GetInverseBodyInertiaTensor() *
		Transpose(Target->GetOrientation()));

	Target->SetAngularVelocity(Target->GetInverseWorldInertiaTensor() *
		Target->GetAngularMomentum());
}

void CRigidBody::CalculateVertices(int ConfigurationIndex)
{
	vector_3 vAux;
	CRigidBody::CConfig *Configuration = this->GetConfiguration(ConfigurationIndex);
	matrix_3x3 const &A = Configuration->GetOrientation();
	vector_3 const &R = Configuration->GetCMPosition();


	for (int unsigned i = 0; i < this->GetNumberOfBoundingVertices(); i++)
	{
		*Configuration->GetBoundingVertice(i) =
			R + A * this->GetBodyBoundingVertice(i);
	}
}

vector_3 CRigidBody::GetBodyBoundingVertice(const int& i)
{
	vector_3 s;
	aBodyBoundingVertices->_get(i, s);
	return s;
}

vector_3* CRigidBody::CConfig::GetBoundingVertice(const int& i)
{
	vector_3* v;
	aBoundingVertices->_getPointer(i, v);
	return v;
}

void CRigidBody::AddBodyBoundingVertice(vector_3 v)
{
	aBodyBoundingVertices->_add(v);
	for (int i = 0; i<NumberOfConfigurations; i++)
		aConfigurations[i]->aBoundingVertices->_add(v);

}
