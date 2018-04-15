#ifndef PLAYER_HEADER_INCLUDED
#define PLAYER_HEADER_INCLUDED
#include"engine/util/OpenGLUtility.h"
#include"engine/util/BoundryBox.h"
#include"engine/objects/GameObject.h"
#include"game/LaserCannon.h"

class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
	void Render(const glm::mat4&, const glm::mat4&) override;
	void HandleKeyboardInput(GLFWwindow*);
	void AttachCannon(LaserCannon*);
	void Update(const float&) override;
	virtual void Strafe(const Constants::Movement::DIRECTION&);
	virtual void FireCannon();
	virtual void Speed(const float&);
	const float& Speed() const;
	virtual void Boost();
protected:
	float mSpeed;
	float mStep;
	BoundryBox mBoundries;
	float mTargetXPos;
	float mSpeedBoost;
	float mMaxBoost;
	LaserCannon* mLaserCannon;
};

#endif