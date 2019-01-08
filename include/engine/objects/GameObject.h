#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED

#include"engine/objects/Renderer.h"
#include"engine/objects/Collider.h"
#include"engine/objects/RigidBody.h"
#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include"engine/objects/DrawableObject.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace game_object {
using namespace constants::physics;
using event_t = constants::types::event_t;
using object_t = constants::types::object_t;
using OpenGLPolyMode = util::OpenGLPolyMode;
class Subject;
/** @addtogroup EngineObjects */
/*@{*/
class GameObject :
  public Subject {
public:

  struct CompareDrawObjPtr {
    bool operator()(const DrawableObject* lhs, const DrawableObject* rhs) const {
      return *lhs < *rhs;
    }
  };
  struct CompareTransPtr {
    bool operator()(const Transform* lhs, const Transform* rhs) const {
      return *lhs < *rhs;
    }
  };
  struct CompareGameObjectPtr {
    bool operator()(const GameObject* lhs, const GameObject* rhs) const {
      return *lhs < *rhs;
    }
  };

  GameObject();
  GameObject(const GameObject&);
  GameObject(GameObject&&);
  virtual ~GameObject();

  const unsigned int& Id() const;
  virtual object_t Type() const;
  virtual void Collide(const GameObject&) const;
  virtual void Update(float);
  virtual void AddRenderer(Renderer*);
  virtual void AddRigidBody(RigidBody*);
  virtual void Match(const Transform&);
  virtual void MatchShapes(const Transform&);
  virtual void MatchColliders(const Transform&);
  virtual void MatchGameObjects(const Transform&);

  void Mass(float);
  void Force(const glm::vec3&);
  void Damping(float);

  float Mass() const;
  float InverseMass() const;
  const glm::vec3& Force() const;
  float Damping() const;
  const glm::vec3& Velocity() const;
  const glm::vec3& Acceleration() const;



  // Transform Interface and individual Shape/Collider/GameObject tranforms
  const Transform& GetTransform() const;
  virtual void JumpToPosition(const Transform&);
  virtual void JumpToPosition(const glm::vec3&);
  virtual void Scale(float);
  virtual void ResetScale();
  virtual void Scale(float, DrawableObject*);
  virtual void Scale(float, Collider*);
  virtual void Scale(float, GameObject*);
  virtual void Scale(const glm::vec3&);
  const glm::vec3& Scale() const;
  const glm::vec3& Scale(DrawableObject*) const;
  const glm::vec3& Scale(Collider*) const;
  const glm::vec3& Scale(GameObject*) const;
  virtual void Translate(const glm::vec3&);
  virtual void Translate(const glm::vec3&, DrawableObject*);
  virtual void Translate(const glm::vec3&, Collider*);
  virtual void Translate(const glm::vec3&, GameObject*);
  const glm::vec3& Position() const;
  const glm::vec3& Position(DrawableObject*) const;
  const glm::vec3& Position(Collider*) const;
  const glm::vec3& Position(GameObject*) const;
  virtual void Rotate(float, const glm::vec3&);
  virtual void Rotate(float, const glm::vec3&, DrawableObject*);
  virtual void Rotate(float, const glm::vec3&, Collider*);
  virtual void Rotate(float, const glm::vec3&, GameObject*);
  virtual void Rotation(const glm::quat&);
  virtual void Rotation(const glm::quat&, DrawableObject*);
  virtual void Rotation(const glm::quat&, Collider*);
  virtual void Rotation(const glm::quat&, GameObject*);
  const glm::quat& Rotation() const;
  const glm::quat& Rotation(DrawableObject*) const;
  const glm::quat& Rotation(Collider*) const;
  const glm::quat& Rotation(GameObject*) const;
  virtual void Offset(const glm::vec3&);
  virtual void Offset(const glm::vec3&, DrawableObject*);
  virtual void Offset(const glm::vec3&, Collider*);
  virtual void Offset(const glm::vec3&, GameObject*);
  const glm::vec3& Offset() const;
  const glm::vec3& Offset(DrawableObject*) const;
  const glm::vec3& Offset(Collider*) const;
  const glm::vec3& Offset(GameObject*) const;
  glm::mat4 Model();
  glm::mat4 Model(DrawableObject*);
  glm::mat4 Model(Collider*);
  glm::mat4 Model(GameObject*);
  // Shape Interface
  virtual void AddDrawableObject(DrawableObject*);
  virtual void RemoveDrawableObject(DrawableObject*);

  // Renderer Interface
  virtual void Render(const glm::mat4&, const glm::mat4&);
  virtual void Render(const glm::mat4&, const glm::mat4&, DrawableObject*);
  virtual void Render(const glm::mat4&, const glm::mat4&, GameObject*);

  virtual void PolyMode(const OpenGLPolyMode::face_t&, const GLenum&);
  GLenum PolyMode(const OpenGLPolyMode::face_t&) const;

  // Collider Interface
  virtual void AddCollider(Collider*);
  virtual void RemoveCollider(Collider*);

  // Object Iterface
  virtual void AddGameObject(GameObject*);
  virtual void RemoveGameObject(GameObject*);

  virtual void Spawn(const Transform&);
  virtual void Despawn() const;
  virtual void OutOfBounds() const;

  virtual bool CollisionDetected(const Collider*) const;
  virtual bool CollisionDetected(const GameObject&) const;

  typedef std::map<Collider*, Collider*, CompareTransPtr>::const_iterator const_collider_iter;
  std::pair<const_collider_iter, const_collider_iter> GetColliders() const;

  void ResetRigidBody();

  // Operators
  bool operator<(const GameObject&) const;
  bool operator==(const GameObject&) const;
  GameObject& operator=(const GameObject&);

protected:
  Transform mTransform;
  Renderer* mRenderer;
  RigidBody* mRigidBody;
  std::map<DrawableObject*, Transform, CompareDrawObjPtr> mDrawableObjectMap;
  std::map<Collider*, Collider*, CompareTransPtr> mColliderMap;
  std::map<GameObject*, GameObject*, CompareGameObjectPtr> mGameObjectMap;

  virtual void ScaleDrawableObjects(float);
  virtual void ScaleDrawableObjects(const glm::vec3&);
  virtual void ScaleColliders(float);
  virtual void ScaleColliders(const glm::vec3&);
  virtual void ScaleObjects(float);
  virtual void ScaleObjects(const glm::vec3&);
  virtual void ResetScaleOnDrawableObjects();
  virtual void ResetScaleOnColliders();
  virtual void ResetScaleOnObjects();
  virtual void TranslateDrawableObjects(const glm::vec3&);
  virtual void TranslateColliders(const glm::vec3&);
  virtual void TranslateObjects(const glm::vec3&);
  virtual void RotateDrawableObjects(float, const glm::vec3&);
  virtual void RotateColliders(float, const glm::vec3&);
  virtual void RotateObjects(float, const glm::vec3&);
  virtual void RotationDrawableObjects(const glm::quat&);
  virtual void RotationColliders(const glm::quat&);
  virtual void RotationObjects(const glm::quat&);
  virtual void OffsetDrawableObjects(const glm::vec3&);
  virtual void OffsetColliders(const glm::vec3&);
  virtual void OffsetObjects(const glm::vec3&);

  virtual void CustomScaleActions(float) {}
  virtual void CustomScaleActions(float, DrawableObject*) {}
  virtual void CustomScaleActions(const glm::vec3&) {}
  virtual void CustomTranslateActions(const glm::vec3&) {}

  virtual void JumpToPositionOnDrawableObjects(const glm::vec3&);
  virtual void JumpToPositionOnColliders(const glm::vec3&);
  virtual void JumpToPositionOnObjects(const glm::vec3&);


  virtual void RenderDrawableObjects(const glm::mat4&, const glm::mat4&);
  virtual void RenderGameObjects(const glm::mat4&, const glm::mat4&);

  std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator GetDrawableObject(DrawableObject*);
  std::map<DrawableObject*, Transform, CompareDrawObjPtr>::const_iterator GetDrawableObject(DrawableObject*) const;
  std::map<Collider*, Collider*, CompareTransPtr>::iterator GetCollider(Collider*);
  std::map<Collider*, Collider*, CompareTransPtr>::const_iterator GetCollider(Collider*) const;
  std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator GetGameObject(GameObject*);
  std::map<GameObject*, GameObject*, CompareGameObjectPtr>::const_iterator GetGameObject(GameObject*) const;

  bool DrawableObjectIsMapped(DrawableObject*) const;
  bool ColliderIsMapped(Collider*) const;
  bool ObjectIsMapped(GameObject*) const;

  void ReportCollision() const;

private:
  static unsigned int NextObjectId;
  unsigned int mId;

};

/*@}*/

} // namespace game_object
} // namespace impl
using GameObject = impl::game_object::GameObject;
} // namespace objects
} // namespace engine
} // namespace sd_app

#include"engine/objects/Subject.h"

#endif

