#ifndef SCROLLING_BACKGROUND_HEADER_INCLUDED
#define SCROLLING_BACKGROUND_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace scrolling_background {
/** @addtogroup EngineObjects */
/*@{*/

class ScrollingBackground :
  protected GameObject {
public:
  using GameObject::Render;

  ScrollingBackground();
  ~ScrollingBackground();
  void Update(float) override;
  void AddBackground(GameObject*);

  void ScrollSpeed(float);
  void MaxYOffset(float);
  void StartingPosition(const Transform&);

  float ScrollSpeed() const;
  float MaxYOffset() const;
  const Transform& StartingPosition() const;

protected:
  glm::vec3 mScrollOffsetVec;
  float mMaxYOffset;
  Transform mStartingPosition;
};

/*@}*/
} // namespace scrolling_background
} // namespace impl
using ScrollingBackground = impl::scrolling_background::ScrollingBackground;
} // namespace objects
} // namespace engine
} // namespace sd_app



#endif // !SCROLLING_BACKGROUND_HEADER_INCLUDED
