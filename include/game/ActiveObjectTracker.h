#ifndef ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
#define ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED

#include<vector>
#include<set>
#include"engine/objects/Observer.h"
#include"engine/objects/GameObject.h"
#include"engine/util/UtiliDefs.h"
#include"engine/util/Logger.h"

using namespace Constants::Types;

/** @addtogroup GameWorld */
/*@{*/
class ActiveObjectTracker :
	public Observer
{
public:
	ActiveObjectTracker();
	~ActiveObjectTracker();

	void OnNotify(const GameObject&, const event_t&);
	const std::vector<const GameObject*>& GetActiveObjectsList() const;
	std::vector<const GameObject*> ObjectScan(const Transform&, const Transform&) const;
	std::vector<const GameObject*> ObjectScan(const Transform&) const;
	void ObjectScan(const Transform&, std::vector<const GameObject*>&) const;
	void ObjectScan(const Transform&, std::vector<const GameObject*>&, const std::set<object_t>&, bool = false) const;
protected:
	std::vector<const GameObject*> mGameObjectList;
	Logger* mLogger;

};
/*@}*/
#endif // !ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
