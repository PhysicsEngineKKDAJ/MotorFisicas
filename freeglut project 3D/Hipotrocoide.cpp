
#include "Hipotrocoide.h"
#include <iostream>

Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c)
{
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;

	modo = false;
	radio = 0.5;

	//-------------Se crean los arrays de vértices, normales y caras----------------
	numeroVertices = numeroNormales = numeroCaras = nP * nQ;
	vertice = new PuntoVector3D*[numeroVertices];
	normal = new PuntoVector3D*[numeroNormales];
	cara = new Cara*[numeroCaras];
	//-------------------------------------------------------------

	int indVertices = 0;

	//------------------Crear perfil------------------------------
	perfil = new PuntoVector3D*[nP];
	GLfloat angTotal = 2 * 3.14 / nP;
	for (GLfloat ang = 0; ang <= 2 * 3.14; ang += angTotal){
		perfil[indVertices] = new PuntoVector3D(radio * cos(ang), radio * sin(ang), 0, 1);
		//std::cout << perfil[indVertices]->getX() << " " << perfil[indVertices]->getY() << "  " << perfil[indVertices]->getZ() << '\n';
		indVertices++;
	}
	//-------------------------------------------------------------

	indVertices = 0;

	GLfloat t = 0.0f; // angulo que rota en cada iteracion de la curva

	//-------------CREAR VERTICES INICIALES. SE APLICARÁ LA MATRIZ----------------
	cargaMatriz(t);

	creaPerfil(indVertices);
	//-------------------------------------------------------------

	GLfloat tAux = 8.0f* 3.14f / nQ ;
	int indCara = 0;
	//------------------------------REPETIR nQ veces----------------
	for (int i = 0; i < nQ; i++)
	{
		//AUMENTAR T
		t += tAux;
		//CALCULAR M(T)
		cargaMatriz(t);
		//CREAR VERTICES

		if (i != nQ-1)
			creaPerfil(indVertices);

		//UNIR CARAS
		creaRodaja(i, indCara);
	}
	//-------------------------------------------------------------
}

Hipotrocoide::~Hipotrocoide() {
	delete perfil;
}

//HAY QUE HACERLO EN FUNCION DE M
void Hipotrocoide::creaPerfil(int & indice) {
	
	for (int i = 0; i < nP; i++){
		GLfloat x = matriz[0] * perfil[i]->getX() + matriz[4] * perfil[i]->getY() + matriz[8] * perfil[i]->getZ() + matriz[12];
		GLfloat y = matriz[1] * perfil[i]->getX() + matriz[5] * perfil[i]->getY() + matriz[9] * perfil[i]->getZ() + matriz[13];
		GLfloat z = matriz[2] * perfil[i]->getX() + matriz[6] * perfil[i]->getY() + matriz[10] * perfil[i]->getZ() + matriz[14];

		vertice[indice] = new PuntoVector3D(x, y, z, 1);
		//std::cout << vertice[indice]->getX() << " " << vertice[indice]->getY() << "  " << vertice[indice]->getZ() << '\n';
		indice++;
	}
}

void Hipotrocoide::cargaMatriz(GLfloat t) {
	// Oscura M(t) = N(t), B(t), T(t), C(t);
	PuntoVector3D* m_N = N(t);
	PuntoVector3D* m_B = B(t);
	PuntoVector3D* m_T = T(t);
	PuntoVector3D* m_C = C(t);

	// Iluminada M(t) = B(t), N(t), T(t), C(t);

	matriz[0] = m_B->getX();	matriz[1] = m_B->getY();	matriz[2] = m_B->getZ();	matriz[3] = 0;

	matriz[4] = m_N->getX();	matriz[5] = m_N->getY();	matriz[6] = m_N->getZ();	matriz[7] = 0;

	matriz[8] = m_T->getX();	matriz[9] = m_T->getY();	matriz[10] = m_T->getZ();	matriz[11] = 0;

	matriz[12] = m_C->getX();	matriz[13] = m_C->getY();	matriz[14] = m_C->getZ();	matriz[15] = 1;
}


void Hipotrocoide::creaRodaja(int i, int &indCara) {
	for (int j = i * nP; j<(i * nP + nP); j++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		VerticeNormal** vn = new VerticeNormal*[4];
		vn[0] = new VerticeNormal(j, indCara);
		vn[1] = new VerticeNormal((j + nP) % (nP * nQ), indCara);
		vn[2] = new VerticeNormal(((j + nP + 1) % nP + (i + 1) * nP) % (nP * nQ), indCara);
		vn[3] = new VerticeNormal((j + 1) % nP + i * nP, indCara);

		cara[indCara] = new Cara(4, vn);

		// Normales
		PuntoVector3D* v = CalculoVectorNormalPorNewell(cara[indCara]); //Newell
		normal[indCara] = v;

		//cout << (i % numVertices) + 2 << "   " << ((i + 1) % numVertices) + 2 << endl;
		indCara++;
	} //for

}


// Ecuacion de los puntos de la curva
PuntoVector3D* Hipotrocoide::C(GLfloat t) {
	return new PuntoVector3D((a - b)*cos(t) + c*cos(t*((a - b) / b)), 0, (a - b)*sin(t) - c*sin(t*((a - b) / b)), 1);
}

// Primera derivada de la curva
PuntoVector3D* Hipotrocoide::Cd(GLfloat t) {
	return new PuntoVector3D(-1 * (a - b)*sin(t) + (-c*sin(t*((a - b) / b)) * ((a - b) / b)),
		0, (a - b)*cos(t) - (c*cos(t*((a - b) / b)) * ((a - b) / b)), 0);
}

// Segunda derivada de la curva
PuntoVector3D* Hipotrocoide::Cd2(GLfloat t) {
	return new PuntoVector3D(-1 * (a - b)*cos(t) + (-c*cos(t*((a - b) / b))*((a - b) / b) * ((a - b) / b)), 0,
		-1 * (a - b)*sin(t) + (c*sin(t*((a - b) / b))*((a - b) / b)*((a - b) / b)), 0);
}

// El vector T(t) es la normalización de C’(t)
PuntoVector3D* Hipotrocoide::T(GLfloat t) {
	PuntoVector3D* T = Cd(t);
	T->normalizar();
	return T;
}

// El vector binormal B(t) es la normalización de C’(t)×C’’(t)
PuntoVector3D* Hipotrocoide::B(GLfloat t) {

	PuntoVector3D* curvaDerivada = Cd(t);
	PuntoVector3D* curvaDerivada2 = Cd2(t);

	PuntoVector3D* B = curvaDerivada->productoVectorial(curvaDerivada2);

	B->normalizar();
	return B;
}

// El vector N(t) es B(t)×T(t). Ya está normalizado
PuntoVector3D* Hipotrocoide::N(GLfloat t) {
	PuntoVector3D* Base = B(t);
	PuntoVector3D* vectorT = T(t);

	return Base->productoVectorial(vectorT);
}

void Hipotrocoide::dibuja() {
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


