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

	const int& MinRespawnWaitTime() const;
	const int& MaxRespawnWaitTime() const;
	const float& MinProjectileSpeed() const;
	const float& MaxProjectileSpeed() const;
	const float& StartingYPos() const;
	const float& MinXPos() const;
	const float& MaxXPos() const;
	const float& TerminateYPos() const;
	const float& ProbabilityOfSpawn() const;
	const float& MinScale() const;
	const float& MaxScale() const;
	const int& MinHitPoints() const;
	const int& MaxHitPoints() const;
	const float& MinRotationSpeed() const;
	const float& MaxRotationSpeed() const;

	const Transform& GetTransform() const;
	Transform& GetTransform();

	void Scale(const float&);
	void Translate(const glm::vec3&);

	void MinRespawnWaitTime(const int&);
	void MaxRespawnWaitTime(const int&);
	void MinProjectileSpeed(const float&);
	void MaxProjectileSpeed(const float&);
	void StartingYPos(const float&);
	void MinXPos(const float&);
	void MaxXPos(const float&);
	void TerminateYPos(const float&);
	void ProbabilityOfSpawn(const float&);
	void MinScale(const float&);
	void MaxScale(const float&);
	void MinHitPoints(const int&);
	void MaxHitPoints(const int&);
	void MinRotationSpeed(const float&);
	void MaxRotationSpeed(const float&);

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
	void CustomAllocOps(const unsigned int&) override;
	void CustomDeallocOps(const unsigned int&) override;
	void CustomUpdateOps(const float&) override;
	bool DestructionPred(Asteroid*) const override;

	void TrySpawn();
	Asteroid* LookUpAsteroid(const unsigned int&);

};
/*@}*/

#endif
