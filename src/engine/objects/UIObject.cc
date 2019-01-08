#include"engine/objects/UIObject.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace ui_object {
UIObject::UIObject() :
	Observer()
{

}

UIObject::~UIObject()
{

}

void UIObject::OnNotify(const GameObject& object, const event_t& event_name)
{

}
} // namespace ui_object
} // namespace impl
} // namespace objects
} // namespace engine
} // namespace sd_app