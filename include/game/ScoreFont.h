#ifndef SCORE_FONT_HEADER_INCLUDED
#define SCORE_FONT_HEADER_INCLUDED

#include"engine/font/Font.h"

class ScoreFont :
	public Font
{
public:
	ScoreFont();
	~ScoreFont();
	const char* PathToFont();
	int FontWidth();
	int FontHeight();
	void PathToFont(const char*);
	void PathToFont(const std::string&);
	void FontWidth(const int&);
	void FontHeight(const int&);
protected:
	std::string mPath;
	int mWidth;
	int mHeight;
};

#endif