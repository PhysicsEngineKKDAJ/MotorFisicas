#pragma once
#include "PuntoVector3D.h"
class Muro
{

	public:

		Muro();
		Muro(PuntoVector3D Normal, float d);	//Constructora
		Muro(const Muro& w);					//Constructor por copia

		~Muro();

		inline PuntoVector3D GetNormal(){ return Normal; };		//Get de la normal del muro
		inline float GetD(){ return d; };						

private:
	// define el muro con la ecuación del plano
	PuntoVector3D Normal;        // inward pointing (La normal)
	float d;                 // ax + by + cz + d = 0
	//Creo que el "d" es el 1 ó 0 que determina si es punto o vector.
	/*
	Para determinar un plano se necesitan un punto Po(xo,yo,zo) y un vector N⃗ (A,B,C) normal al plano. La ecuación del plano viene entonces dada por la relación:

	A(x - xo) + B(y - yo) + C(z - zo) = 0 ⇒ A.x + B.y + C.z + D = 0 (1)

	Donde D = -A.xo - B.yo - C.zo

	*/
};

