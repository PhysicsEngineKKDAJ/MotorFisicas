#include "CuboRevolucion.h"
#include <iostream>

using namespace std;

CuboRevolucion::CuboRevolucion(GLfloat l, Color c) : arista(l)
{
	numeroVertices = 8;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = 6;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = 6;
	cara = new Cara*[numeroCaras];
	color = c;
	//---------------1. Perfil-----------------------------
	int numVertPerf = 2;
	PuntoVector3D** perfil = new PuntoVector3D*[numVertPerf];

	// Vértices  
	perfil[0] = new PuntoVector3D(cos(0) * arista / 2 * sqrt(2), arista / 2, sin(0)*arista / 2 * sqrt(2), 1);
	perfil[1] = new PuntoVector3D(cos(0) * arista / 2 * sqrt(2), -arista / 2, sin(0)*arista / 2 * sqrt(2), 1);

	for (int i = 0; i < numVertPerf; i++)
		vertice[i] = perfil[i]->clonar();

	//---------------1. Perfil-----------------------------


	//----------------2. Construccion de 4 caras verticales por revolucion-------------------

	int numRevoluciones = 4;

	//Vertices
	for (int i = 1; i < numRevoluciones; i++)
	{
		float theta = i * 360 / (double)numRevoluciones ;
		float c = cos((theta * 2 * 3.14) / 360), s = sin((theta * 2 * 3.14) / 360);

		for (int j = 0; j < numVertPerf; j++)
		{
			int indice = i*numVertPerf + j;

			GLfloat x = c* perfil[j]->getX() + s*perfil[j]->getZ();
			GLfloat z = -s* perfil[j]->getX() + c*perfil[j]->getZ();

			vertice[indice] = new PuntoVector3D(x, perfil[j]->getY(), z, 1);
		}
	}

	//Caras
	int indiceCara = 0;
	for (int i = 0; i<numRevoluciones; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<numVertPerf - 1; j++) { //esquina inferior-izquierda de una cara
			// indiceCara = i*(m-1) + j;
			int indice = i*numVertPerf + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[3] = new VerticeNormal((indice + numVertPerf) % numeroVertices, indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + numVertPerf) % numeroVertices, indiceCara);
			vn[1] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PuntoVector3D* v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = v;
			indiceCara++;
		} //for
	} //for

	//----------------2. Construccion de 4 caras verticales por revolucion-------------------

	//----------------3. Construccion de las 2 caras horizontales----------------------------
	VerticeNormal** vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(0, indiceCara);
	vn[1] = new VerticeNormal(2, indiceCara);
	vn[2] = new VerticeNormal(4, indiceCara);
	vn[3] = new VerticeNormal(6, indiceCara);
	cara[indiceCara] = new Cara(4, vn);

	PuntoVector3D* v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = v;
	indiceCara++;

	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(1, indiceCara);
	vn[1] = new VerticeNormal(7, indiceCara);
	vn[2] = new VerticeNormal(5, indiceCara);
	vn[3] = new VerticeNormal(3, indiceCara);
	cara[indiceCara] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = v;
	indiceCara++;

	//----------------3. Construccion de las 2 caras horizontales----------------------------
}

CuboRevolucion::~CuboRevolucion() {}

