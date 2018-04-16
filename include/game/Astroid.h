#ifndef ASTROID_HEADER_INCLUDED
#define ASTROID_HEADER_INCLDUED

#include"engine/objects/GameObject.h"

class Astroid :
	public GameObject
{
public:
	Astroid();
	~Astroid();
	
	const float& Speed() const;
	const float& TerminateYPos() const;

	void Speed(const float&);
	void TerminateYPos(const float&);

	void Update(const float&) override;
	
	bool Terminate() const;

protected:
	float mSpeed;
	float mTerminateYPos;
};

#endif