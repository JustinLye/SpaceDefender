#include"engine/shapes/Shape.h"

Shape::Shape() :
	mShapeData(nullptr),
	mVaoId(0),
	mVerticesVboId(0),
	mIndicesVboId(0)
{

}

Shape::~Shape()
{
	try
	{
		Destroy();
	}
	catch (...)
	{

	}
}

void Shape::Draw()
{
#ifdef ENGINE_DEBUG
	assert(mShapeData != nullptr);
#endif
	glDrawElements(mShapeData->PrimType(), mShapeData->IndexCount(), GL_UNSIGNED_INT, 0);
}

unsigned int Shape::GetVAO()
{
	return mVaoId;
}

const unsigned int& Shape::GetVAO() const
{
	return mVaoId;
}

void Shape::ShapeDataPtr(ShapeData* shape_ptr)
{
	mShapeData = shape_ptr;
}

bool Shape::operator<(const Shape& other) const
{
	return mVaoId < other.GetVAO();
}

bool Shape::operator==(const Shape& other) const
{
	return mVaoId == other.GetVAO();
}

void Shape::Buffer(ShapeData* shape_data)
{
	
	if (mVerticesVboId != 0 || mIndicesVboId != 0 || mVaoId != 0)
	{
		Destroy();
	}
	if (shape_data != nullptr)
	{
		mShapeData = shape_data;
	}

#ifdef ENGINE_DEBUG	
	assert(mShapeData != nullptr);
#endif

	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVerticesVboId);
	glGenBuffers(1, &mIndicesVboId);

	glBindVertexArray(mVaoId);

	glBindBuffer(GL_ARRAY_BUFFER, mVerticesVboId);
	glBufferData(GL_ARRAY_BUFFER, mShapeData->VertCount() * sizeof(glm::vec3), 0, GL_STATIC_DRAW);
	GLfloat* buffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	mShapeData->FillVertices(buffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glEnableVertexAttribArray(Constants::Shaders::VERTEX_ATTRIB_POS);
	glVertexAttribPointer(Constants::Shaders::VERTEX_ATTRIB_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesVboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mShapeData->IndexCount() * sizeof(GLuint), 0, GL_STATIC_DRAW);
	GLuint* index_buffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	mShapeData->FillIndices(index_buffer);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
	glBindVertexArray(0);
}

void Shape::Destroy()
{
	glDeleteBuffers(1, &mVerticesVboId);
	glDeleteBuffers(1, &mIndicesVboId);
	glDeleteVertexArrays(1, &mVaoId);
	mVerticesVboId = 0;
	mIndicesVboId = 0;
	mVaoId = 0;
}




