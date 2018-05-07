#include"game/ExplosionManager.h"

ExplosionManager::ExplosionManager(DrawableObject* explosion, ShaderProgram* shader) :
	Subject(),
	Observer(),
	ObjectManager<Explosion>(),
	mTransform(Transform()),
	mShape(explosion),
	mShaderProg(shader),
	mSpeed(0.0f),
	mMaxExpansion(0.0f),
	mInitScale(1.0f)
{
	Init();
}

ExplosionManager::~ExplosionManager()
{

}

int ExplosionManager::MaxCapacity()
{
	return 15;
}

int ExplosionManager::MaxActiveCapacity()
{
	return 15;
}

void ExplosionManager::OnNotify(const GameObject& object, const event_t& event_name)
{
	switch (event_name)
	{
	case event_t::TERMINATED_COLLIDABLE_OBJECT:
		if (object.Type() == object_t::LASER)
		{
			mTransform.Match(object.GetTransform());
			Alloc();
		}
		break;
	}
}

void ExplosionManager::AddObserver(Observer* observer)
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

void ExplosionManager::RemoveObserver(Observer* observer)
{
	mObserverMap.erase(observer->Id());
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->RemoveObserver(observer);
	}
}

void ExplosionManager::ExpansionSpeed(const float& speed)
{
	mSpeed = speed;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Speed(mSpeed);
	}
}

void ExplosionManager::MaxExpansion(const float& max)
{
	mMaxExpansion = max;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->MaxScale(max);
	}
}

void ExplosionManager::InitScale(const float& scale)
{
	mInitScale = scale;
}

const float& ExplosionManager::ExpansionSpeed() const
{
	return mSpeed;
}

const float& ExplosionManager::MaxExpansion() const
{
	return mMaxExpansion;
}

const float& ExplosionManager::InitScale() const
{
	return mInitScale;
}

Explosion* ExplosionManager::ConstructObject()
{
	Explosion* object = new Explosion();
	object->AddRenderer(mRenderer);
	object->AddDrawableObject(mShape);
	object->Scale(mInitScale);
	object->Speed(mSpeed);
	object->MaxScale(mMaxExpansion);
	object->AddObserver(this);
	return object;
}

void ExplosionManager::CustomAllocOps(const unsigned int& index)
{
	if (index == NOT_INDEX)
	{
		return;
	}

	Explosion* object = mObjects[index];
	object->Spawn(mTransform);
	if (object->Scale().x > 0)
	{
		// set scale to 1
		object->Scale((1.0f / object->Scale().x));
		// set init scale
		object->Scale(mInitScale);
	}
	object->Translate(glm::vec3(0.0f, 0.0f, 0.50f));
	
}

void ExplosionManager::CustomInitOps()
{
	mRenderer = new TexRenderer(mShaderProg, GL_FILL);
}

bool ExplosionManager::DestructionPred(Explosion* object) const
{
	return object->Terminate();
}