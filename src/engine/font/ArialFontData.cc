#include"engine/font/ArialFontData.h"


namespace sd_app {
namespace engine {
namespace font {
namespace impl {
namespace arial_font_data {
ArialFontData::ArialFontData() :
	FontData(),
	mPath(EngineFontPath("arial.ttf"))
{
	Init();
}

ArialFontData::~ArialFontData()
{

}

const char* ArialFontData::PathToFont()
{
	return mPath.c_str();
}

int ArialFontData::Width()
{
	return 0;
}

int ArialFontData::Height()
{
	return 48;
}
} // namespace arial_font_data
} // namespace impl
} // namespace font
} // namespace engine
} // namespace sd_app