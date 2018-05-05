#include"game/LaserCannon.h"

LaserCannon::LaserCannon(Shape* laser, ShaderProgram* shader) :
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
	mLaserTermYPos(0.0f)

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
	return 5;
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
	if (ObserverIsMapped(observer))
	{
		mObserverMap.insert({ observer->Id(), observer });
	}
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

unsigned int LaserCannon::Fire()
{
	float elapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastShotTime).count();
	if (elapsed > mCooldownTime)
	{
		mLastShotTime = std::chrono::high_resolution_clock::now();
		return Alloc();
	}
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

void LaserCannon::CustomAllocOps(const unsigned int& index)
{
	if (index == NOT_INDEX)
	{
		return;
	}
	Laser* object = mObjects[index];
	object->Spawn(mTransform);
	object->Scale(0.40f);
}

void LaserCannon::CustomDeallocOps(const unsigned int& index)
{

}

void LaserCannon::CustomInitOps()
{
	mRenderer = new Renderer(mShaderProg, GL_LINE);
	mCollider = new Collider();
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

void LaserCannon::Translate(const glm::vec3& translation)
{
	mTransform.Translate(translation);
}