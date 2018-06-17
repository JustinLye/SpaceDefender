#include"game/ActiveObjectTracker.h"

ActiveObjectTracker::ActiveObjectTracker() :
	Observer()
{
	std::string p = LogFilePath("active-obj-tracker.log");
	mLogger = new Logger(p.c_str());
	mLogger->Launch();
}

ActiveObjectTracker::~ActiveObjectTracker()
{

}

void ActiveObjectTracker::OnNotify(const GameObject& obj, const event_t& event_name)
{
	std::string str;
	mLogger->Log("notified by object type " + TypeToString(obj.Type()) + std::string(" id ") + boost::lexical_cast<std::string>(obj.Id()) + std::string(" event num ") + boost::lexical_cast<std::string>(event_name));
	switch (event_name)
	{
	case event_t::SPAWNED_OBJECT:
		mLogger->Log("event type is spawned object");
		switch (obj.Type())
		{
		case object_t::ASTEROID:
		case object_t::ENEMY_SHIP:
			mLogger->Log(std::string("Adding ") + TypeToString(obj.Type()) + " to object list");
			mGameObjectList.push_back(&obj);
			break;
		}
		break;
	case event_t::DESPAWNED_OBJECT:
		std::vector<const GameObject*>::iterator iter = mGameObjectList.begin();
		while (iter != mGameObjectList.end())
		{
			if (*(*iter) == obj)
			{
				mLogger->Log(std::string("Removing ") + TypeToString(obj.Type()) + std::string(" id ") + boost::lexical_cast<std::string>((*iter)->Id()) + std::string(" from object list"));
				iter = mGameObjectList.erase(iter);
				break;
			}
			++iter;
		}
		if (iter == mGameObjectList.end())
		{
			mLogger->Log("Object not found!!");
		}
		break;
	}
	
}

const std::vector<const GameObject*>& ActiveObjectTracker::GetActiveObjectsList() const
{
	return mGameObjectList;
}

std::vector<const GameObject*> ActiveObjectTracker::ObjectScan(const Transform& origin, const Transform& dest) const
{
	// Translate toward destination in increments of origin.scale
	std::vector<const GameObject*> result;
	std::vector<const GameObject*> temp = mGameObjectList;
	Transform current_pos = origin;
	glm::vec3 translate_increment = (dest.Position() - origin.Position()) / origin.Scale();
	while (!Collider::CollisionDetected(current_pos, dest) && !temp.empty())
	{
		std::vector<const GameObject*>::const_iterator iter = temp.begin();
		while (iter != temp.end())
		{
			if (Collider::CollisionDetected(current_pos, (*iter)->GetTransform()))
			{
				result.push_back(*iter);
				iter = temp.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		current_pos.Translate(translate_increment);
	}
	return result;
}

std::vector<const GameObject*> ActiveObjectTracker::ObjectScan(const Transform& origin) const
{
	std::vector<const GameObject*> result;
	std::vector<const GameObject*>::const_iterator iter = mGameObjectList.cbegin();
	std::vector<const GameObject*>::const_iterator end_iter = mGameObjectList.cend();
	while (iter != end_iter)
	{
		if (Collider::CollisionDetected(origin, (*iter)->GetTransform()))
		{
			result.push_back(*iter);
		}
		++iter;
	}
	return result;
}

void ActiveObjectTracker::ObjectScan(const Transform& origin, std::vector<const GameObject*>& obj_vec) const
{
	obj_vec.clear();
	std::vector<const GameObject*>::const_iterator iter = mGameObjectList.cbegin();
	std::vector<const GameObject*>::const_iterator end_iter = mGameObjectList.cend();
	while (iter != end_iter)
	{
		if (Collider::CollisionDetected(origin, (*iter)->GetTransform()))
		{
			obj_vec.push_back(*iter);
		}
		++iter;
	}
}

void ActiveObjectTracker::ObjectScan(const Transform& origin, std::vector<const GameObject*>& obj_vec, const std::set<Constants::Types::object_t>& type_set, bool inclusion) const
{
	obj_vec.clear();
	std::vector<const GameObject*>::const_iterator iter = mGameObjectList.cbegin();
	std::vector<const GameObject*>::const_iterator end_iter = mGameObjectList.cend();
	while (iter != end_iter)
	{
		if (Collider::CollisionDetected(origin, (*iter)->GetTransform()))
		{
			std::set<object_t>::const_iterator type_iter = type_set.find((*iter)->Type());
			if (inclusion && type_iter != type_set.cend())
			{
				obj_vec.push_back(*iter);
			}
			else if (!inclusion && type_iter == type_set.cend())
			{
				obj_vec.push_back(*iter);
			}
		}
		++iter;
	}
}