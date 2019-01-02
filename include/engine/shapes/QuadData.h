#ifndef QUAD_DATA_HEADER_INCLUDED
#define QUAD_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

/** @addtogroup EngineShapes */
/*@{*/

class QuadData :
	public ShapeData
{
public:
	QuadData();
	virtual ~QuadData();
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();
protected:
	virtual void InitializeData();
};

/*@}*/
#endif