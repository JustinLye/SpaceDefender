#include"engine/font/ArialFontData.h"

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