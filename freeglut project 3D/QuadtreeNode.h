#ifndef QuadtreeNode_H_
#define QuadtreeNode_H_

#include <list>
#include "ObjetoCompuesto.h"

class QuadtreeNode
{
public:
	QuadtreeNode(float x, float z, float s, Objeto3D** arboles,int const& nHijos);
	~QuadtreeNode();

	void drawTrees(float x1, float z1, // dibuja los asteroides de la lista de asteroides de aquellos nodos hoja que intersecan con el frustum
		float x3, float z3); //dibuja recursivamente los asteroides contenidos en un nodo
	void build();//Construye recursivamente el nodo

private:
	GLdouble SWCornerX, SWCornerZ; //Coordenadas de la esquina inferior izquierda
	GLdouble size;//Tamaño del cuadrado
	int umbral = 20;
	int numHijos;


	Objeto3D** arrayTrees;
	std::list<Objeto3D*> treeList; //lista de arboles que intersecan con el nodo; solo para nodoshoja con 1 arbol, a lo más
	QuadtreeNode *SWChild, *NWChild, *NEChild, *SEChild; //punteros a los nodos hijo; no nulos solo para nodos internos

	int numberTreesIntersected();// recorre todos los asteroides y, por cada uno, averigua si interseca con el cuadrado asociado al nodo
	void addIntersectingTreesToList(); // construye una lista con todos los asteroides que intersecan con el nodo
};
#endif
