#include"engine/graphics/Texture.h"

Texture::Texture() :
	TexData(),
	DrawableObject(),
	mTexId(0),
	mVerticesVboId(0),
	mIndicesVboId(0)
{
	Init();
}

Texture::~Texture()
{

}

void Texture::Draw()
{
	glDrawElements(PrimType(), IndexCount(), GL_UNSIGNED_INT, 0);
}

void Texture::Buffer()
{
	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVerticesVboId);
	glGenBuffers(1, &mIndicesVboId);
	glBindVertexArray(mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, mVerticesVboId);
	glBufferData(GL_ARRAY_BUFFER, VertCount() * sizeof(TexVertexData), 0, GL_STATIC_DRAW);
	GLfloat* buffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillVertices(buffer);
#ifdef GRAPHICS_DEBUG
	GLfloat* temp = buffer;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << *temp << '\t';
			++temp;
		}
		std::cout << '\n';
	}
#endif
	glEnableVertexAttribArray(VERTEX_ATTRIB_POS);
#ifdef GRAPHICS_DEBUG
	DebugMessage(sizeof(TexVertexData));
	DebugMessage(5 * sizeof(GLfloat));
#endif
	glVertexAttribPointer(VERTEX_ATTRIB_POS, 3, GL_FLOAT, GL_FALSE, sizeof(TexVertexData), 0);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POS);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POS, 2, GL_FLOAT, GL_FALSE, sizeof(TexVertexData), (void*)(sizeof(glm::vec3)));
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesVboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount() * sizeof(GLuint), 0, GL_STATIC_DRAW);
	GLuint* index_buffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillIndices(index_buffer);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindVertexArray(0);

}

unsigned int Texture::VertCount()
{
	return 4;
}

unsigned int Texture::IndexCount()
{
	return 6;
}

GLenum Texture::PrimType()
{
	return GL_TRIANGLES;
}

void Texture::LoadFromFile(const std::string& path)
{
	if (mTexId != 0)
	{
		glDeleteTextures(1, &mTexId);
		mTexId = 0;
	}
	glGenTextures(1, &mTexId);
	glBindTexture(GL_TEXTURE_2D, mTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, c;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 0);
	if (!data)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + path);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

const unsigned int& Texture::TexId() const 
{
	return mTexId;
}

void Texture::InitializeData()
{
	mTexVertexData[0] = { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
	mTexVertexData[1] = { glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
	mTexVertexData[2] = { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	mTexVertexData[3] = { glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

	mIndices[0] = 0;
	mIndices[1] = 1;
	mIndices[2] = 3;
	mIndices[3] = 1;
	mIndices[4] = 2;
	mIndices[5] = 3;

	Buffer();
}

void Texture::CustomActivationSteps()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexId);
}

void Texture::CustomDeactivationSteps()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
