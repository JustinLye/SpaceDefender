#ifndef	SHAPE_HEADER_INCLUDED
#define SHAPE_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<memory>
#include"engine/util/Constants.h"
#include"engine/shapes/ShapeData.h"
#include"engine/objects/DrawableObject.h"


/** @addtogroup EngineShapes */
/*@{*/
class Shape :
	public DrawableObject
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw();
	virtual void ShapeDataPtr(ShapeData*);
	virtual void Buffer(ShapeData* = nullptr);

protected:
	ShapeData* mShapeData;
	GLuint mVerticesVboId;
	GLuint mIndicesVboId;
	virtual void Destroy();
};
/*@}*/
#endif