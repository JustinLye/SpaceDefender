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

	int MinRespawnWaitTime() const;
	int MaxRespawnWaitTime() const;
	float MinProjectileSpeed() const;
	float MaxProjectileSpeed() const;
	float StartingYPos() const;
	float MinXPos() const;
	float MaxXPos() const;
	float TerminateYPos() const;
	float ProbabilityOfSpawn() const;
	int HitPoints() const;
	glm::vec3 ShipScale() const;
	int MaxPlacementAttempts() const;

	const Transform& GetTransform() const;
	Transform& GetTransform();

	void MinRespawnWaitTime(int);
	void MaxRespawnWaitTime(int);
	void MinProjectileSpeed(float);
	void MaxProjectileSpeed(float);
	void StartingYPos(float);
	void MinXPos(float);
	void MaxXPos(float);
	void TerminateYPos(float);
	void ProbabilityOfSpawn(float);
	void HitPoints(int);
	void ShipScale(const glm::vec3&);
	void ShipScale(float);
	void MaxPlacementAttempts(int);

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
	void CustomAllocOps(unsigned int) override;
	void CustomDeallocOps(unsigned int) override;
	void CustomUpdateOps(float) override;
	bool DestructionPred(EnemyShip*) const override;

	void TrySpawn();
	bool CanSpawn();

};

/*@}*/
#endif