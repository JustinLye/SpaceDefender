#ifndef LASER_HEADER_INCLUDED
#define LASER_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include"engine/objects/GameObject.h"


class Laser :
	public GameObject
{
public:
	Laser();
	~Laser();
	void Update(const float&) override;
	void Render(const glm::mat4&, const glm::mat4&) override;
	void TerminateYPos(const float&);
	const float& TerminateYPos() const;
	bool Terminate() const;
protected:
	float mTerminateYPos;
};

#endif