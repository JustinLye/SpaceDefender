#include"engine/font/Font.h"

bool Font::InitOpenGL = true;

Font::Font() :
	mTextures(nullptr),
	mVaoId(0),
	mVboId(0)
{

}

Font::~Font()
{
	Destroy();
}

void Font::Destroy()
{
	if (mTextures != nullptr)
	{
		glDeleteTextures(128, mTextures);
		delete[] mTextures;
		mTextures = nullptr;
	}
}

void Font::Draw(const std::string& text, const GLfloat& x, const GLfloat& y, const GLfloat& scale)
{
	GLint prev_poly_mode;
	glGetIntegerv(GL_POLYGON_MODE, &prev_poly_mode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVaoId);

	float temp_x = x;
	for (auto c : text)
	{
		Character ch = this->operator[](c);
		GLfloat xpos = temp_x + ch.mBearing.x * scale;
		GLfloat ypos = y - (ch.mSize.y - ch.mBearing.y) * scale;
		GLfloat w = ch.mSize.x * scale;
		GLfloat h = ch.mSize.y * scale;
		GLfloat verts[6][4] =
		{
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.mTextureId);
		glBindBuffer(GL_ARRAY_BUFFER, mVboId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		temp_x += (ch.mAdvance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, prev_poly_mode);
}

void Font::Init()
{
	if (InitOpenGL)
	{
		InitOpenGL = false;
		//		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	FT_Library ft;
	mTextures = new GLuint[128];
	glGenTextures(128, mTextures);
	if (FT_Init_FreeType(&ft))
	{
		throw std::runtime_error("Failed to init FreeType lib");
	}
	FT_Face face;
	if (FT_New_Face(ft, PathToFont(), 0, &face))
	{
		throw std::runtime_error("Failed to load font.");
	}
	FT_Set_Pixel_Sizes(face, FontWidth(), FontHeight());
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
#ifdef FONT_DEBUG
			std::cout << "Failed to load Glyph " << c << '\n';
			continue;
#else
			Destroy();
			throw std::runtime_error("Failed to load Glyph");
#endif
		}
		glBindTexture(GL_TEXTURE_2D, mTextures[c]);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		mCharacterMap.insert(
		{
			(const GLchar)c,
			{
				mTextures[c],
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x
			}
		});
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	Buffer();
}

void Font::Buffer()
{
	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVboId);
	glBindVertexArray(mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

const Character& Font::operator[](const GLchar& character) const
{
	auto result = mCharacterMap.find(character);
	if (result == mCharacterMap.end())
	{
		throw std::runtime_error("Character not found.");
	}
	return result->second;
}