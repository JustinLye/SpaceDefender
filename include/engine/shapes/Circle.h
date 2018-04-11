#ifndef CIRCLE_HEADER_INCLUDED
#define CIRCLE_HEADER_INCLUDED

#include"engine/shapes/Shape.h"

class Circle :
	public Shape
{
public:
	Circle();
	virtual ~Circle();

protected:
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
	void FillVertices(GLfloat*);
	void FillIndices(GLuint*);

};



#endif