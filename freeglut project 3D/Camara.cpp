#include "Camara.h"


/*
//-------------------------------------------------------------------------

//Cambia la posición de la cámara a 2D
void Camara::setEZ() {
	eye = new PuntoVector3D(0, 0, 500, 1);
	look = new PuntoVector3D(0, 0, 0, 1);
	up = new PuntoVector3D(0, 1, 0, 1);

	setPos();
}

//-------------------------------------------------------------------------

//Cambia la posición de la cámara a 3D
void Camara::set3D() {
	eye = new PuntoVector3D(500, 500, 500, 1);
	look = new PuntoVector3D(0, 10, 0, 1);
	up = new PuntoVector3D (0, 1, 0,1);

	setPos();
}
*/

//-------------------------------------------------------------------------

void Camara::setPos(PuntoVector3D *ay, PuntoVector3D* al, PuntoVector3D* ap){
	eye = ay;
	look = al;
	up = ap;
	setPos();
}

//-------------------------------------------------------------------------

void Camara::setPos() {
	calcularNUV();
	setModelViewMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX() , eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());  // eye, look, up
}

//-------------------------------------------------------------------------

void Camara::setVV(GLdouble aw, GLdouble ah) {

	GLdouble RatioViewPort = (float)aw / (float)ah;

	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}

	setVV();

}

//-------------------------------------------------------------------------

void Camara::setVV() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(xLeft, xRight, yBot, yTop, nearVal, farVal);
	//glOrtho(xLeft, xRight, yBot, yTop, nearVal, farVal);
}

//-------------------------------------------------------------------------

void Camara::setEye(GLfloat x, GLfloat z){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eye = new PuntoVector3D(x, eye->getY(), z, 1);
	look = new PuntoVector3D(x, 0, z, 1);

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());  // eye, look, up

	//look = new PuntoVector3D(x, y-100, z, 1);
	//up = new PuntoVector3D()
}

void Camara::giraX(GLfloat ang){

	GLfloat dist = sqrt(eye->getY()*eye->getY() + eye->getZ()*eye->getZ());//Distancia del eje a la cámara
	GLfloat t = atan2(eye->getZ(), eye->getY()); //Angulo

	GLfloat cosA = cos(ang * 3.14 / 180 + t);
	GLfloat senA = sin(ang * 3.14 / 180 + t);

	eye = new PuntoVector3D(eye->getX(), dist*cosA, dist*senA, 1);

	setPos(eye, look, up);
}



void Camara::roll(GLfloat ang)
{
	GLfloat cosA = cos(ang * 3.14 / 180);
	GLfloat senA = sin(ang * 3.14 / 180);

	PuntoVector3D* uAux = u->clonar();

	u = new PuntoVector3D(cosA*uAux->getX() + senA*v->getX(),
		cosA*uAux->getY() + senA*v->getY(),
		cosA*uAux->getZ() + senA*v->getZ(),
		0);
	v = new PuntoVector3D(-senA*uAux->getX() + cosA*v->getX(),
		-senA*uAux->getY() + cosA*v->getY(),
		-senA*uAux->getZ() + cosA*v->getZ(),
		0);

	setModelViewMatrix();
}

void Camara::setModelViewMatrix()
{
	GLfloat m[16];
	m[0] = u->getX(); 	m[4] = u->getY();  m[8] = u->getZ();   m[12] = -eye->productoEscalar(u);
	m[1] = v->getX();  	m[5] = v->getY();  m[9] = v->getZ();   m[13] = -eye->productoEscalar(v);
	m[2] = n->getX();   m[6] = n->getY();  m[10] = n->getZ();  m[14] = -eye->productoEscalar(n);
	m[3] = 0;  	        m[7] = 0;          m[11] = 0; 	       m[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);//Carga matriz resultante como la nueva matriz de vista
}

void Camara::calcularNUV(){

	//n = (eye - look).normalizar
	n = new PuntoVector3D(eye->getX() - look->getX(), eye->getY() - look->getY(), eye->getZ() - look->getZ(), 0);
	n->normalizar();

	//u = (up x n).normalizar
	u = up->productoVectorial(n);
	u->normalizar();

	//v = n x u
	v = n->productoVectorial(u);
}
