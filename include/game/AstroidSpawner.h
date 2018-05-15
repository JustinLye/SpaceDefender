#ifndef ASTROID_SPAWNER_HEADER_INCLUDED
#define ASTROID_SPAWNER_HEADER_INCLUDED
#include<random>
#include<chrono>
#include"engine/objects/Subject.h"
#include"engine/objects/Observer.h"
#include"engine/containers/ObjectManager.h"
#include"engine/objects/RigidBody.h"
#include"engine/objects/TexRenderer.h"
#include"game/Astroid.h"
#include"game/AstroidCollision.h"
using namespace Constants::Types;
class AstroidSpawner :
	Subject,
	Observer,
	public ObjectManager<Astroid>
{
public:
	AstroidSpawner(DrawableObject*, ShaderProgram*);
	~AstroidSpawner();
	int MaxCapacity();
	int MaxActiveCapacity();

	void AddObserver(Observer*) override;
	void RemoveObserver(Observer*) override;

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
	std::map<unsigned int, unsigned int> mAstroidToIndexMap;
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
	Astroid* ConstructObject();
	void CustomAllocOps(const unsigned int&) override;
	void CustomDeallocOps(const unsigned int&) override;
	void CustomUpdateOps(const float&) override;
	bool DestructionPred(Astroid*) const override;

	void TrySpawn();
	Astroid* LookUpAstroid(const unsigned int&);

};


#endif
