#ifndef LASER_CANNON_HEADER_INCLUDED
#define LASER_CANNON_HEADER_INCLUDED
#ifdef LASER_CANNON_DEBUG
#include"engine/util/DebugFunctions.h"
#endif // LASER_CANNON_DEBUG

#include<chrono>
#include"engine/objects/Observer.h"
#include"engine/objects/Subject.h"
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"game/Laser.h"

#ifdef COLLISION_DEBUG
#include"engine/shapes/CircleData.h"
#endif

/** @addtogroup GameComponents */
/*@{*/
class LaserCannon :
	public Subject,
	public Observer,
	public ObjectManager<Laser>
{
public:
	LaserCannon(DrawableObject*, ShaderProgram*);
	~LaserCannon();
	int MaxCapacity();
	int MaxActiveCapacity();
	void OnNotify(const GameObject&, const Constants::Types::event_t&);
	void AddObserver(Observer*) override;
	void RemoveObserver(Observer*) override;

	void DoDetection(Collider*);

	float ProjectileSpeed() const; 
	float CooldownTime() const;
	float LaserTermYPos() const;
	float OverheatCooldownTime() const;
	float CurrentGunTemp() const;
	float MaxGunTemp() const;
	bool GunOverHeated() const;

	const Transform& GetTransform() const;
	Transform& GetTransform();
	void Scale(float);
	void ScaleLasers(const glm::vec3&);
	void Translate(const glm::vec3&);
	unsigned int Fire();
	void ProjectileSpeed(float);
	void CooldownTime(float);
	void LaserTermYPos(float);
	void OverheatCooldownTime(float);
	bool DestructionPred(Laser*) const override;
	void AttachTo(const GameObject&);
	void Render(const glm::mat4&, const glm::mat4&) override;
	bool operator<(const LaserCannon&) const;

protected:
	Transform mTransform;
	DrawableObject* mShape;
	ShaderProgram* mShaderProg;
	Renderer* mRenderer;
	Collider* mCollider;
	Laser* ConstructObject();
	float mProjectileSpeed;
	std::chrono::time_point<std::chrono::steady_clock> mLastShotTime;
	float mCooldownTime;
	float mLaserTermYPos;
	float mOverheatCooldownTime;
	float mMaxGunTemp;
	float mCoolDownTemp;
	float mShotTemp;
	float mCoolDownStepTemp;
	float mCurrentGunTemp;
	bool mGunOverHeated;

	void CustomAllocOps(unsigned int) override;
	void CustomDeallocOps(unsigned int) override;
	void CustomInitOps() override;
	void CustomUpdateOps(float);
};
/*@}*/
#endif