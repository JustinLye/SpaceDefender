#include"game/CollisionDetector.h"

CollisionDetector::CollisionDetector() :
	Subject(),
	Observer()
{

}

CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::DoDetection(const float& dt)
{
	std::map<unsigned int, const Laser*>::const_iterator laser_iter = mLaserMap.cbegin();
	while (laser_iter != mLaserMap.cend())
	{
		bool collision_detected = false;
		std::map<unsigned int, const Asteroid*>::const_iterator asteroid_iter = mAsteroidMap.cbegin();

		while (asteroid_iter != mAsteroidMap.cend())
		{
			
			collision_detected = laser_iter->second->CollisionDetected(*asteroid_iter->second);
			if (collision_detected)
			{
				break;
			}
			++asteroid_iter;
		}
		if (collision_detected)
		{
			laser_iter->second->Collide(*asteroid_iter->second);
			asteroid_iter->second->Collide(*laser_iter->second);
			laser_iter = mLaserMap.erase(laser_iter);
			if (asteroid_iter->second->HitPoints() <= 0)
			{
				asteroid_iter = mAsteroidMap.erase(asteroid_iter);
			}
			continue;
		}

		std::map<unsigned int, const EnemyShip*>::const_iterator enemy_ship_iter = mEnemyShipMap.cbegin();
		while (enemy_ship_iter != mEnemyShipMap.cend())
		{
			collision_detected = laser_iter->second->CollisionDetected(*enemy_ship_iter->second);
			if (collision_detected)
			{
				break;
			}
			++enemy_ship_iter;
		}
		if (collision_detected)
		{
			laser_iter->second->Collide(*enemy_ship_iter->second);
			enemy_ship_iter->second->Collide(*laser_iter->second);
			laser_iter = mLaserMap.erase(laser_iter);
			if (enemy_ship_iter->second->HitPoints() <= 0)
			{
				enemy_ship_iter = mEnemyShipMap.erase(enemy_ship_iter);
			}
			continue;
		}
		++laser_iter;
	}

	std::map<unsigned int, const Asteroid*>::const_iterator curr_asteroid_iter = mAsteroidMap.cbegin();
	while (curr_asteroid_iter != mAsteroidMap.cend())
	{
		bool collision_detected = false;
		std::map<unsigned int, const Asteroid*>::const_iterator asteroid_iter = curr_asteroid_iter;
		asteroid_iter++;
		while (asteroid_iter != mAsteroidMap.cend())
		{
			collision_detected = curr_asteroid_iter->second->CollisionDetected(*asteroid_iter->second);
			if (collision_detected)
			{
				break;
			}
			++asteroid_iter;
		}
		if (collision_detected)
		{
			curr_asteroid_iter->second->Collide(*asteroid_iter->second);
			asteroid_iter->second->Collide(*curr_asteroid_iter->second);
		}
		++curr_asteroid_iter;
	}
}

void CollisionDetector::OnNotify(const GameObject& object, const Constants::Types::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::Types::event_t::ACTIVATED_COLLIDABLE_OBJECT:
		if (object.Type() == Constants::Types::object_t::ASTEROID)
		{
			mAsteroidMap.insert({ object.Id(), reinterpret_cast<const Asteroid*>(&object) });
		}
		else if (object.Type() == Constants::Types::object_t::LASER)
		{
			mLaserMap.insert({ object.Id(), reinterpret_cast<const Laser*>(&object) });
		}
		else if (object.Type() == object_t::ENEMY_SHIP)
		{
			mEnemyShipMap.insert({ object.Id(), reinterpret_cast<const EnemyShip*>(&object) });
		}
		break;
	case Constants::Types::event_t::OBJECT_OUT_OF_BOUNDS:
		DebugMessage("Object out-of-bounds notifcation");
		if (object.Type() == Constants::Types::object_t::ASTEROID)
		{
			mAsteroidMap.erase(object.Id());
		}
		else if (object.Type() == Constants::Types::object_t::LASER)
		{
			mLaserMap.erase(object.Id());
		}
		else if (object.Type() == object_t::ENEMY_SHIP)
		{
			mLaserMap.erase(object.Id());
		}
		break;
	}
}