#ifndef _H_RigidBody_H_
#define _H_RigidBody_H_

#include "matriz3x3.h"
#include "Lista.h"

/*Tiene todos los datos necesarios para definir un sólido*/
class RigidBody
{
public:
	class CConfig
	{
	private:


		friend class RigidBody;

		// primary quantities
		PuntoVector3D velocity; //Velocidad del centro de masas
		PuntoVector3D angularMomentum;

		PuntoVector3D position; //Posicion del centro de masas
		matrix3x3 orientation;

		// auxiliary quantities
		matrix3x3 inverseInertiaTensor;
		PuntoVector3D angularVelocity;

		PuntoVector3D force;//Acumulador de fuerzas
		PuntoVector3D torque;//Acumulador de fuerzas de rotacion

		tLista<PuntoVector3D> *aBoundingVertices;//lista de vértices tomando como referencia el centro de masas.

	public:

		CConfig();
		CConfig(const CConfig& c);
		~CConfig();


		//Acceso y modificacion de atributos
		inline PuntoVector3D GetPosition(){ return position; };
		inline void SetPosition(PuntoVector3D v){ position = v; };

		inline matrix3x3 GetOrientation(){ return orientation; };
		inline void SetOrientation(matrix3x3 v){ orientation = v; };

		inline PuntoVector3D GetAngularVelocity(){ return angularVelocity; };
		inline void SetAngularVelocity(PuntoVector3D v){ angularVelocity = v; };

		inline matrix3x3 GetInverseInertiaTensor(){ return inverseInertiaTensor; };
		inline void SetInverseInertiaTensor(matrix3x3 v){ inverseInertiaTensor = v; };

		inline PuntoVector3D GetForce(){ return force; };
		inline void AddForce(PuntoVector3D v){ force = force + v; };
		inline void ClearForce(){ force = PuntoVector3D(); };

		inline PuntoVector3D GetTorque(){ return torque; };
		inline void AddTorque(PuntoVector3D v){ torque = torque + v; };
		inline void ClearTorque(){ torque = PuntoVector3D(); };

		inline PuntoVector3D GetVelocity(){ return velocity; };
		inline void SetVelocity(PuntoVector3D v){ velocity = v; };

		inline PuntoVector3D GetAngularMomentum(){ return angularMomentum; };
		inline void SetAngularMomentum(PuntoVector3D v){ angularMomentum = v; };

		PuntoVector3D *GetBoundingVertice(const int& i);
		inline tLista<PuntoVector3D> *GetBoundingVertices(){ return aBoundingVertices; };

	};

	//Crea un sólido con una geometría determinada
	RigidBody(BoxCollision* box);
	~RigidBody();

	//-----------GETTER--------------
	GLfloat GetKdl(void){ return Kdl; };
	GLfloat GetKda(void){ return Kda; };
	bool GetInmovil(void);
	bool GetDormido(void);
	GLfloat GetOneOverMass(void);

	//-----------GETTER--------------

	GLfloat GetCoefficientOfRestitution(void);
	void SetCoefficientOfRestitution(GLfloat v);
	matrix3x3 GetInverseBodyInertiaTensor(void);
	void SetInverseBodyInertiaTensor(matrix3x3 m);
	Config* GetConfiguration(int i);
	void Integrate(GLfloat DeltaTime, int ConfIndex, int Target);
	int GetNumberOfBoundingVertices(void);
	PuntoVector3D GetBodyBoundingVertice(int i);
	void AddBodyBoundingVertice(PuntoVector3D v);
	BoxCollision* GetGeoBox();

	//-----------SETTER--------------
	inline void SetKdl(GLfloat v){ Kdl = v; };
	inline void SetKda(GLfloat v){ Kda = v; };
	inline void SetInmovil(bool v);
	inline void SetDormido(bool v);
	inline void SetOneOverMass(GLfloat v);
	//-----------SETTER--------------


private:
	GLfloat Kdl;// Factor de amortiguamiento lineal
	GLfloat Kda;//Factor de amortiguamiento angular
	GLfloat CoefficientOfRestitution;//Coeficiente de rozamiento
	GLfloat inverseMass;

	matrix3x3 inverseBodyInertiaTensor;

	tLista<PuntoVector3D> *aBodyBoundingVertices; //Array de vértices que componen el objeto tomando el origen como referencia

	bool inmovil, dormido;

	/*array de configuraciones. Cada configuración se almacenan los datos del sólido que varían en cada simulación,
	de forma que se tiene varias configuraciones almacenadas que deben ser gestionadas por el resolutor*/
	//Por ejemplo, el resolutor de Euler solo necesita dos configuraciones, anterior y presente.
	Config ** aConfigurations;

	/*
		Define la geometría para ser utilizada por colisiones
	*/
	BoxCollision * boxCollision;


	/*Método que calcula los vértices de la configuración indicada 
	seguún su matriz de orientacion y el centro de masas*/
	void CalculateVertices(int ConfigurationIndex);


};

#endif