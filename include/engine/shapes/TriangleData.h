#ifndef TRIANGLE_DATA_HEADER_INCLUDED
#define TRIANGLE_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

/** @addtogroup EngineShapes */
/*@{*/

class TriangleData :
	public ShapeData
{
public:
	TriangleData();
	virtual ~TriangleData();
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();

protected:
	void InitializeData();

};
/*@}*/
#endif