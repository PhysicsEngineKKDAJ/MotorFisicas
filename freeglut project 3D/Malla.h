 
#ifndef Malla_H_
#define Malla_H_

#include "PuntoVector3D.h"
#include "Cara.h"
#include "Objeto3D.h"

class Malla : public Objeto3D {	 
    protected:
        int numeroVertices;
        PuntoVector3D** vertice;
        int numeroNormales;
        PuntoVector3D** normal;
        int numeroCaras;
        Cara** cara;

		PuntoVector3D * CalculoVectorNormalPorNewell(Cara* cara);
    public:
        Malla(int nV, int nN, int nC, PuntoVector3D** v, PuntoVector3D** n, Cara** c);
        Malla();
        virtual ~Malla();
        int getNumeroVertices();
        int getNumeroNormales();
        int getNumeroCaras();         
        virtual void dibuja();  
};
#endif
