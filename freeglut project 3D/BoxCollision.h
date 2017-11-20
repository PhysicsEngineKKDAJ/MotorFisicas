#ifndef _H_BoxCollision_H_
#define _H_BoxCollision_H_

#include "Lista.h"
#include "PuntoVector3D.h"
//Contiene información de la geometría del objeto, la utiliza el motor de colisiones
class BoxCollision
{
public:

	class QuadFace
	{
	public:
		QuadFace();
		QuadFace(int cara[]);
		QuadFace(const QuadFace& cara);
		~QuadFace();
		PuntoVector3D GetNormal(tLista<PuntoVector3D>* lista);
		PuntoVector3D GetCentro(tLista<PuntoVector3D>* lista);
		float GetD(tLista<PuntoVector3D>* lista);
		PuntoVector3D GetVertex(int i, tLista<PuntoVector3D>* lista);

		// distancia de un punto a un plano
		float GetDistance(PuntoVector3D x, tLista<PuntoVector3D>* lista);

	private:
		int lVertices[4];

	};

	BoxCollision(float radio);
	~BoxCollision();
	void AddCara(QuadFace lv);
	QuadFace GetCara(int index);
	float GetRadio();
	int GetNumCaras();
	int GetNumAristas();
	PuntoVector3D* GetArista(int i, tLista<PuntoVector3D>* lista);
private:
	GLfloat radio;//Para una primera aproximacion
	tLista<BoxCollision::QuadFace>* lCaras; //lista de caras del objeto
};
#endif
