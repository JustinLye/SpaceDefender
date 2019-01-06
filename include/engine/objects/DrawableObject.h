#ifndef DRAWABLE_OBJECT_HEADER_INCLUDED
#define DRAWABLE_OBJECT_HEADER_INCLUDED

#include<glad/glad.h>
/** @addtogroup EngineObjects */
/*@{*/
class DrawableObject
{
public:
	DrawableObject();
	virtual ~DrawableObject();
	virtual void Draw() = 0;
	virtual void Activate();
	virtual void Deactivate();
	virtual const unsigned int& GetVAO() const;
	virtual unsigned int GetVAO();
	virtual bool operator<(const DrawableObject&) const;
	virtual bool operator==(const DrawableObject&) const;
protected:
	unsigned int mVaoId;
	virtual void CustomActivationSteps();
	virtual void CustomDeactivationSteps();
};
/*@}*/
#endif
