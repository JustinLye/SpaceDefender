#include"engine/objects/UIObject.h"


UIObject::UIObject() :
	Observer()
{

}

UIObject::~UIObject()
{

}

void UIObject::OnNotify(const GameObject& object, const event_t& event_name)
{

}