#ifndef ASTEROID_SPAWNER_HEADER_INCLUDED
#define ASTEROID_SPAWNER_HEADER_INCLUDED
#include<random>
#include<chrono>
#include<vector>
#include"engine/objects/Subject.h"
#include"engine/objects/Observer.h"
#include"engine/containers/ObjectManager.h"
#include"engine/objects/RigidBody.h"
#include"engine/objects/TexRenderer.h"
#include"game/Asteroid.h"
#include"game/AsteroidCollision.h"
#include"game/ActiveObjectTracker.h"

/** @addtogroup GameWorld */
/*@{*/
using namespace Constants::Types;
class AsteroidSpawner :
	Subject,
	Observer,
	public ObjectManager<Asteroid>
{
public:
	AsteroidSpawner(DrawableObject*, ShaderProgram*);
	~AsteroidSpawner();
	int MaxCapacity();
	int MaxActiveCapacity();
	std::vector<const Asteroid*> ActiveAsteroidList() const;

	void AddObserver(Observer*) override;
	void RemoveObserver(Observer*) override;
	void AddActiveObjectTracker(const ActiveObjectTracker*);

	int MinRespawnWaitTime() const;
	int MaxRespawnWaitTime() const;
	float MinProjectileSpeed() const;
	float MaxProjectileSpeed() const;
	float StartingYPos() const;
	float MinXPos() const;
	float MaxXPos() const;
	float TerminateYPos() const;
	float ProbabilityOfSpawn() const;
	float MinScale() const;
	float MaxScale() const;
	int MinHitPoints() const;
	int MaxHitPoints() const;
	float MinRotationSpeed() const;
	float MaxRotationSpeed() const;

	const Transform& GetTransform() const;
	Transform& GetTransform();

	void Scale(float);
	void Translate(const glm::vec3&);

	void MinRespawnWaitTime(int);
	void MaxRespawnWaitTime(int);
	void MinProjectileSpeed(float);
	void MaxProjectileSpeed(float);
	void StartingYPos(float);
	void MinXPos(float);
	void MaxXPos(float);
	void TerminateYPos(float);
	void ProbabilityOfSpawn(float);
	void MinScale(float);
	void MaxScale(float);
	void MinHitPoints(int);
	void MaxHitPoints(int);
	void MinRotationSpeed(float);
	void MaxRotationSpeed(float);

	void Init() override;

protected:
	float mStartingYPos;
	float mTerminateYPos;
	float mProbabilityOfSpawn;
	int mMinRespawnWaitTime;
	int mMaxRespawnWaitTime;
	int mMinHitPoints;
	int mMaxHitPoints;
	Transform mTransform;
	DrawableObject* mShape;
	TexRenderer* mRenderer;
	std::map<unsigned int, unsigned int> mAsteroidToIndexMap;
	std::random_device mRd;
	std::mt19937 mGen;
	std::uniform_real_distribution<> mSpawnDist;
	std::uniform_real_distribution<> mPosDist;
	std::uniform_real_distribution<> mSpeedDist;
	std::uniform_real_distribution<> mScaleDist;
	std::uniform_real_distribution<> mRotateDist;

	std::chrono::time_point<
		std::chrono::high_resolution_clock,
		std::chrono::duration<float, std::milli>> mLastSpawnTime;

	void OnNotify(const GameObject&, const Constants::Types::event_t&);
	Asteroid* ConstructObject();
	void CustomAllocOps(unsigned int) override;
	void CustomDeallocOps(unsigned int) override;
	void CustomUpdateOps(float) override;
	bool DestructionPred(Asteroid*) const override;

	void TrySpawn();
	Asteroid* LookUpAsteroid(unsigned int);

};
/*@}*/

#endif
