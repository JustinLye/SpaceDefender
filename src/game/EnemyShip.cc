#include"game/EnemyShip.h"

EnemyShip::EnemyShip() :
	GameObject(),
	mSpeed(0.0f),
	mHitPoints(1),
	mTerminateYPos(0.0f),
	mFront(glm::vec3(0.0f))
{
	std::string p(LogFilePath("EnemyShip.log"));
	mLogger = new Logger(p.c_str());
	mLogger->Launch();
}

EnemyShip::EnemyShip(const EnemyShip& other) :
	GameObject(other),
	mSpeed(other.mSpeed),
	mHitPoints(other.mHitPoints),
	mTerminateYPos(other.mTerminateYPos),
	mFront(other.mFront)
{

}

EnemyShip::~EnemyShip()
{

}

object_t EnemyShip::Type() const
{
	return object_t::ENEMY_SHIP;
}

void EnemyShip::Update(const float& dt)
{
	if (mRigidBody != nullptr)
	{
		if (mTracker != nullptr)
		{
			ProximityScan();
			
			size_t count = mCloseObjects.size();
			if (count > 0)
			{
				mLogger->Log(std::string("----------------- EnemyShip [") + boost::lexical_cast<std::string>(Id()) + std::string("] proximity scan results ---------------"));
				mLogger->Log(boost::lexical_cast<std::string>(count) + std::string(" objects detected."));
			}
			std::string pos_str = Vec3ToString(mTransform.Position());
			for (index_t i = 0; i < (index_t)count; ++i)
			{
				mLogger->Log(TypeToString(mCloseObjects[i]->Type()) + std::string(" object detected at ") + std::string(static_cast<std::string>(mCloseObjects[i]->GetTransform())) + std::string(" with distance of ") + boost::lexical_cast<std::string>(glm::distance(mTransform.Position(), mCloseObjects[i]->GetTransform().Position())) + std::string(" from ") + static_cast<std::string>(mTransform) + std::string(" with angle of ") + boost::lexical_cast<std::string>(glm::angle(mTransform.Rotation())) + std::string(" id is ") + boost::lexical_cast<std::string>(mCloseObjects[i]->Id()));
			}
			if (count > 0)
			{
				float x_pos = mCloseObjects[0]->Position().x;
				float scale = mCloseObjects[0]->Scale().x;
				float rot_angle = 0.0f;
				float inv_angle = 1.0f;
				glm::vec3 new_pos = mTransform.Position();
				if (x_pos > mTransform.Position().x)
				{
					new_pos.x -= (scale / 2.0f);
					inv_angle = -1.0f;
				}
				else
				{
					new_pos.x += (scale / 2.0f);
				}
				rot_angle = VecToVecAngle(mTransform.Position(), new_pos);
				Rotate(inv_angle*rot_angle, glm::vec3(0.0f, 0.0f, 1.0f));
				double angle = inv_angle * glm::angle(mTransform.Rotation());
				mFront.x = mUp.x * std::cos(angle) - mUp.y * std::sin(angle);
				mFront.y = mUp.x * std::sin(angle) + mUp.y * std::cos(angle);
				mRigidBody->Force(glm::vec3(mFront.x*mSpeed*5.0f, mFront.y*mSpeed*5.0f, 0.0f));
				mRigidBody->Update(dt);
				Translate(mRigidBody->Velocity());
				
				return;
			}
		}

		
		double angle = glm::angle(mTransform.Rotation());
		if (angle > PI)
		{
			angle *= -1;
		}
		mFront.x = mUp.x * std::cos(angle) - mUp.y * std::sin(angle);
		mFront.y = mUp.x * std::sin(angle) + mUp.y * std::cos(angle);
		mRigidBody->Force(glm::vec3(mFront.x*mSpeed, mFront.y*mSpeed, 0.0f));
		mRigidBody->Update(dt);
		/*if (std::abs(mRigidBody->Force().y) <= 0.0f)
		{
			
		}*/
		Translate(mRigidBody->Velocity());
	}
	else
	{
		Translate(glm::vec3(0.0f, mSpeed, 0.0f) * -dt);
	}
}

void EnemyShip::Collide(const GameObject& object) const
{
	switch (object.Type())
	{
	case object_t::LASER:
		ReportCollision(); // Will notify manager. Manager should update hitpoints, etc. as needed.
		if (mHitPoints <= 0)
		{
			Despawn();
		}
		break;
	}
}

bool EnemyShip::Terminate() const
{
	return mTransform.Position().y < mTerminateYPos;
}

void EnemyShip::Despawn() const
{
	if (mColliderMap.size() > 0)
	{
		Notify(*this, event_t::TERMINATED_COLLIDABLE_OBJECT);
	}
	if (mHitPoints <= 0)
	{
		Notify(*this, event_t::PLAYER_DESTROYED_ENEMY_SHIP);
	}
	else
	{
		Notify(*this, event_t::OBJECT_OUT_OF_BOUNDS);
	}
	Notify(*this, event_t::DESPAWNED_OBJECT);
}

const float& EnemyShip::Speed() const
{
	return mSpeed;
}

const int& EnemyShip::HitPoints() const
{
	return mHitPoints;
}

const float& EnemyShip::TerminateYPos() const
{
	return mTerminateYPos;
}

const glm::vec3& EnemyShip::Up() const
{
	return mUp;
}

void EnemyShip::Speed(const float& speed)
{
	mSpeed = speed;
}

void EnemyShip::HitPoints(const int& hp)
{
	mHitPoints = hp;
}

void EnemyShip::TerminateYPos(const float& pos)
{
	mTerminateYPos = pos;
}

void EnemyShip::Up(const glm::vec3& up)
{
	mUp = up;
}

void EnemyShip::AddActiveObjectTracker(const ActiveObjectTracker* tracker)
{
	mTracker = tracker;
}

void EnemyShip::ProximityScan()
{
	assert(mTracker != nullptr);

	//Get objects near the ship
	Transform detection_space = mTransform;
	detection_space.Scale(2.0f);
	mTracker->ObjectScan(detection_space, mCloseObjects);
	//mTracker->ObjectScan(detection_space, mCloseObjects, { object_t::ENEMY_SHIP }, false);

	// Remove this game object
	std::vector<const GameObject*>::iterator iter = mCloseObjects.begin();
	std::vector<const GameObject*>::iterator end_iter = mCloseObjects.end();

	while (iter != end_iter)
	{
		const GameObject* temp = *iter;
		if (Id() == temp->Id())
		{
			mLogger->Log("removing this enemy ship");
			iter = mCloseObjects.erase(iter);
			break;
		}
		++iter;
	}

	//Return if no objects in close proximity
	if (mCloseObjects.empty())
	{
		return;
	}

	//Store objects by distance
	std::vector<DistanceEntry> dist_vec;
	size_t close_obj_count = mCloseObjects.size();

	for (index_t i = 0; i < (index_t)close_obj_count; ++i)
	{
		dist_vec.push_back({ i, glm::distance(mTransform.Position(), mCloseObjects[i]->GetTransform().Position()) });
	}

	std::sort(dist_vec.begin(), dist_vec.end(), std::less<DistanceEntry>());

	//Put mCloseObjects in order by distance
	for (index_t i = 0; i < (index_t)close_obj_count; ++i)
	{
		index_t idx = dist_vec[i].mIndex;
		if (idx != i)
		{
			const GameObject* temp = mCloseObjects[i];
			mCloseObjects[i] = mCloseObjects[idx];
			mCloseObjects[idx] = temp;
		}
	}

}