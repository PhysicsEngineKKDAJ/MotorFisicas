#include "QuadtreeNode.h"

//Método que comprueba la colisión entre la base del tronco y el nodo
bool checkDiscRectangleIntersection(GLdouble SWCornerX, GLdouble SWCornerZ,
	GLdouble size,
	GLdouble circuloX,
	GLdouble circuloZ,
	GLdouble radio)
{

	GLdouble circXDist, circZDist;
	circXDist = abs(circuloX - (SWCornerX+ size/2) );
	circZDist = abs(circuloZ - (SWCornerZ + size / 2));

	if (circXDist > (size / 2 + radio)) { return false; }
	if (circZDist > (size / 2 + radio)) { return false; }

	if (circXDist <= (size / 2)) { return true; }
	if (circZDist <= (size / 2)) { return true; }

	GLdouble distCornerToSquare;
	distCornerToSquare = (circXDist - size / 2) * (circXDist - size / 2) +
		(circZDist - size / 2) * (circZDist - size / 2);

	return (distCornerToSquare <= (radio * radio));

}



QuadtreeNode::QuadtreeNode(float x, float z, float s, Objeto3D** arboles,int const& nHijos)
{
	SWCornerX = x;
	SWCornerZ = z;
	size = s;
	arrayTrees = arboles;
	numHijos = nHijos;
	SWChild = NWChild = NEChild = SEChild = nullptr;//Inicializamos los hijos

}


QuadtreeNode::~QuadtreeNode()
{
	delete SWChild;
	delete NWChild;
	delete NEChild;
	delete SEChild;
}

void QuadtreeNode::build()
{
	if (this->numberTreesIntersected() <= umbral)
		this->addIntersectingTreesToList();//Añado todos los arboles, porque no hace falta hacer una división. El num arboles colisionados está dentro del umbral.
	else {
		//Creamos nodos hijos
		SWChild = new QuadtreeNode(SWCornerX, SWCornerZ, size / 2.0, arrayTrees, numHijos);
		NWChild = new QuadtreeNode(SWCornerX, SWCornerZ + size / 2.0,
			size / 2.0, arrayTrees, numHijos);
		NEChild = new QuadtreeNode(SWCornerX + size / 2.0,
			SWCornerZ + size / 2.0, size / 2.0, arrayTrees, numHijos);
		SEChild = new QuadtreeNode(SWCornerX + size / 2.0, SWCornerZ,
			size / 2.0, arrayTrees, numHijos);
		SWChild->build(); NWChild->build();
		NEChild->build(); SEChild->build();
	}
}

int QuadtreeNode::numberTreesIntersected(){
	int numVal = 0;
	for (int i = 0; i < numHijos; i++)
	{
		if (arrayTrees[i]->esVisible())
		{
			//Obtengo la matriz de transformación
			GLfloat* mArbol = arrayTrees[i]->getmT()->getM();
			//Compruebo si hay colision
			if (checkDiscRectangleIntersection(
				SWCornerX, SWCornerZ,
				size,
				mArbol[12], //X de la base del arbol
				mArbol[14], //Z de la base del arbol
				4))
				numVal++;
		}
	}
	return numVal;
}

void QuadtreeNode::addIntersectingTreesToList(){
	for (int i = 0; i < numHijos; i++)
	{
		if (arrayTrees[i]->esVisible())
		{
			//Añado los arboles intersecados a la lista
			GLfloat* mArbol = arrayTrees[i]->getmT()->getM();
			if (checkDiscRectangleIntersection(
				SWCornerX, SWCornerZ,
				size,
				mArbol[12],
				mArbol[14],
				4))
				treeList.push_back((arrayTrees[i]));
		}
	}
}

bool checkQuadrilateralsIntersection(float v1x1, float v1z1,
	float v1x3, float  v1z3,
	float v2x1, float v2z1,
	float v2x3, float v2z3)
{
	
	//Lados del rectángulo
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	float anchoA, altoA;

	anchoA = abs(v1x1) + abs(v1x3);
	altoA = abs(v1z3) + abs(v1z1);

	leftA = v1x1;
	rightA = v1x1 + anchoA;
	topA = v1z3;
	bottomA = v1z3 - altoA;


	float anchoB, altoB;

	anchoB = abs(v2x1) + abs(v2x3);
	altoB = abs(v2z3) + abs(v2z1);

	leftB= v2x1;
	rightB = v2x1 + anchoB;
	topB = v2z3;
	bottomB = v2z3 - altoB;
	

	return !(bottomA >= topB || topA <= bottomB || rightA <= leftB || (leftA >= rightB));

}

void QuadtreeNode::drawTrees(float x1, float z1, // dibuja los árboles de la lista de árboles de aquellos nodos hoja que intersecan con el frustum
	float x3, float z3) {
	//If the square does not intersect the frustum do nothing.
	if (checkQuadrilateralsIntersection(x1, z1, x3, z3, 
		SWCornerX, SWCornerZ,
		SWCornerX + size, SWCornerZ + size)) {
		//Caso en el que no se ha dividido el nodo en hijos. Si el nodo no se ha dividido, pinto todos los arboles
		//del nodo
		if (SWChild == nullptr) { //Square is leaf.
			std::list<Objeto3D*>::const_iterator it = treeList.cbegin();

			//Pinto todos los arboles
			while (it != treeList.cend())
			{
				if ((*it)->esVisible())
					(*it)->dibuja();
				it++;
			}
		}
		//Caso en el que dividimos de forma recursiva en nodos
		else {
			SWChild->drawTrees(x1, z1, x3, z3);
			NWChild->drawTrees(x1, z1,x3, z3);
			NEChild->drawTrees(x1, z1,x3, z3);
			SEChild->drawTrees(x1, z1, x3, z3);
		}
	}
}