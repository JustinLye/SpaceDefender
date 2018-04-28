#ifndef ARIAL_FONT_DATA_HEADER_INCLUDED
#define ARIAL_FONT_DATA_HEADER_INCLUDED

#include"engine/util/Paths.h"
#include"engine/font/FontData.h"

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

#endif