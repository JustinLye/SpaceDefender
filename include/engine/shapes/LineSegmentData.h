#ifndef LINE_SEGMENT_DATA_HEADER_INCLUDED
#define LINE_SEGMENT_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

class LineSegmentData :
	public ShapeData
{
public:
	LineSegmentData();
	virtual ~LineSegmentData();
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
protected:
	void InitializeData();
};

#endif