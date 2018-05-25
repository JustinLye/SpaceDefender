#include"game/AsteroidSpawner.h"

AsteroidSpawner::AsteroidSpawner(DrawableObject* shape, ShaderProgram* shader_prog) :
	Subject(),
	Observer(),
	ObjectManager<Asteroid>(),
	mStartingYPos(0.0f),
	mTerminateYPos(0.0f),
	mProbabilityOfSpawn(0.0f),
	mMinRespawnWaitTime(0),
	mMaxRespawnWaitTime(0),
	mMinHitPoints(1),
	mMaxHitPoints(1),
	mTransform(Transform()),
	mShape(shape),
	mRenderer(new TexRenderer(shader_prog, { GL_FILL, GL_FILL })),
	mGen(mRd()),
	mSpawnDist(0.0f, 100.0f),
	mPosDist(0.0f, 0.0f),
	mSpeedDist(0.0f, 0.0f),
	mScaleDist(0.0f, 0.0f),
	mRotateDist(0.0f, 0.0f),
	mLastSpawnTime(std::chrono::high_resolution_clock::now())
{
	Init();
}
AsteroidSpawner::~AsteroidSpawner()
{

}
int AsteroidSpawner::MaxCapacity()
{
	return 30;
}
int AsteroidSpawner::MaxActiveCapacity()
{
	return 15;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///\fn std::vector<const Asteroid*> AsteroidSpawner::ActiveAsteroidList() const
///\brief Access to active asteroids
///\returns vector full of const pointers to active Asteriod objects
///
///\date 05/19/2018
///\author Justin Lye
/////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<const Asteroid*> AsteroidSpawner::ActiveAsteroidList() const
{
	// init result vector
	std::vector<const Asteroid*> result;
	result.reserve(mActiveIndices.size());

	// fill result vector
	std::list<unsigned int>::const_iterator iter = mActiveIndices.cbegin();
	while (iter != mActiveIndices.cend())
	{
		result.push_back(const_cast<const Asteroid*>(mObjects[*iter]));
		++iter;
	}
	return result;
}
const int& AsteroidSpawner::MinRespawnWaitTime() const
{
	return mMinRespawnWaitTime;
}
const int& AsteroidSpawner::MaxRespawnWaitTime() const
{
	return mMaxRespawnWaitTime;
}
const float& AsteroidSpawner::MinProjectileSpeed() const
{
	return mSpeedDist.min();
}
const float& AsteroidSpawner::MaxProjectileSpeed() const
{
	return mSpeedDist.max();
}
const float& AsteroidSpawner::StartingYPos() const
{
	return mStartingYPos;
}
const float& AsteroidSpawner::MinXPos() const
{
	return mPosDist.min();
}
const float& AsteroidSpawner::MaxXPos() const
{
	return mPosDist.max();
}
const float& AsteroidSpawner::TerminateYPos() const
{
	return mTerminateYPos;
}
const float& AsteroidSpawner::ProbabilityOfSpawn() const
{
	return mProbabilityOfSpawn;
}
const float& AsteroidSpawner::MinScale() const
{
	return mScaleDist.min();
}
const float& AsteroidSpawner::MaxScale() const
{
	return mScaleDist.max();
}

const int& AsteroidSpawner::MinHitPoints() const
{
	return mMinHitPoints;
}

const int& AsteroidSpawner::MaxHitPoints() const
{
	return mMaxHitPoints;
}

const float& AsteroidSpawner::MinRotationSpeed() const
{
	return mRotateDist.min();
}

const float& AsteroidSpawner::MaxRotationSpeed() const
{
	return mRotateDist.max();
}

const Transform& AsteroidSpawner::GetTransform() const
{
	return mTransform;
}

Transform& AsteroidSpawner::GetTransform()
{
	return mTransform;
}

void AsteroidSpawner::Scale(const float& scale)
{
	mTransform.Scale(scale);
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Scale(scale);
	}
}

void AsteroidSpawner::Translate(const glm::vec3& translation)
{
	mTransform.Translate(translation);
}

void AsteroidSpawner::MinRespawnWaitTime(const int& wait_time)
{
	mMinRespawnWaitTime = wait_time;
}
void AsteroidSpawner::MaxRespawnWaitTime(const int& wait_time)
{
	mMaxRespawnWaitTime = wait_time;
}
void AsteroidSpawner::MinProjectileSpeed(const float& speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(speed, mSpeedDist.max()));
}
void AsteroidSpawner::MaxProjectileSpeed(const float& speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(mSpeedDist.min(), speed));
}
void AsteroidSpawner::StartingYPos(const float& ypos)
{
	mStartingYPos = ypos;
}
void AsteroidSpawner::MinXPos(const float& xpos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(xpos, mPosDist.max()));
}
void AsteroidSpawner::MaxXPos(const float& xpos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(mPosDist.min(), xpos));
}
void AsteroidSpawner::MinRotationSpeed(const float& speed)
{
	mRotateDist.param(std::uniform_real_distribution<>::param_type(speed, mRotateDist.max()));
}
void AsteroidSpawner::MaxRotationSpeed(const float& speed)
{
	mRotateDist.param(std::uniform_real_distribution<>::param_type(mRotateDist.min(), speed));
}

void AsteroidSpawner::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->TerminateYPos(ypos);
	}
}
void AsteroidSpawner::ProbabilityOfSpawn(const float& prob)
{
	mProbabilityOfSpawn = prob;
}

void AsteroidSpawner::MinScale(const float& scale)
{
	mScaleDist.param(std::uniform_real_distribution<>::param_type(scale, mScaleDist.max()));
}

void AsteroidSpawner::MaxScale(const float& scale)
{
	mScaleDist.param(std::uniform_real_distribution<>::param_type(mScaleDist.min(), scale));
}

void AsteroidSpawner::MinHitPoints(const int& hp)
{
	mMinHitPoints = hp;
}

void AsteroidSpawner::MaxHitPoints(const int& hp)
{
	mMaxHitPoints = hp;
}

void AsteroidSpawner::Init()
{
	CustomInitOps();
	mMaxCapacity = MaxCapacity();
	mMaxActiveCapacity = MaxActiveCapacity();
	mObjects = new Asteroid*[mMaxCapacity];
	mIndexQueue.Initialize(mMaxCapacity);
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i] = ConstructObject();
		mIndexQueue.Insert(i);
		mAsteroidToIndexMap.insert({ mObjects[i]->Id(), i });
	}
}

void AsteroidSpawner::AddObserver(Observer* observer)
{
	if (!ObserverIsMapped(observer))
	{
		mObserverMap.insert({ observer->Id(), observer });
	}
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->AddObserver(observer);
	}
}

void AsteroidSpawner::RemoveObserver(Observer* observer)
{
	if (ObserverIsMapped(observer))
	{
		mObserverMap.erase(observer->Id());
	}
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->RemoveObserver(observer);
	}
}

void AsteroidSpawner::OnNotify(const GameObject& object, const Constants::Types::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::Types::event_t::TERMINATED_COLLIDABLE_OBJECT:
		if (object.Type() == Constants::Types::object_t::ASTEROID)
		{
			std::list<unsigned int>::iterator iter = mActiveIndices.begin();
			unsigned int index = mAsteroidToIndexMap[object.Id()];
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
	case Constants::Types::event_t::COLLISION_REPORTED:
		if (object.Type() == object_t::ASTEROID)
		{
			//std::list<unsigned int>::iterator iter = mActiveIndices.begin();
			unsigned int index = mAsteroidToIndexMap[object.Id()];
			Asteroid* asteroid = mObjects[index];
			asteroid->HitPoints(asteroid->HitPoints() - 1);
			/*while (iter != mActiveIndices.end())
			{
				if (*iter == index)
				{
					Asteroid* asteroid = mObjects[*iter];
					asteroid->HitPoints(asteroid->HitPoints() - 1);
					return;
				}
				++iter;
			}*/
		}
		break;
	case event_t::ASTEROID_TO_ASTEROID_COLLISION:
		Asteroid* asteroid_1 = mObjects[mAsteroidToIndexMap[((const AsteroidCollision&)object).GetAsteroidIds().first]];
		Asteroid* asteroid_2 = mObjects[mAsteroidToIndexMap[((const AsteroidCollision&)object).GetAsteroidIds().second]];
		// calculate final velocity
		glm::vec3 U1 = asteroid_1->Velocity();
		float M1 = asteroid_1->Mass();
		glm::vec3 U2 = asteroid_2->Velocity();
		float M2 = asteroid_2->Mass();
		glm::vec3 V1 = (U1 * (M1 - M2) + 2.0f * (M2)* U2) / (M1 + M2);
		glm::vec3 V2 = (U2 * (M2 - M1) + 2.0f * (M1)* U1) / (M1 + M2);
		glm::vec3 V1d = V1 - U1;
		glm::vec3 V2d = V2 - U2;
		glm::vec3 F1 = M1 * V1d;
		glm::vec3 F2 = M2 * V2d;
		asteroid_1->Translate(V1);
		asteroid_2->Translate(V2);
		if (asteroid_1->Position().y < asteroid_2->Position().y)
		{
			float depth_1_in_2 = asteroid_1->Position().y + asteroid_1->Scale().y;
			float depth_2_in_1 = asteroid_2->Position().y - asteroid_2->Scale().y;
			asteroid_1->Translate(glm::vec3(0.0f, depth_2_in_1 - depth_1_in_2, 0.0f));
		} else
		{
			float depth_1_in_2 = asteroid_1->Position().y - asteroid_1->Scale().y;
			float depth_2_in_1 = asteroid_2->Position().y + asteroid_2->Scale().y;
			asteroid_2->Translate(glm::vec3(0.0f, depth_1_in_2 - depth_2_in_1, 0.0f));
		}
		
		break;
	}
}

Asteroid* AsteroidSpawner::LookUpAsteroid(const unsigned int& id)
{
	Asteroid* result = nullptr;
	
	return result;
}

Asteroid* AsteroidSpawner::ConstructObject()
{
	Asteroid* asteroid = new Asteroid();
	asteroid->AddRenderer(mRenderer);
	asteroid->AddDrawableObject(mShape);
	asteroid->AddCollider(new Collider());
	asteroid->AddObserver(this);
	asteroid->HitPoints(1);
	asteroid->AddRigidBody(new RigidBody());
	return asteroid;
}

void AsteroidSpawner::CustomAllocOps(const unsigned int& index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	Asteroid* asteroid = mObjects[index];
	asteroid->Spawn(mTransform);
	asteroid->Speed(mSpeedDist(mGen));
	asteroid->Translate(glm::vec3(mPosDist(mGen), mStartingYPos - mTransform.Position().y, 0.0f));
	asteroid->Scale(mScaleDist(mGen));
	asteroid->HitPoints((int)((asteroid->Scale().x / mScaleDist.max()) * (mMaxHitPoints - mMinHitPoints) + mMinHitPoints));
	asteroid->Mass(asteroid->Scale().x);
	asteroid->RotationSpeed(mRotateDist(mGen));
}

void AsteroidSpawner::CustomDeallocOps(const unsigned int& index)
{
	mObjects[index]->ResetRigidBody();
	if (mObjects[index]->HitPoints() > 0)
	{
		Notify(*mObjects[index], event_t::OBJECT_OUT_OF_BOUNDS);
	}
}

void AsteroidSpawner::CustomUpdateOps(const float& dt)
{
	TrySpawn();
}

void AsteroidSpawner::TrySpawn()
{
	float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastSpawnTime).count();
	//if (elapsed >= mMaxRespawnWaitTime || (elapsed >= mMinRespawnWaitTime && ((mProbabilityOfSpawn)*((float)mMinRespawnWaitTime/(float)mMaxRespawnWaitTime) > mSpawnDist(mGen))))
	if (elapsed >= mMaxRespawnWaitTime || (elapsed >= mMinRespawnWaitTime && (mProbabilityOfSpawn > mSpawnDist(mGen))))
	{
		if (mActiveIndices.size() < mMaxActiveCapacity)
		{
			if (Alloc() != NOT_INDEX)
			{
				mLastSpawnTime = std::chrono::high_resolution_clock::now();
			}
		}
	}
}


bool AsteroidSpawner::DestructionPred(Asteroid* asteroid) const
{
	return asteroid->Terminate();
}