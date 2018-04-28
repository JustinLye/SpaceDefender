#include"engine/objects/Canvas.h"

Canvas::Canvas() :
	UIObject()
{

}

Canvas::~Canvas()
{

}

void Canvas::Render()
{
	std::map<unsigned int, UIObject*>::iterator iter = mUIObjects.begin();
	while (iter != mUIObjects.end())
	{
		iter->second->Render();
		++iter;
	}
}

void Canvas::AddUIObject(UIObject* object)
{
	if (mUIObjects.find(object->Id()) == mUIObjects.end())
	{
		mUIObjects.insert({ object->Id(), object });
	}
}

void Canvas::RemoveUIObject(UIObject* object)
{
	mUIObjects.erase(object->Id());
}