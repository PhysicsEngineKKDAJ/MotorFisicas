#include "Cono.h"
#include <iostream>

using namespace std;

Cono::Cono(int numVertices, int radio, int altura) {
	numeroVertices = numVertices + 2;
	vertice = new PuntoVector3D*[numeroVertices];
	numeroNormales = numVertices * 2;
	normal = new PuntoVector3D*[numeroNormales];
	numeroCaras = numVertices * 2;
	cara = new Cara*[numeroCaras];
	modo = false;
	m_altura = altura;
	m_radio = radio;

	// Vértices  
	vertice[0] = new PuntoVector3D(0.0f, 0.0f, 0.0f, 1);
	vertice[1] = new PuntoVector3D(0.0f, m_altura, 0.0f, 1);

	float angTotal = 2 * 3.14 / numVertices;
	float ang = 0;
	for (int i = 2; i < numeroVertices; i++, ang += angTotal)
		vertice[i] = new PuntoVector3D(m_radio * cos(ang), 0, m_radio*sin(ang), 1);
	
	int indiceCara = 0;
	for (int i = 0; i<numVertices; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<2 ; j++) { //esquina inferior-izquierda de una cara
			VerticeNormal** vn = new VerticeNormal*[3];
			vn[0] = new VerticeNormal(j, indiceCara);
			vn[1] = new VerticeNormal(((i + 1) % numVertices) + 2, indiceCara);
			vn[2] = new VerticeNormal((i % numVertices) + 2, indiceCara);
			cara[indiceCara] = new Cara(3, vn);

			// Normales
			PuntoVector3D* v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = v;

			//cout << (i % numVertices) + 2 << "   " << ((i + 1) % numVertices) + 2 << endl;
			indiceCara++;
		} //for
	} //for
}

Cono::~Cono() {}

void Cono::dibuja() {
	for (int i = 0; i<numeroCaras; i++) 
	{
		if (!modo) glBegin(GL_POLYGON);
		else glBegin(GL_LINE_LOOP);
		for (int j = 0; j<cara[i]->getNumeroVertices(); j++) 
		{
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}


