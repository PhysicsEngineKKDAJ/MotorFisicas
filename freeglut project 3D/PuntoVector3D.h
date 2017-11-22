#ifndef _PuntoVector3D_H_
#define _PuntoVector3D_H_

//#include <math.h>
#include <GL/freeglut.h>

class PuntoVector3D {
	private:
		GLfloat x, y, z;
        int pv;
    public:
        PuntoVector3D(GLfloat x, GLfloat y, GLfloat z, int pv);
        ~PuntoVector3D();
        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
        bool esPunto();
        bool esVector();
        void escalar(GLfloat factor);
        void normalizar();
        void sumar(PuntoVector3D* pv);
        PuntoVector3D* clonar();
        GLfloat productoEscalar(PuntoVector3D* vector);
        PuntoVector3D* productoVectorial(PuntoVector3D* vector);

		// SOBRECARGA DE OPERADORES
		/**********************************************/
		PuntoVector3D operator +(PuntoVector3D &PV3D) {
			int PoV;
			if (this->esPunto()) PoV = 1;
			else PoV = 0;
			return{ this->getX() + PV3D.getX(), this->getY() + PV3D.getY(),
				this->getZ() + PV3D.getZ(), PoV };
		}

		PuntoVector3D operator += (PuntoVector3D &PV3D) {
			return operator+(PV3D);
		}

};
#endif

