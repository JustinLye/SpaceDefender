#ifndef MENU_HEADER_INCLUDED
#define MENU_HEADER_INCLUDED

#include"engine/objects/Subject.h"
#include"engine/objects/Transform.h"
#include"engine/objects/Canvas.h"

/** @addtogroup EngineObjects */
/*@{*/

class Menu :
	public Subject
	public Canvas
{
public:
	Menu();
	virtual ~Menu();
	Transform& GetTransform();
protected:

};

/*@}*/

#endif