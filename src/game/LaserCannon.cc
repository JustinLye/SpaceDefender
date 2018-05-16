#include"game/LaserCannon.h"

LaserCannon::LaserCannon(DrawableObject* laser, ShaderProgram* shader) :
	Subject(),
	Observer(),
	ObjectManager<Laser>(), 
	mTransform(Transform()),
	mShape(laser),
	mShaderProg(shader),
	mRenderer(nullptr),
	mCollider(nullptr),
	mProjectileSpeed(20.0f),
	mCooldownTime(0.0f),
	mLastShotTime(std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(1000000)),
	mLaserTermYPos(0.0f),
	mOverheatCooldownTime(0.0f),
	mMaxGunTemp(100.0f),
	mCoolDownTemp(20.0f),
	mShotTemp(5.8f),
	mCoolDownStepTemp(0.30f),
	mCurrentGunTemp(0.0f),
	mGunOverHeated(false)
{
	Init();
}

LaserCannon::~LaserCannon()
{

}

int LaserCannon::MaxCapacity()
{
	return 20;
}

int LaserCannon::MaxActiveCapacity()
{
	return 20;
}

void LaserCannon::OnNotify(const GameObject& object, const Constants::Types::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::Types::event_t::TERMINATED_COLLIDABLE_OBJECT:
		if (object.Type() == Constants::Types::object_t::LASER)
		{
			std::list<unsigned int>::iterator iter = mActiveIndices.begin();
			while (iter != mActiveIndices.end())
			{
				if (mObjects[*iter]->Id() == object.Id())
				{
					Dealloc(iter);
					return;
				}
				++iter;
			}
		}
		break;
	}
}

void LaserCannon::AddObserver(Observer* observer)
{
	if (!ObserverIsMapped(observer))
	{
		mObserverMap.insert({ observer->Id(), observer });
	}
	for (int i = 0; i < mMaxCapacity; ++i) // Add observer to each laser
	{
		mObjects[i]->AddObserver(observer);
	}
}

void LaserCannon::RemoveObserver(Observer* observer)
{
	mObserverMap.erase(observer->Id());
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->RemoveObserver(observer);
	}
}

void LaserCannon::DoDetection(Collider* collider)
{
	std::list<unsigned int>::iterator iter = mActiveIndices.begin();
	while (iter != mActiveIndices.end())
	{
		if (mObjects[*iter]->CollisionDetected(collider))
		{
			iter = Dealloc(iter);
		}
	}
}

bool LaserCannon::DestructionPred(Laser* object) const
{
	return object->Terminate();
}

void LaserCannon::AttachTo(const GameObject& object)
{
	mTransform.Match(object.GetTransform());
}

void LaserCannon::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	std::list<unsigned int>::iterator iter = mActiveIndices.begin();
	while (iter != mActiveIndices.end())
	{
		reinterpret_cast<TexRenderer*>(mRenderer)->MixInColor(mObjects[*iter]->Color());
		mObjects[*iter]->Render(proj_mat, view_mat);
		++iter;
	}
}

unsigned int LaserCannon::Fire()
{
	float elapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastShotTime).count();
	if (elapsed > mCooldownTime && !mGunOverHeated)
	{
		mLastShotTime = std::chrono::high_resolution_clock::now();
		mCurrentGunTemp += mShotTemp;
		return Alloc();
	}
#ifdef ENGINE_DEBUG
	else if (mGunOverHeated)
	{
		DebugMessage("Gun is overheated. Current temp is: " + boost::lexical_cast<std::string>(mCurrentGunTemp));
		return NOT_INDEX;
	}
#endif
	else
	{
		return NOT_INDEX;
	}
}

bool LaserCannon::operator<(const LaserCannon& other) const
{
	return mTransform < other.GetTransform();
}

const Transform& LaserCannon::GetTransform() const
{
	return mTransform;
}

Transform& LaserCannon::GetTransform()
{
	return mTransform;
}

void LaserCannon::ProjectileSpeed(const float& speed)
{
	mProjectileSpeed = speed;
}

void LaserCannon::CooldownTime(const float& cooldown_time)
{
	mCooldownTime = cooldown_time;
}

void LaserCannon::LaserTermYPos(const float& ypos)
{
	mLaserTermYPos = ypos;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->TerminateYPos(ypos);
	}
}

void LaserCannon::OverheatCooldownTime(const float& t)
{
	mOverheatCooldownTime = t;
}

const float& LaserCannon::LaserTermYPos() const
{
	return mLaserTermYPos;
}

const float& LaserCannon::ProjectileSpeed() const
{
	return mProjectileSpeed;
}

const float& LaserCannon::CooldownTime() const
{
	return mCooldownTime;
}

const float& LaserCannon::OverheatCooldownTime() const
{
	return mOverheatCooldownTime;
}

const float& LaserCannon::CurrentGunTemp() const
{
	return mCurrentGunTemp;
}

const float& LaserCannon::MaxGunTemp() const
{
	return mMaxGunTemp;
}

bool LaserCannon::GunOverHeated() const
{
	return mGunOverHeated;
}

void LaserCannon::CustomAllocOps(const unsigned int& index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	Laser* object = mObjects[index];
	object->Spawn(mTransform);
	object->Scale(0.50f);
	object->Scale(glm::vec3(1.0f, 2.0f, 1.0f));
	float gun_temp_ratio = mCurrentGunTemp / mMaxGunTemp;
#ifdef LASER_CANNON_DEBUG
	DebugMessage("gun_time_ratio = " + boost::lexical_cast<std::string>(gun_temp_ratio));
#endif
	object->Color(glm::vec4(gun_temp_ratio, 1.0f - gun_temp_ratio, gun_temp_ratio / 3.0f, 1.0f));
}

void LaserCannon::CustomDeallocOps(const unsigned int& index)
{

}

void LaserCannon::CustomInitOps()
{
	mRenderer = new TexRenderer(mShaderProg, GL_FILL);
	mCollider = new Collider();
	reinterpret_cast<TexRenderer*>(mRenderer)->UseMixInColor(true);
}

void LaserCannon::CustomUpdateOps(const float& dt)
{
#ifdef ENGINE_DEBUG
	static int counter = 25;
	++counter;
	if (counter >= 25)
	{
		DebugMessage("Current Gun Temp: " + boost::lexical_cast<std::string>(mCurrentGunTemp));
		counter = 0;
	}
	
#endif
	if (mMaxGunTemp <= mCurrentGunTemp)
	{
		mGunOverHeated = true;
	} else if (mGunOverHeated && mCurrentGunTemp <= mCoolDownTemp)
	{
		mGunOverHeated = false;
	}
	if (mCurrentGunTemp > 0)
	{
		mCurrentGunTemp -= mCoolDownStepTemp * dt;
		if (mCurrentGunTemp < 0)
		{
			mCurrentGunTemp = 0;
		}
	}
}

Laser* LaserCannon::ConstructObject()
{
	Laser* new_obj = new Laser();
	new_obj->AddRenderer(mRenderer);
	new_obj->AddDrawableObject(mShape);
	new_obj->AddCollider(new Collider());
	new_obj->TerminateYPos(mLaserTermYPos);
	new_obj->AddObserver(this);
#ifdef COLLISION_DEBUG
	Shape* circle = new Shape();
	CircleData* circle_data = new CircleData();
	circle->Buffer(circle_data);
	new_obj->AddDrawableObject(circle);
#endif
	return new_obj;
}

void LaserCannon::Scale(const float& scale)
{
	mTransform.Scale(scale);
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Scale(scale*0.6f);
	}
}

void LaserCannon::ScaleLasers(const glm::vec3& scale)
{
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Scale(scale);
	}
}




void LaserCannon::Translate(const glm::vec3& translation)
{
	mTransform.Translate(translation);
}