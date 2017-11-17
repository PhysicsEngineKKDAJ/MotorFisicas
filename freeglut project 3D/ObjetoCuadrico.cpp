#include "ObjetoCuadrico.h"


ObjetoCuadrico::ObjetoCuadrico(Color c) 
{
	//Crea un objeto cuadrico
	objCua = gluNewQuadric();
	//Estilo de dibujo: GLU_POINT / GLU_LINE / GLU_FILL
	gluQuadricDrawStyle(objCua, GLU_FILL);

	color = c;
}


ObjetoCuadrico::~ObjetoCuadrico()
{
	gluDeleteQuadric(objCua);
}

void ObjetoCuadrico::dibuja()
{
	glColor3d(color.r, color.g, color.b);
	glMatrixMode(GL_MODELVIEW);
}

