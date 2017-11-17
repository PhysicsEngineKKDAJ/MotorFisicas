#include "Cubo.h"
#include <iostream>

using namespace std;

Cubo::Cubo(GLfloat l, Color c) : arista(l)
{
	numeroVertices = 8;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = 6;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = 6;
	cara = new Cara*[numeroCaras];
	color = c;



	//Vértices
	vertice[0] = new PuntoVector3D(arista / 2, -arista / 2, arista / 2, 1);
	vertice[1] = new PuntoVector3D(arista / 2, arista / 2, arista / 2, 1);
	vertice[2] = new PuntoVector3D(arista / 2, -arista / 2, -arista / 2, 1);
	vertice[3] = new PuntoVector3D(arista / 2, arista / 2, -arista / 2, 1);
	vertice[4] = new PuntoVector3D(-arista / 2, -arista / 2, -arista / 2, 1);
	vertice[5] = new PuntoVector3D(-arista / 2, arista / 2, -arista / 2, 1);
	vertice[6] = new PuntoVector3D(-arista / 2, -arista / 2, arista / 2, 1);
	vertice[7] = new PuntoVector3D(-arista / 2, arista / 2, arista / 2, 1);

	//CARAS Y NORMALES
	VerticeNormal** vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(1, 0);
	vn[1] = new VerticeNormal(0, 0);
	vn[2] = new VerticeNormal(2, 0);
	vn[3] = new VerticeNormal(3, 0);
	cara[0] = new Cara(4, vn);

	PuntoVector3D* v = CalculoVectorNormalPorNewell(cara[0]); //Newell
	normal[0] = v;

	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(3, 1);
	vn[1] = new VerticeNormal(2, 1);
	vn[2] = new VerticeNormal(4, 1);
	vn[3] = new VerticeNormal(5, 1);
	cara[1] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[1]); //Newell
	normal[1] = v;

	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(5, 2);
	vn[1] = new VerticeNormal(4, 2);
	vn[2] = new VerticeNormal(6, 2);
	vn[3] = new VerticeNormal(7, 2);
	cara[2] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[2]); //Newell
	normal[2] = v;

	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(7, 3);
	vn[1] = new VerticeNormal(6, 3);
	vn[2] = new VerticeNormal(0, 3);
	vn[3] = new VerticeNormal(1, 3);
	cara[3] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[3]); //Newell
	normal[3] = v;

	//Caras horizontales
	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(2, 4);
	vn[1] = new VerticeNormal(0, 4);
	vn[2] = new VerticeNormal(6, 4);
	vn[3] = new VerticeNormal(4, 4);
	cara[4] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[4]); //Newell
	normal[4] = v;

	vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(1, 5);
	vn[1] = new VerticeNormal(3, 5);
	vn[2] = new VerticeNormal(5, 5);
	vn[3] = new VerticeNormal(7, 5);
	cara[5] = new Cara(4, vn);

	v = CalculoVectorNormalPorNewell(cara[5]); //Newell
	normal[5] = v;

}

Cubo::~Cubo() {}

