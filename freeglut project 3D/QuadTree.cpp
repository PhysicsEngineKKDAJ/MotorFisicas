#include "QuadTree.h"


QuadTree::QuadTree()
{
}

void QuadTree::initialize(float x, float z, float s, Objeto3D** arboles,int const& numH)
{
	header = new QuadtreeNode(x, z, s,arboles,numH);
	header->build();
}

void QuadTree::drawTrees(float x1, float z1,float x3, float z3)
{
	header->drawTrees(x1, z1,x3, z3);
}
QuadTree::~QuadTree()
{
	delete header;
}
