#include "Simulacion.h"
#include "PuntoVector3D.h"


Simulacion::Simulacion()
{

}

Simulacion::Simulacion(CWorld * pWorld)
{
	this->pWorld = pWorld;	//Recibe un puntero a mundo y lo asocia 
	pCollEngine = new CCollisionEngine(pWorld);	//Igual pero con las colisiones
	LastTime = 0;	
	MaxTimeStep = float(0.03125);//valor por defecto

	// calculate initial bounding volume positions: Calcula los vertices principales de las
	//configuraciones 0 y 1.
	CalculateVertices(0);
	CalculateVertices(1);
}


Simulacion::~Simulacion()
{
}

/*----------------------------------------------------------------------------

CalculateVertices - figure out the body vertices from the configuration*/
void Simulacion::CalculateVertices(int ConfigurationIndex)
{
	//CRigidBody *Body; 
	PuntoVector3D vAux; //Punto vector SIN INICIALIZAR DE MOMENTO
	for (unsigned int Counter = 0; Counter <pWorld->GetNumBodies(); Counter++)
	{
		//Esto hace que por cada uno de los cuerpos de la simulacion, llama a un método que tienen los cuerpos
		//que calculan sus nuevos vertices según una configuración dada por una tabla en RigidBody.

		//En definitiva, por cada objeto de la escena va a calcular sus nuevos vertices.
		Body = pWorld->GetBody(Counter);
		Body->CalculateVertices(ConfigurationIndex);
	}
}