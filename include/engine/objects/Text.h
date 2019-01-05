#ifndef TEXT_HEADER_INCLUDED
#define TEXT_HEADER_INCLUDED

#include"engine/objects/UIObject.h"
#include"engine/font/Font.h"

/** @addtogroup EngineObjects */
/*@{*/

class Text :
	public UIObject
{
public:
	Text();
	virtual ~Text();
	void Render();

	void FontPtr(Font*);
	void XBearing(float);
	void YBearing(float);
	void Scale(float);
	void Message(const std::string&);
	void Color(const glm::vec4&);

	const Font* FontPtr() const;
	float XBearing() const;
	float YBearing() const;
	float Scale() const;
	const std::string& Message() const;
	const glm::vec4& Color() const;
protected:
	Font* mFont;
	float mXBearing;
	float mYBearing;
	float mScale;
	std::string mMessage;

};
/*@}*/
#endif