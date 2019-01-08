#ifndef ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
#define ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED

#include<vector>
#include<set>
#include"engine/objects/Observer.h"
#include"engine/objects/GameObject.h"
#include"engine/util/UtiliDefs.h"
#include"engine/util/Logger.h"


namespace sd_app {
namespace game {
namespace impl {
namespace active_object_tracker {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
using Observer = engine::objects::Observer;
using Transform = engine::objects::Transform;
using GameObject = engine::objects::GameObject;
using Logger = engine::util::Logger;

/** @addtogroup GameWorld */
/*@{*/
class ActiveObjectTracker :
  public Observer {
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
} // namespace active_object_tracker
} // namespace impl
using ActiveObjectTracker = impl::active_object_tracker::ActiveObjectTracker;
} // namespace game
} // namespace sd_app


#endif // !ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
