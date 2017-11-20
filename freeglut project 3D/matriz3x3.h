#ifndef _H_matriz3x3_H_
#define _H_matriz3x3_H_

#include "PuntoVector3D.h"
class matrix3x3
{
public:

	matrix3x3(void);
	matrix3x3(GLfloat(*pElements)[3]);

	// @todo this isn't the safest ctor to have
	enum mode { SkewSymmetric, Zero };
	inline matrix3x3(mode MustBeZero);
	inline matrix3x3(PuntoVector3D const &CrossVector, mode MustBeSkewSymmetric);

	inline matrix3x3 &operator+=(matrix3x3 const &A);

	inline GLfloat &operator()(int unsigned Row, int unsigned Column);
	inline GLfloat const &operator()(int unsigned Row, int unsigned Column) const;

	inline GLfloat GetElement(int Row, int Column) const;
	inline matrix3x3 &SetElement(int Row, int Column, GLfloat Value);

protected:

	enum do_not_initialize { DoNotInitialize };

	inline matrix3x3(do_not_initialize);

	GLfloat aElements[3][3];
};
#endif