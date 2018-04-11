#ifndef	SHAPE_HEADER_INCLUDED
#define SHAPE_HEADER_INCLUDED

#include<memory>
#include<glm/glm.hpp>
#include<glad/glad.h>

#include"engine/util/Constants.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw();
	unsigned int GetVAO();
	
protected:
	virtual unsigned int VertCount() = 0;
	virtual unsigned int IndexCount() = 0;
	virtual GLenum PrimType() = 0;
	virtual void FillVertices(GLfloat*) = 0;
	virtual void FillIndices(GLuint*) = 0;

	virtual void Init();
	virtual void Buffer();
	virtual void Destroy();
	
	GLuint mVaoId;
	GLuint mVerticesVboId;
	GLuint mIndicesVboId;
};

#endif
