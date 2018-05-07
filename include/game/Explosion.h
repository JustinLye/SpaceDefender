#ifndef EXPLOSION_HEADER_INCLUDED
#define EXPLOSION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

using namespace Constants::Types;

class Explosion :
	public GameObject
{
public:
	Explosion();
	virtual ~Explosion();

	const object_t& Type() const override;
	virtual void Update(const float&) override;
	bool Terminate() const;

	void Speed(const float&);
	void MaxScale(const float&);

	const float& Speed() const;
	const float& MaxScale() const;

protected:
	float mSpeed;
	float mMaxScale;
};

#endif