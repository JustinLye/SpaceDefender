#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED


#include"engine/objects/Renderer.h"
#include"engine/objects/Collider.h"
#include"engine/objects/Subject.h"
#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

class GameObject :
	public Subject
{
public:

	struct CompareShapePtr
	{
		bool operator()(const Shape* lhs, const Shape* rhs) const
		{
			return *lhs < *rhs;
		}
	};
	struct CompareTransPtr
	{
		bool operator()(const Transform* lhs, const Transform* rhs) const
		{
			return *lhs < *rhs;
		}
	};
	struct CompareGameObjectPtr
	{
		bool operator()(const GameObject* lhs, const GameObject* rhs) const
		{
			return *lhs < *rhs;
		}
	};

	GameObject();
	virtual ~GameObject();

	const unsigned int& Id() const;
	virtual const Constants::Types::object_t& Type() const;
	virtual void Collide(const GameObject&) const;
	virtual void Update(const float&);
	virtual void AddRenderer(Renderer*);

	virtual void Match(const Transform&);
	virtual void MatchShapes(const Transform&);
	virtual void MatchColliders(const Transform&);
	virtual void MatchGameObjects(const Transform&);
	
	const Transform& GetTransform() const;

	// Transform Interface and individual Shape/Collider/GameObject tranforms
	virtual void Scale(const float&);
	virtual void Scale(const float&, Shape*);
	virtual void Scale(const float&, Collider*);
	virtual void Scale(const float&, GameObject*);
	const glm::vec3& Scale() const;
	const glm::vec3& Scale(Shape*) const;
	const glm::vec3& Scale(Collider*) const;
	const glm::vec3& Scale(GameObject*) const;
	virtual void Translate(const glm::vec3&);
	virtual void Translate(const glm::vec3&, Shape*);
	virtual void Translate(const glm::vec3&, Collider*);
	virtual void Translate(const glm::vec3&, GameObject*);
	const glm::vec3& Position() const;
	const glm::vec3& Position(Shape*) const;
	const glm::vec3& Position(Collider*) const;
	const glm::vec3& Position(GameObject*) const;
	virtual void Rotate(const float&, const glm::vec3&);
	virtual void Rotate(const float&, const glm::vec3&, Shape*);
	virtual void Rotate(const float&, const glm::vec3&, Collider*);
	virtual void Rotate(const float&, const glm::vec3&, GameObject*);
	virtual void Rotation(const glm::quat&);
	virtual void Rotation(const glm::quat&, Shape*);
	virtual void Rotation(const glm::quat&, Collider*);
	virtual void Rotation(const glm::quat&, GameObject*);
	const glm::quat& Rotation() const;
	const glm::quat& Rotation(Shape*) const;
	const glm::quat& Rotation(Collider*) const;
	const glm::quat& Rotation(GameObject*) const;
	virtual void Offset(const glm::vec3&);
	virtual void Offset(const glm::vec3&, Shape*);
	virtual void Offset(const glm::vec3&, Collider*);
	virtual void Offset(const glm::vec3&, GameObject*);
	const glm::vec3& Offset() const;
	const glm::vec3& Offset(Shape*) const;
	const glm::vec3& Offset(Collider*) const;
	const glm::vec3& Offset(GameObject*) const;
	 glm::mat4 Model();
	 glm::mat4 Model(Shape*);
	 glm::mat4 Model(Collider*);
	 glm::mat4 Model(GameObject*);
	// Shape Interface
	virtual void AddShape(Shape*);
	virtual void RemoveShape(Shape*);

	// Renderer Interface
	virtual void Render(const glm::mat4&, const glm::mat4&);
	virtual void Render(const glm::mat4&, const glm::mat4&, Shape*);
	virtual void Render(const glm::mat4&, const glm::mat4&, GameObject*);

	virtual void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;

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

	// Operators
	bool operator<(const GameObject&) const;
	bool operator==(const GameObject&) const;

protected:


	Transform mTransform;
	Renderer* mRenderer;
	std::map<Shape*, Transform, CompareShapePtr> mShapeMap;
	std::map<Collider*, Collider*, CompareTransPtr> mColliderMap;
	std::map<GameObject*, GameObject*, CompareGameObjectPtr> mGameObjectMap;

	virtual void ScaleShapes(const float&);
	virtual void ScaleColliders(const float&);
	virtual void ScaleObjects(const float&);
	virtual void TranslateShapes(const glm::vec3&);
	virtual void TranslateColliders(const glm::vec3&);
	virtual void TranslateObjects(const glm::vec3&);
	virtual void RotateShapes(const float&, const glm::vec3&);
	virtual void RotateColliders(const float&, const glm::vec3&);
	virtual void RotateObjects(const float&, const glm::vec3&);
	virtual void RotationShapes(const glm::quat&);
	virtual void RotationColliders(const glm::quat&);
	virtual void RotationObjects(const glm::quat&);
	virtual void OffsetShapes(const glm::vec3&);
	virtual void OffsetColliders(const glm::vec3&);
	virtual void OffsetObjects(const glm::vec3&);

	virtual void CustomScaleActions(const float&) {}
	virtual void CustomScaleActions(const float&, Shape*) {}

	virtual void CustomTranslateActions(const glm::vec3&) {}

	virtual void RenderShapes(const glm::mat4&, const glm::mat4&);
	virtual void RenderGameObjects(const glm::mat4&, const glm::mat4&);

	std::map<Shape*, Transform, CompareShapePtr>::iterator GetShape(Shape*);
	std::map<Shape*, Transform, CompareShapePtr>::const_iterator GetShape(Shape*) const;
	std::map<Collider*, Collider*, CompareTransPtr>::iterator GetCollider(Collider*);
	std::map<Collider*, Collider*, CompareTransPtr>::const_iterator GetCollider(Collider*) const;
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator GetGameObject(GameObject*);
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::const_iterator GetGameObject(GameObject*) const;

	bool ShapeIsMapped(Shape*) const;
	bool ColliderIsMapped(Collider*) const;
	bool ObjectIsMapped(GameObject*) const;

	void ReportCollision() const;

private:
	static unsigned int NextObjectId;
	unsigned int mId;
	
};

#endif

