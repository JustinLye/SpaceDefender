#ifndef	SHAPE_HEADER_INCLUDED
#define SHAPE_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<memory>
#include"engine/util/Constants.h"
#include"engine/shapes/ShapeData.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw();
	unsigned int GetVAO();
	const unsigned int& GetVAO() const;
	virtual void ShapeDataPtr(ShapeData*);
	virtual void Buffer(ShapeData* = nullptr);
	bool operator<(const Shape&) const;
	bool operator==(const Shape&) const;

protected:
	ShapeData* mShapeData;
	GLuint mVaoId;
	GLuint mVerticesVboId;
	GLuint mIndicesVboId;
	virtual void Destroy();
};

#endif
