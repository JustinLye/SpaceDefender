#ifndef ENEMY_SHIP_MANAGER_HEADER_INCLUDED
#define ENEMY_SHIP_MANAGER_HEADER_INCLUDED

#include<random>
#include<chrono>
#include<vector>
#include<list>
#include"engine/util/Constants.h"
#include"engine/objects/Subject.h"
#include"engine/objects/Observer.h"
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"engine/util/Logger.h"
#include"game/EnemyShip.h"
#include"game/ActiveObjectTracker.h"

using namespace Constants::Types;
using namespace std::chrono;

/** @addtogroup GameWorld */
/*@{*/
class EnemyShipManager :
	Subject,
	Observer,
	public ObjectManager<EnemyShip>
{
public:
	EnemyShipManager(DrawableObject*, ShaderProgram*);
	~EnemyShipManager();

	int MaxCapacity();
	int MaxActiveCapacity();
	std::vector<const EnemyShip*> ActiveEnemyShipList() const;

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
	const int& HitPoints() const;
	const glm::vec3& ShipScale() const;
	const int& MaxPlacementAttempts() const;

	const Transform& GetTransform() const;
	Transform& GetTransform();

	void MinRespawnWaitTime(const int&);
	void MaxRespawnWaitTime(const int&);
	void MinProjectileSpeed(const float&);
	void MaxProjectileSpeed(const float&);
	void StartingYPos(const float&);
	void MinXPos(const float&);
	void MaxXPos(const float&);
	void TerminateYPos(const float&);
	void ProbabilityOfSpawn(const float&);
	void HitPoints(const int&);
	void ShipScale(const glm::vec3&);
	void ShipScale(const float&);
	void MaxPlacementAttempts(const int&);

	void Init() override;

protected:
	float mStartingYPos;
	float mTerminateYPos;
	float mProbabilityOfSpawn;
	int mMinRespawnWaitTime;
	int mMaxRespawnWaitTime;
	int mHitPoints;
	glm::vec3 mShipScale;
	Transform mTransform;
	DrawableObject* mShape;
	TexRenderer* mRenderer;
	std::map<unsigned int, unsigned int> mEnemyShipToIndexMap;
	std::random_device mRd;
	std::mt19937 mGen;
	std::uniform_real_distribution<> mSpawnDist;
	std::uniform_real_distribution<> mPosDist;
	std::uniform_real_distribution<> mSpeedDist;

	std::chrono::time_point<
		std::chrono::high_resolution_clock,
		std::chrono::duration<float, std::milli>> mLastSpawnTime;

	float mNextXPos;
	int mMaxPlacementAttempts;
	const ActiveObjectTracker* mTracker;
	Logger* mLogger;

	void OnNotify(const GameObject&, const Constants::Types::event_t&);
	EnemyShip* ConstructObject();
	void CustomAllocOps(const unsigned int&) override;
	void CustomDeallocOps(const unsigned int&) override;
	void CustomUpdateOps(const float&) override;
	bool DestructionPred(EnemyShip*) const override;

	void TrySpawn();
	bool CanSpawn();

};

/*@}*/
#endif