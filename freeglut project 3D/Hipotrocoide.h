#ifndef _H_Hipotrocoide_H_
#define _H_Hipotrocoide_H_
#include "Malla.h"
#include "PuntoVector3D.h"

class Hipotrocoide : public Malla
{
public:
	Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipotrocoide();

	virtual void dibuja();
	
	void setMode(bool mode){ modo = mode; };
	bool getMode(){ return modo; };

	PuntoVector3D* C(GLfloat t);//Se necesita para la pos del coche
	PuntoVector3D* Cd(GLfloat t);//Se necesita para el angulo del coche


private:
	GLfloat a, b, c; // Parametros de la curva
	GLfloat radio;
	int nP; // número de lados del polígono que aproxima el grosor de la curva
	int nQ; // número de de muestras que se toman en la curva
	GLfloat matriz[16]; // matriz para pasar el perfil a la curva
	PuntoVector3D** perfil; // polígono de nP lados
	bool modo;

	void creaPerfil(int & indice);
	void creaRodaja(int i, int &indCara);

	void cargaMatriz(GLfloat t);

	// metodos para rellenar la matriz m
	PuntoVector3D* Cd2(GLfloat t);
	PuntoVector3D* T(GLfloat t);
	PuntoVector3D* B(GLfloat t);
	PuntoVector3D* N(GLfloat t); 
};
#endif

