#ifndef BUTTON_HEADER_INCLUDED
#define BUTTON_HEADER_INCLUDED

#include"engine/shapes/Shape.h"
#include"engine/objects/Transform.h"
#include"engine/objects/Renderer.h"
#include"engine/objects/Subject.h"
#include"engine/objects/Text.h"
#include"engine/objects/UIObject.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace button {
using Shape = shapes::Shape;

/** @addtogroup EngineObjects */
/*@{*/
class Button :
  public UIObject {
public:
  Button();
  virtual ~Button();

  void Init();
  void Render();
  virtual void Clicked(float, float);
  virtual void Translate(const glm::vec3&);
  virtual void Scale(const glm::vec3&);
  void FillColor(const glm::vec4&);
  void TextColor(const glm::vec4&);
  void Projection(const glm::mat4&);
  void View(const glm::mat4&);
  void AddRenderer(Renderer*);
  void AddDrawableObject(Shape*);
  void AddText(Text*);

  glm::vec4 FillColor() const;
  glm::vec4 TextColor() const;

protected:
  Transform* mTransform;
  Shape* mShape;
  Text* mText;
  Renderer* mRenderer;
  glm::mat4 mProjMat;
  glm::mat4 mViewMat;

};
/*@}*/
} // namespace button
} // namespace impl
using Button = impl::button::Button;
} // namespace objects
} // namespace engine
} // namespace sd_app


#endif