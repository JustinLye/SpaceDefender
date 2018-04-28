#include"engine/font/FontData.h"

FontData::FontData() :
	mTextures(nullptr)
{

}

FontData::~FontData()
{
	Destroy();
}

void FontData::Init()
{
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Alloc textures
	if (mTextures != nullptr)
	{
		Destroy();
	}
	mTextures = new GLuint[128];
	glGenTextures(128, mTextures);

	// Init ft lib
	FT_Library ft_lib;
	if (FT_Init_FreeType(&ft_lib))
	{
		throw std::runtime_error("Failed to init FreeType lib");
	}

	// Alloc new face
	FT_Face face;
	if (FT_New_Face(ft_lib, PathToFont(), 0, &face))
	{
		throw std::runtime_error(std::string("Failed to load font: ") + PathToFont() + std::string("."));
	}

	// Set pixle size
	FT_Set_Pixel_Sizes(face, Width(), Height());

	// Unsure no alignment issues
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load character map
	for (GLubyte c = 0; c < 128; ++c)
	{
		// Load character
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			Destroy();
			throw std::runtime_error(std::string("Failed to load glyph ") + boost::lexical_cast<std::string>(c));
		}

		// Create texture
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
		
		// Insert character into map
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

	// Dealloc
	FT_Done_Face(face);
	FT_Done_FreeType(ft_lib);
}

void FontData::Destroy()
{
	if (mTextures != nullptr)
	{
		glDeleteTextures(128, mTextures);
		delete[] mTextures;
		mTextures = nullptr;
	}
}

const Character& FontData::operator[](const GLchar& character) const
{
	auto result = mCharacterMap.find(character);
	if (result == mCharacterMap.end())
	{
		throw std::runtime_error("Character not found.");
	}
	return result->second;
}