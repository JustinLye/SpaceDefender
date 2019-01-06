#ifndef PLAYER_HEADER_INCLUDED
#define PLAYER_HEADER_INCLUDED
#include"engine/util/OpenGLUtility.h"
#include"engine/util/BoundryBox.h"
#include"engine/objects/GameObject.h"
#include"game/LaserCannon.h"

using namespace Constants::Types;
/** @addtogroup GameActors */
/*@{*/
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
	object_t Type() const override;
	void Render(const glm::mat4&, const glm::mat4&) override;
	void HandleKeyboardInput(GLFWwindow*);
	void AttachCannon(LaserCannon*);
	void Update(float) override;
	virtual void Strafe(const Constants::Types::DIRECTION&);
	virtual void FireCannon();
	virtual void CustomScaleActions(float) override;
	virtual void CustomTranslateActions(const glm::vec3&) override;
	virtual void Speed(float);
	float Speed() const;
	virtual void Boost(float);
	float Boost() const;
	float CurrentGunTemp() const;
	float MaxGunTemp() const;
	bool GunOverHeated() const;

	virtual void DoDetection(Collider*);
	virtual void AddObserver(Observer*) override;
	virtual void RemoveObserver(Observer*) override;
protected:
	float mSpeed;
	float mStep;
	BoundryBox mBoundries;
	float mTargetXPos;
	float mSpeedBoost;
	float mMaxBoost;
	LaserCannon* mLaserCannon;
};
/*@}*/
#endif