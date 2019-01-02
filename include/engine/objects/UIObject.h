#ifndef UI_OBJECT_HEADER_INCLUDED
#define UI_OBJECT_HEADER_INCLUDED

#include"engine/objects/Observer.h"

/** @addtogroup EngineObjects */
/*@{*/

class UIObject :
	public Observer
{
public:
	UIObject();
	virtual ~UIObject();
	virtual void Render() = 0;
	virtual void OnNotify(const GameObject&, const event_t&);
};
/*@}*/
#endif