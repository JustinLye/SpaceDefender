#include"game/ExplosionManager.h"

ExplosionManager::ExplosionManager(DrawableObject* explosion, ShaderProgram* shader) :
	Subject(),
	Observer(),
	ObjectManager<Explosion>(),
	mTransform(Transform()),
	mShape(explosion),
	mShaderProg(shader),
	mSpeed(0.0f),
	mInitScale(1.0f),
	mGen(mRd()),
	mExpansionDist(0.0f, 0.0f)
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
			//mTransform.Match(object.GetTransform());
			mTransform.Translate(object.Position() - mTransform.Position());
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

void ExplosionManager::ExpansionSpeed(float speed)
{
	mSpeed = speed;
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i]->Speed(mSpeed);
	}
}

void ExplosionManager::MinExpansion(float min)
{
	mExpansionDist.param(std::uniform_real_distribution<>::param_type((double)min, mExpansionDist.max()));
}

void ExplosionManager::MaxExpansion(float max)
{
	mExpansionDist.param(std::uniform_real_distribution<>::param_type(mExpansionDist.min(), (double)max));
}



void ExplosionManager::InitScale(float scale)
{
	mInitScale = scale;
}

float ExplosionManager::ExpansionSpeed() const
{
	return mSpeed;
}

float ExplosionManager::MinExpansion() const
{
	return (float)mExpansionDist.min();
}

float ExplosionManager::MaxExpansion() const
{
	return (float)mExpansionDist.max();
}

float ExplosionManager::InitScale() const
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
	object->MaxScale(mExpansionDist(mGen));
	object->AddObserver(this);
	return object;
}

void ExplosionManager::CustomAllocOps(unsigned int index)
{
	if (index == NOT_INDEX)
	{
		return;
	}

	Explosion* object = mObjects[index];
	object->Spawn(mTransform);
	object->MaxScale(mExpansionDist(mGen));
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
	mRenderer = new TexRenderer(mShaderProg, { GL_FILL, GL_FILL });
}

bool ExplosionManager::DestructionPred(Explosion* object) const
{
	return object->Terminate();
}