#ifndef EXPLOSION_HEADER_INCLUDED
#define EXPLOSION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

using namespace Constants::Types;

/** @addtogroup GameComponents */
/*@{*/

class Explosion :
	public GameObject
{
public:
	Explosion();
	virtual ~Explosion();

	object_t Type() const override;
	virtual void Update(float) override;
	bool Terminate() const;

	void Speed(float);
	void MaxScale(float);

	float Speed() const;
	float MaxScale() const;

protected:
	float mSpeed;
	float mMaxScale;
};
/*@}*/
#endif