#ifndef TEXT_HEADER_INCLUDED
#define TEXT_HEADER_INCLUDED

#include"engine/objects/UIObject.h"
#include"engine/font/Font.h"

class Text :
	public UIObject
{
public:
	Text();
	virtual ~Text();
	void Render();

	void FontPtr(Font*);
	void XBearing(const float&);
	void YBearing(const float&);
	void Scale(const float&);
	void Message(const std::string&);

	const Font* FontPtr() const;
	const float& XBearing() const;
	const float& YBearing() const;
	const float& Scale() const;
	const std::string& Message() const;
	
protected:
	Font* mFont;
	float mXBearing;
	float mYBearing;
	float mScale;
	std::string mMessage;

};

#endif