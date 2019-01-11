#include"game/EnemyShipManager.h"
namespace sd_app {
namespace game {
namespace impl {
namespace enemy_ship_manager {
EnemyShipManager::EnemyShipManager(DrawableObject* shape, ShaderProgram* shader_prog) :
	Subject(),
	Observer(),
	ObjectManager<EnemyShip>(),
	mStartingYPos(0.0f),
	mTerminateYPos(0.0f),
	mProbabilityOfSpawn(0.0f),
	mMinRespawnWaitTime(0),
	mMaxRespawnWaitTime(0),
	mHitPoints(1),
	mShipScale(glm::vec3(1.0f)),
	mTransform(Transform()),
	mShape(shape),
	mRenderer(new TexRenderer(shader_prog, { GL_FILL, GL_FILL })),
	mEnemyShipToIndexMap(std::map<unsigned int, unsigned int>()),
	mGen(mRd()),
	mSpawnDist(0.0f, 100.0f),
	mPosDist(0.0f, 0.0f),
	mSpeedDist(0.0f, 0.0f),
	mLastSpawnTime(high_resolution_clock::now()),
	mNextXPos(0.0),
	mMaxPlacementAttempts(1),
	mTracker(nullptr)
{
	std::string p = LogFilePath("enemy-shp-mgr.log");
	mLogger = new Logger(p.c_str());
	mLogger->Launch();
	Init();
}

EnemyShipManager::~EnemyShipManager()
{

}

int EnemyShipManager::MaxCapacity()
{
	return 10;
}

int EnemyShipManager::MaxActiveCapacity()
{
	return 8;
}


std::vector<const EnemyShip*> EnemyShipManager::ActiveEnemyShipList() const
{
	// init result vector
	std::vector<const EnemyShip*> result;
	result.reserve(mActiveIndices.size());

	// fill result vector
	std::list<unsigned int>::const_iterator iter = mActiveIndices.cbegin();
	while (iter != mActiveIndices.cend())
	{
		result.push_back(const_cast<const EnemyShip*>(mObjects[*iter]));
		++iter;
	}
	return result;
}

void EnemyShipManager::AddObserver(Observer* observer)
{
	if (mObserverMap.find(observer->Id()) == mObserverMap.end())
	{
		mObserverMap.insert({ observer->Id(), observer });
	}
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->AddObserver(observer);
	}
}

void EnemyShipManager::RemoveObserver(Observer* observer)
{
	mObserverMap.erase(observer->Id());
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->RemoveObserver(observer);
	}
}

void EnemyShipManager::AddActiveObjectTracker(const ActiveObjectTracker* tracker)
{
	mTracker = tracker;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->AddActiveObjectTracker(tracker);
	}
}

int EnemyShipManager::MinRespawnWaitTime() const
{
	return mMinRespawnWaitTime;
}

int EnemyShipManager::MaxRespawnWaitTime() const
{
	return mMaxRespawnWaitTime;
}

double EnemyShipManager::MinProjectileSpeed() const
{
	return mSpeedDist.min();
}

double EnemyShipManager::MaxProjectileSpeed() const
{
	return mSpeedDist.max();
}

float EnemyShipManager::StartingYPos() const
{
	return mStartingYPos;
}

double EnemyShipManager::MinXPos() const
{
	return mPosDist.min();
}

double EnemyShipManager::MaxXPos() const
{
	return mPosDist.max();
}

float EnemyShipManager::TerminateYPos() const
{
	return mTerminateYPos;
}

float EnemyShipManager::ProbabilityOfSpawn() const
{
	return mProbabilityOfSpawn;
}

int EnemyShipManager::HitPoints() const
{
	return mHitPoints;
}

glm::vec3 EnemyShipManager::ShipScale() const
{
	return mShipScale;
}

int EnemyShipManager::MaxPlacementAttempts() const
{
	return mMaxPlacementAttempts;
}

const Transform& EnemyShipManager::GetTransform() const
{
	return mTransform;
}

Transform& EnemyShipManager::GetTransform()
{
	return mTransform;
}

void EnemyShipManager::MinRespawnWaitTime(int min)
{
	mMinRespawnWaitTime = min;
}

void EnemyShipManager::MaxRespawnWaitTime(int max)
{
	mMaxRespawnWaitTime = max;
}

void EnemyShipManager::MinProjectileSpeed(float speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(speed, mSpeedDist.max()));
}

void EnemyShipManager::MaxProjectileSpeed(float speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(mSpeedDist.min(), speed));
}

void EnemyShipManager::StartingYPos(float pos)
{
	mStartingYPos = pos;
}

void EnemyShipManager::MinXPos(float pos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(pos, mPosDist.max()));
}

void EnemyShipManager::MaxXPos(float pos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(mPosDist.min(), pos));
}

void EnemyShipManager::TerminateYPos(float pos)
{
	mTerminateYPos = pos;
}

void EnemyShipManager::ProbabilityOfSpawn(float prob)
{
	mProbabilityOfSpawn = prob;
}

void EnemyShipManager::HitPoints(int hp)
{
	mHitPoints = hp;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->HitPoints(hp);
	}
}

void EnemyShipManager::ShipScale(const glm::vec3& scale)
{
	mShipScale = scale;
}

void EnemyShipManager::ShipScale(float scale)
{
	mShipScale = glm::vec3(scale);
}

void EnemyShipManager::MaxPlacementAttempts(int attempts)
{
	mMaxPlacementAttempts = attempts;
}

void EnemyShipManager::Init()
{
	CustomInitOps();
	mMaxCapacity = MaxCapacity();
	mMaxActiveCapacity = MaxActiveCapacity();
	mObjects = new EnemyShip*[mMaxCapacity];
	mIndexQueue.Initialize(mMaxCapacity);
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i] = ConstructObject();
		mIndexQueue.Insert(i);
		mEnemyShipToIndexMap.insert({ mObjects[i]->Id(), i });
	}
}

void EnemyShipManager::OnNotify(const GameObject& object, const event_t& event_name)
{
	
	if (object.Type() == object_t::ENEMY_SHIP)
	{
		std::map<unsigned int, unsigned int>::iterator ship_iter = mEnemyShipToIndexMap.find(object.Id());
		if (ship_iter == mEnemyShipToIndexMap.end())
		{
			return;
		}
		EnemyShip* ship = nullptr;
		std::list<unsigned int>::iterator iter;
		unsigned int index = NOT_INDEX;
		switch (event_name)
		{
		case event_t::PLAYER_DESTROYED_ENEMY_SHIP:
			if (object.Type() == object_t::ENEMY_SHIP)
			{
				iter = mActiveIndices.begin();
				index = mEnemyShipToIndexMap[object.Id()];
				while (iter != mActiveIndices.end())
				{
					if (*iter == index)
					{
						iter = Dealloc(iter);
						return;
					}
					++iter;
				}
			}
			break;
			case event_t::COLLISION_REPORTED:
				ship = mObjects[ship_iter->second];
				ship->HitPoints(ship->HitPoints() - 1);
				break;
		}
	}
}

EnemyShip* EnemyShipManager::ConstructObject()
{
	EnemyShip* ship = new EnemyShip();
	ship->AddRenderer(mRenderer);
	ship->AddDrawableObject(mShape);
	ship->AddCollider(new Collider());
	ship->AddObserver(this);
	ship->HitPoints(mHitPoints);
	ship->AddRigidBody(new RigidBody());
	ship->TerminateYPos(mTerminateYPos);
	ship->Up(glm::vec3(0.0f, -1.0f, 0.0f));
	return ship;
}

void EnemyShipManager::CustomAllocOps(unsigned int index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	EnemyShip* ship = mObjects[index];
	ship->Spawn(mTransform);
	if (ship->Scale() != mShipScale)
	{
		ship->ResetScale();
		ship->Scale(mShipScale);
	}
	ship->Speed(mSpeedDist(mGen));
	ship->Translate(glm::vec3(mNextXPos, mStartingYPos - mTransform.Position().y, 0.0f));
	ship->HitPoints(mHitPoints);
	/*float rad = DegToRad(180.0f);
	mLogger->Log(std::string("rads ") + std::to_string(rad));
	ship->Rotate(DegToRad(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));*/
}

void EnemyShipManager::CustomDeallocOps(unsigned int index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	mObjects[index]->ResetRigidBody();
	Notify(*mObjects[index], event_t::DESPAWNED_OBJECT);
}

void EnemyShipManager::CustomUpdateOps(float dt)
{
	TrySpawn();
}

bool EnemyShipManager::DestructionPred(EnemyShip* ship) const
{
	return ship->Terminate();
}

void EnemyShipManager::TrySpawn()
{
	// See if we can spawn
	if (CanSpawn())
	{
		// Make sure allocation went ok
		if (Alloc() != NOT_INDEX)
		{
			// Reset last spawn time
			mLastSpawnTime = high_resolution_clock::now();
		}
	}
}

bool EnemyShipManager::CanSpawn()
{
	// Check if all active slots are used
	if (mActiveIndices.size() >= static_cast<std::size_t>(mMaxActiveCapacity))
	{
		return false;
	}
	// Get time since last spawn in milliseconds
	float elapsed = static_cast<float>(duration_cast<milliseconds>(high_resolution_clock::now() - mLastSpawnTime).count());

	// Check if enough time has passed since last spawn
	if (elapsed < mMinRespawnWaitTime)
	{
		return false;
	}

	// Check if max time since last spawn has passed
	if (elapsed >= mMaxRespawnWaitTime)
	{
		return true;
	}

	// Roll for chance to spawn
	if (mProbabilityOfSpawn > mSpawnDist(mGen))
	{
		if (mTracker != nullptr)
		{
			// Make sure don't set the ship on top of another object
			int attempts = 0;
			std::vector<const GameObject*> close_objects;
			Transform probe = mTransform;
			mNextXPos = mPosDist(mGen);
			probe.Translate(glm::vec3(mNextXPos, mStartingYPos - mTransform.Position().y, 0.0f));
			if (probe.Scale() != mShipScale)
			{
				probe.ResetScale();
				probe.Scale(mShipScale*2.5f);
			}

			mTracker->ObjectScan(probe, close_objects);

			if (close_objects.size() == 0)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}
} // namespace enemy_ship_manager
} // namespace impl
} // namespace game
} // namespace sd_app