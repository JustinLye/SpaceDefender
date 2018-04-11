#ifndef TRIANGLE_HEADER_INCLUDED
#define TRIANGLE_HEADER_INCLUDED

#include"engine/shapes/Shape.h"

class Triangle :
	public Shape
{
public:
	Triangle();
	virtual ~Triangle();
protected:
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
	void FillVertices(GLfloat*);
	void FillIndices(GLuint*);

};

#endif