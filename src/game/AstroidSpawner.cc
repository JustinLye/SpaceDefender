#include"game/AstroidSpawner.h"

AstroidSpawner::AstroidSpawner(DrawableObject* shape, ShaderProgram* shader_prog) :
	Subject(),
	Observer(),
	ObjectManager<Astroid>(),
	mStartingYPos(0.0f),
	mTerminateYPos(0.0f),
	mProbabilityOfSpawn(0.0f),
	mMinRespawnWaitTime(0),
	mMaxRespawnWaitTime(0),
	mTransform(Transform()),
	mShape(shape),
	mRenderer(new TexRenderer(shader_prog, GL_FILL)),
	mGen(mRd()),
	mSpawnDist(0.0f, 100.0f),
	mPosDist(0.0f, 0.0f),
	mSpeedDist(0.0f, 0.0f),
	mScaleDist(0.0f, 0.0f),
	mLastSpawnTime(std::chrono::high_resolution_clock::now())
{
	Init();
}
AstroidSpawner::~AstroidSpawner()
{

}
int AstroidSpawner::MaxCapacity()
{
	return 30;
}
int AstroidSpawner::MaxActiveCapacity()
{
	return 15;
}
const int& AstroidSpawner::MinRespawnWaitTime() const
{
	return mMinRespawnWaitTime;
}
const int& AstroidSpawner::MaxRespawnWaitTime() const
{
	return mMaxRespawnWaitTime;
}
const float& AstroidSpawner::MinProjectileSpeed() const
{
	return mSpeedDist.min();
}
const float& AstroidSpawner::MaxProjectileSpeed() const
{
	return mSpeedDist.max();
}
const float& AstroidSpawner::StartingYPos() const
{
	return mStartingYPos;
}
const float& AstroidSpawner::MinXPos() const
{
	return mPosDist.min();
}
const float& AstroidSpawner::MaxXPos() const
{
	return mPosDist.max();
}
const float& AstroidSpawner::TerminateYPos() const
{
	return mTerminateYPos;
}
const float& AstroidSpawner::ProbabilityOfSpawn() const
{
	return mProbabilityOfSpawn;
}
const float& AstroidSpawner::MinScale() const
{
	return mScaleDist.min();
}
const float& AstroidSpawner::MaxScale() const
{
	return mScaleDist.max();
}

const Transform& AstroidSpawner::GetTransform() const
{
	return mTransform;
}

Transform& AstroidSpawner::GetTransform()
{
	return mTransform;
}

void AstroidSpawner::Scale(const float& scale)
{
	mTransform.Scale(scale);
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Scale(scale);
	}
}

void AstroidSpawner::Translate(const glm::vec3& translation)
{
	mTransform.Translate(translation);
}

void AstroidSpawner::MinRespawnWaitTime(const int& wait_time)
{
	mMinRespawnWaitTime = wait_time;
}
void AstroidSpawner::MaxRespawnWaitTime(const int& wait_time)
{
	mMaxRespawnWaitTime = wait_time;
}
void AstroidSpawner::MinProjectileSpeed(const float& speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(speed, mSpeedDist.max()));
}
void AstroidSpawner::MaxProjectileSpeed(const float& speed)
{
	mSpeedDist.param(std::uniform_real_distribution<>::param_type(mSpeedDist.min(), speed));
}
void AstroidSpawner::StartingYPos(const float& ypos)
{
	mStartingYPos = ypos;
}
void AstroidSpawner::MinXPos(const float& xpos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(xpos, mPosDist.max()));
}
void AstroidSpawner::MaxXPos(const float& xpos)
{
	mPosDist.param(std::uniform_real_distribution<>::param_type(mPosDist.min(), xpos));
}
void AstroidSpawner::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->TerminateYPos(ypos);
	}
}
void AstroidSpawner::ProbabilityOfSpawn(const float& prob)
{
	mProbabilityOfSpawn = prob;
}

void AstroidSpawner::MinScale(const float& scale)
{
	mScaleDist.param(std::uniform_real_distribution<>::param_type(scale, mScaleDist.max()));
}

void AstroidSpawner::MaxScale(const float& scale)
{
	mScaleDist.param(std::uniform_real_distribution<>::param_type(mScaleDist.min(), scale));
}

void AstroidSpawner::Init()
{
	CustomInitOps();
	mMaxCapacity = MaxCapacity();
	mMaxActiveCapacity = MaxActiveCapacity();
	mObjects = new Astroid*[mMaxCapacity];
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i] = ConstructObject();
		mIndexQueue.push(i);
		mAstroidToIndexMap.insert({ mObjects[i]->Id(), i });
	}
}

void AstroidSpawner::AddObserver(Observer* observer)
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

void AstroidSpawner::RemoveObserver(Observer* observer)
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

void AstroidSpawner::OnNotify(const GameObject& object, const Constants::Types::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::Types::event_t::TERMINATED_COLLIDABLE_OBJECT:
		if (object.Type() == Constants::Types::object_t::ASTROID)
		{
			std::list<unsigned int>::iterator iter = mActiveIndices.begin();
			unsigned int index = mAstroidToIndexMap[object.Id()];
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
		if (object.Type() == object_t::ASTROID)
		{
			//std::list<unsigned int>::iterator iter = mActiveIndices.begin();
			unsigned int index = mAstroidToIndexMap[object.Id()];
			Astroid* astroid = mObjects[index];
			astroid->HitPoints(astroid->HitPoints() - 1);
			/*while (iter != mActiveIndices.end())
			{
				if (*iter == index)
				{
					Astroid* astroid = mObjects[*iter];
					astroid->HitPoints(astroid->HitPoints() - 1);
					return;
				}
				++iter;
			}*/
		}
		break;
	case event_t::ASTROID_TO_ASTROID_COLLISION:
		Astroid* astroid_1 = mObjects[mAstroidToIndexMap[((const AstroidCollision&)object).GetAstroidIds().first]];
		Astroid* astroid_2 = mObjects[mAstroidToIndexMap[((const AstroidCollision&)object).GetAstroidIds().second]];
		// calculate final velocity
		glm::vec3 U1 = astroid_1->Velocity();
		float M1 = astroid_1->Mass();
		glm::vec3 U2 = astroid_2->Velocity();
		float M2 = astroid_2->Mass();
		glm::vec3 V1 = (U1 * (M1 - M2) + 2.0f * (M2)* U2) / (M1 + M2);
		glm::vec3 V2 = (U2 * (M2 - M1) + 2.0f * (M1)* U1) / (M1 + M2);
		glm::vec3 V1d = V1 - U1;
		glm::vec3 V2d = V2 - U2;
		glm::vec3 F1 = M1 * V1d;
		glm::vec3 F2 = M2 * V2d;
		astroid_1->Translate(V1);
		astroid_2->Translate(V2);
		if (astroid_1->Position().y < astroid_2->Position().y)
		{
			float depth_1_in_2 = astroid_1->Position().y + astroid_1->Scale().y;
			float depth_2_in_1 = astroid_2->Position().y - astroid_2->Scale().y;
			astroid_1->Translate(glm::vec3(0.0f, depth_2_in_1 - depth_1_in_2, 0.0f));
		} else
		{
			float depth_1_in_2 = astroid_1->Position().y - astroid_1->Scale().y;
			float depth_2_in_1 = astroid_2->Position().y + astroid_2->Scale().y;
			astroid_2->Translate(glm::vec3(0.0f, depth_1_in_2 - depth_2_in_1, 0.0f));
		}
		
		break;
	}
}

Astroid* AstroidSpawner::LookUpAstroid(const unsigned int& id)
{
	Astroid* result = nullptr;
	
	return result;
}

Astroid* AstroidSpawner::ConstructObject()
{
	Astroid* astroid = new Astroid();
	astroid->AddRenderer(mRenderer);
	astroid->AddDrawableObject(mShape);
	astroid->AddCollider(new Collider());
	astroid->AddObserver(this);
	astroid->HitPoints(2);
	astroid->AddRigidBody(new RigidBody());
	return astroid;
}

void AstroidSpawner::CustomAllocOps(const unsigned int& index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	Astroid* astroid = mObjects[index];
	astroid->Spawn(mTransform);
	astroid->Speed(mSpeedDist(mGen));
	astroid->Translate(glm::vec3(mPosDist(mGen), mStartingYPos - mTransform.Position().y, 0.0f));
	astroid->Scale(mScaleDist(mGen));
	astroid->HitPoints(2);
	astroid->Mass(astroid->Scale().x);
}

void AstroidSpawner::CustomDeallocOps(const unsigned int& index)
{
	mObjects[index]->ResetRigidBody();
}

void AstroidSpawner::CustomUpdateOps(const float& dt)
{
	TrySpawn();
}

void AstroidSpawner::TrySpawn()
{
	float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastSpawnTime).count();
	if (elapsed >= mMaxRespawnWaitTime || (elapsed >= mMinRespawnWaitTime && ((mProbabilityOfSpawn)*((float)mMinRespawnWaitTime/(float)mMaxRespawnWaitTime) > mSpawnDist(mGen))))
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


bool AstroidSpawner::DestructionPred(Astroid* astroid) const
{
	return astroid->Terminate();
}