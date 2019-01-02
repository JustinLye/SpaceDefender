#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#ifndef RENDERABLE_OBJECT_HEADER_INCLUDED
#define RENDERABLE_OBJECT_HEADER_INCLUDED

#include"engine/util/ShaderProgram.h"
/** @addtogroup EngineObjects */
/*@{*/
class RenderableObject
{
public:
	RenderableObject();
	virtual ~RenderableObject();
	
	void Render(const float*);
	virtual int GetTotalVertices() = 0;
	virtual int GetTotalIndices() = 0;
	virtual GLenum GetPrimitiveType() = 0;
	virtual GLenum GetPolygonMode();
	virtual void FillVertexBuffer(GLfloat*) = 0;
	virtual void FillIndexBuffer(GLuint*) = 0;
	virtual std::string VertexShaderPath();
	virtual std::string FragmentShaderPath();

	virtual glm::vec4 Color() const;
	virtual void Color(const glm::vec4&);
	virtual void SetCustomUniforms();
	virtual void AddCustomAttribs();

	void Init();
	void Destroy();
protected:
	GLuint mVaoId;
	GLuint mVboVerticesId;
	GLuint mVboIndicesId;
	ShaderProgram mShader;
	GLenum mPrimitiveType;
	GLenum mPolygonMode;
	int mTotalVertices;
	int mTotalIndices;
	glm::vec4 mColor;
};

/*@}*/

#endif