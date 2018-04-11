#ifndef LINE_SEGMENT_HEADER_INCLUDED
#define LINE_SEGMENT_HEADER_INCLUDED

#include"engine/shapes/Shape.h"

class LineSegment :
	public Shape
{
public:
	LineSegment();
	virtual ~LineSegment();
protected:
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
	void FillVertices(GLfloat*);
	void FillIndices(GLuint*);

};

#endif