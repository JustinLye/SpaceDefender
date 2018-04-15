#include"game/LaserCannon.h"

LaserCannon::LaserCannon(Shape* laser, ShaderProgram* shader) :
	ObjectManager<Laser>(),
	mTransform(Transform()),
	mShape(laser),
	mShaderProg(shader),
	mRenderer(nullptr),
	mCollider(nullptr),
	mProjectileSpeed(20.0f),
	mCooldownTime(0.0f),
	mLastShotTime(std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(1000000))
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
	return 10;
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
	float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLastShotTime).count();
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
	object->Match(mTransform);
	object->Scale(0.40f);
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
	new_obj->AddShape(mShape);
	new_obj->AddCollider(mCollider);
	new_obj->TerminateYPos(1000.0f);
	return new_obj;
}