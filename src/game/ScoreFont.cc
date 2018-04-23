#include"game/ScoreFont.h"

ScoreFont::ScoreFont() :
	Font()
{

}

ScoreFont::~ScoreFont()
{

}

const char* ScoreFont::PathToFont()
{
	return mPath.c_str();
}

int ScoreFont::FontWidth()
{
	return mWidth;
}

int ScoreFont::FontHeight()
{
	return mHeight;
}

void ScoreFont::PathToFont(const char* path)
{
	mPath = path;
}

void ScoreFont::PathToFont(const std::string& path)
{
	mPath = path;
}

void ScoreFont::FontWidth(const int& width)
{
	mWidth = width;
}

void ScoreFont::FontHeight(const int& height)
{
	mHeight = height;
}


