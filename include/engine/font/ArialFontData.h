#ifndef ARIAL_FONT_DATA_HEADER_INCLUDED
#define ARIAL_FONT_DATA_HEADER_INCLUDED

#include"engine/util/Paths.h"
#include"engine/font/FontData.h"

namespace sd_app {
namespace engine {
namespace font {
namespace impl {
namespace arial_font_data {

/** @addtogroup EngineFonts */
/*@{*/
class ArialFontData :
	public FontData
{
public:
	ArialFontData();
	~ArialFontData();
	const char* PathToFont();
	int Width();
	int Height();
protected:
	std::string mPath;
};
/*@}*/
#endif

} // namespace arial_font_data
} // namespace impl
using ArialFontData = impl::arial_font_data::ArialFontData;
} // namespace font
} // namespace engine
} // namespace sd_app