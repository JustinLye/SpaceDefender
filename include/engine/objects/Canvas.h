#ifndef CANVAS_HEADER_INCLUDED
#define CANVAS_HEADER_INCLUDED
#include<map>
#include"engine/objects/UIObject.h"
#include"engine/objects/Text.h"
class Canvas :
	public UIObject
{
public:
	Canvas();
	virtual ~Canvas();
	void Render();

	void AddUIObject(UIObject*);
	void RemoveUIObject(UIObject*);

protected:
	std::map<unsigned int, UIObject*> mUIObjects;
};


#endif
