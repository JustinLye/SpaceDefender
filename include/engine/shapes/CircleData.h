#ifndef CIRCLE_DATA_HEADER_INCLUDED
#define CIRCLE_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

/** @addtogroup EngineShapes */
/*@{*/
class CircleData :
	public ShapeData
{
public:
	CircleData();
	virtual ~CircleData();
	virtual unsigned int VertCount();
	virtual unsigned int IndexCount();
	virtual GLenum PrimType();
protected:
	virtual void InitializeData();

};
/*@}*/
#endif