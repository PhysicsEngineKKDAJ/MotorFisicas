#ifndef Quadtree_H_
#define Quadtree_H_
#include "QuadtreeNode.h"
#include "ObjetoCompuesto.h"


class QuadTree
{
public:
	QuadTree();
	~QuadTree();

	void drawTrees(float x1, float z1, // dibuja los asteroides de la lista de asteroides de aquellos nodos hoja que intersecan con el frustum
		float x3, float z3);

	//Puntero al array
	void initialize(float x, float z, float s, Objeto3D** arboles, int const& numH);//construye recursivamente el árbol

private:
	QuadtreeNode * header;
	
};

#endif