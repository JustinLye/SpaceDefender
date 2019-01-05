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


void Text::XBearing(float x)
{
	mXBearing = x;
}

void Text::YBearing(float y)
{
	mYBearing = y;
}

void Text::Scale(float scale)
{
	mScale = scale;
}

void Text::Message(const std::string& message)
{
	mMessage = message;
}

void Text::Color(const glm::vec4& color)
{
	mFont->Color(color);
}

float Text::XBearing() const
{
	return mXBearing;
}

float Text::YBearing() const
{
	return mYBearing;
}

float Text::Scale() const
{
	return mScale;
}

const std::string& Text::Message() const
{
	return mMessage;
}

const glm::vec4& Text::Color() const
{
	return mFont->Color();
}