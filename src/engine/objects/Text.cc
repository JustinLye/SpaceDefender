#include"engine/objects/Text.h"

Text::Text() :
	UIObject(),
	mFont(nullptr),
	mXBearing(0.0f),
	mYBearing(0.0f),
	mScale(0.0f),
	mMessage("")
{

}

Text::~Text()
{

}

void Text::Render()
{
	mFont->Render(mMessage, mXBearing, mYBearing, mScale);
}

void Text::FontPtr(Font* font)
{
	mFont = font;
}


void Text::XBearing(const float& x)
{
	mXBearing = x;
}

void Text::YBearing(const float& y)
{
	mYBearing = y;
}

void Text::Scale(const float& scale)
{
	mScale = scale;
}

void Text::Message(const std::string& message)
{
	mMessage = message;
}

const float& Text::XBearing() const
{
	return mXBearing;
}

const float& Text::YBearing() const
{
	return mYBearing;
}

const float& Text::Scale() const
{
	return mScale;
}

const std::string& Text::Message() const
{
	return mMessage;
}

