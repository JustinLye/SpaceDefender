#ifndef SCORE_TEXT_HEADER_INCLUDED
#define SCORE_TEXT_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"engine/objects/Text.h"

namespace sd_app {
namespace game {
namespace impl {
namespace score_text {
using event_t = engine::constants::types::event_t;

using GameObject = engine::objects::GameObject;
using Text = engine::objects::Text;

/** @addtogroup GameWorld */
/*@{*/

class ScoreText :
  public Text {
public:
  ScoreText();
  ~ScoreText();
  virtual void OnNotify(const GameObject&, const event_t&) override;
protected:
  unsigned int mPoints;
};
/*@}*/
} // namespace score_text
} // namespace impl
using ScoreText = impl::score_text::ScoreText;
} // namespace game
} // namespace sd_app


#endif