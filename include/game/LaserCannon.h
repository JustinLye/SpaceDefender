#ifndef LASER_CANNON_HEADER_INCLUDED
#define LASER_CANNON_HEADER_INCLUDED
#include<chrono>
#include"engine/objects/Observer.h"
#include"engine/objects/Subject.h"
#include"engine/containers/ObjectManager.h"
#include"game/Laser.h"


class LaserCannon :
	public Subject,
	public Observer,
	public ObjectManager<Laser>
{
public:
	LaserCannon(Shape*, ShaderProgram*);
	~LaserCannon();
	int MaxCapacity();
	int MaxActiveCapacity();
	void OnNotify(const GameObject&, const Constants::event_t&);
	void AddObserver(Observer*) override;
	void RemoveObserver(Observer*) override;

	void DoDetection(Collider*);

	const float& ProjectileSpeed() const; 
	const float& CooldownTime() const;
	const Transform& GetTransform() const;
	Transform& GetTransform();

	unsigned int Fire();
	void ProjectileSpeed(const float&);
	void CooldownTime(const float&);
	bool DestructionPred(Laser*) const override;
	void AttachTo(const GameObject&);
	bool operator<(const LaserCannon&) const;

protected:
	Transform mTransform;
	Shape* mShape;
	ShaderProgram* mShaderProg;
	Renderer* mRenderer;
	Collider* mCollider;
	Laser* ConstructObject();
	float mProjectileSpeed;
	std::chrono::time_point<std::chrono::steady_clock> mLastShotTime;
	float mCooldownTime;
	void CustomAllocOps(const unsigned int&) override;
	void CustomDeallocOps(const unsigned int&) override;
	void CustomInitOps() override;
};

#endif