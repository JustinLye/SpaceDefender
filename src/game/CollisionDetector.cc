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
		std::map<unsigned int, const Astroid*>::const_iterator astroid_iter = mAstroidMap.cbegin();

		while (astroid_iter != mAstroidMap.cend())
		{
			
			collision_detected = laser_iter->second->CollisionDetected(*astroid_iter->second);
			if (collision_detected)
			{
				break;
			}
			++astroid_iter;
		}
		if (collision_detected)
		{
			laser_iter->second->Collide(*astroid_iter->second);
			astroid_iter->second->Collide(*laser_iter->second);
			laser_iter = mLaserMap.erase(laser_iter);
			if (astroid_iter->second->HitPoints() <= 0)
			{
				astroid_iter = mAstroidMap.erase(astroid_iter);
			}
		}
		else
		{
			++laser_iter;
		}
	}
	std::map<unsigned int, const Astroid*>::const_iterator curr_astroid_iter = mAstroidMap.cbegin();
	while (curr_astroid_iter != mAstroidMap.cend())
	{
		bool collision_detected = false;
		std::map<unsigned int, const Astroid*>::const_iterator astroid_iter = curr_astroid_iter;
		astroid_iter++;
		while (astroid_iter != mAstroidMap.cend())
		{
			collision_detected = curr_astroid_iter->second->CollisionDetected(*astroid_iter->second);
			if (collision_detected)
			{
				break;
			}
			++astroid_iter;
		}
		if (collision_detected)
		{
			curr_astroid_iter->second->Collide(*astroid_iter->second);
			astroid_iter->second->Collide(*curr_astroid_iter->second);
		}
		++curr_astroid_iter;
	}
}

void CollisionDetector::OnNotify(const GameObject& object, const Constants::Types::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::Types::event_t::ACTIVATED_COLLIDABLE_OBJECT:
		if (object.Type() == Constants::Types::object_t::ASTROID)
		{
			mAstroidMap.insert({ object.Id(), reinterpret_cast<const Astroid*>(&object) });
		}
		else if (object.Type() == Constants::Types::object_t::LASER)
		{
			mLaserMap.insert({ object.Id(), reinterpret_cast<const Laser*>(&object) });
		}
		break;
	case Constants::Types::event_t::OBJECT_OUT_OF_BOUNDS:
		if (object.Type() == Constants::Types::object_t::ASTROID)
		{
			mAstroidMap.erase(object.Id());
		}
		else if (object.Type() == Constants::Types::object_t::LASER)
		{
			mLaserMap.erase(object.Id());
		}
	}
}