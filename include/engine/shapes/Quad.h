#ifndef QUAD_HEADER_INCLUDED
#define QUAD_HEADER_INCLUDED

#include"engine/shapes/Shape.h"

class Quad :
	public Shape
{
public:
	Quad();
	virtual ~Quad();
protected:
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
	void FillVertices(GLfloat*);
	void FillIndices(GLuint*);
};

#endif