#ifndef DRAWABLE_OBJECT_HEADER_INCLUDED
#define DRAWABLE_OBJECT_HEADER_INCLUDED

#include<glad/glad.h>

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace drawable_object {
/** @addtogroup EngineObjects */
/*@{*/
class DrawableObject {
public:
  DrawableObject();
  virtual ~DrawableObject();
  virtual void Draw() = 0;
  virtual void Activate();
  virtual void Deactivate();
  virtual const unsigned int& GetVAO() const;
  virtual unsigned int GetVAO();
  virtual bool operator<(const DrawableObject&) const;
  virtual bool operator==(const DrawableObject&) const;
protected:
  unsigned int mVaoId;
  virtual void CustomActivationSteps();
  virtual void CustomDeactivationSteps();
};
/*@}*/
} // namespace drawable_object
} // namespace impl
using DrawableObject = impl::drawable_object::DrawableObject;
} // namespace objects
} // namespace engine
} // namespace sd_app

#endif
