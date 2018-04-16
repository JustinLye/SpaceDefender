#include"game/CollisionDetector.h"

CollisionDetector::CollisionDetector() :
	Subject(),
	Observer()
{

}

CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::DoDetection(GameObject* object)
{
	std::map<unsigned int, const Astroid*>::iterator iter = mAstroidMap.begin();

	while (iter != mAstroidMap.end())
	{
		auto colliders = iter->second->GetColliders();
		auto current_collider = colliders.first;
		bool collision_detected = false;
		while (current_collider != colliders.second)
		{
			if (object->CollisionDetected(current_collider->second))
			{
				object->Despawn();
				Notify(*iter->second, Constants::event_t::TERMINATED_COLLIDABLE_OBJECT);
				iter = mAstroidMap.erase(iter);
				collision_detected = true;
				break;
			}
			++current_collider;
		}
		if (!collision_detected)
		{
			++iter;
		}
	}
}

void CollisionDetector::OnNotify(const GameObject& object, const Constants::event_t& event_name)
{
	switch (event_name)
	{
	case Constants::event_t::ACTIVATED_COLLIDABLE_OBJECT:
		mAstroidMap.insert({ object.Id(), reinterpret_cast<const Astroid*>(&object) });
		break;
	}
}