#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED


#include"engine/objects/Renderer.h"
#include"engine/objects/Collider.h"

#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(const float&);
	virtual void AddRenderer(std::unique_ptr<Renderer>);

	// Transform Interface and individual Shape/Collider tranforms
	virtual void Scale(const float&);
	virtual void Scale(const float&, Shape*);
	virtual void Scale(const float&, Collider*);
	const glm::vec3& Scale() const;
	const glm::vec3& Scale(Shape*) const;
	const glm::vec3& Scale(Collider*) const;
	virtual void Translate(const glm::vec3&);
	virtual void Translate(const glm::vec3&, Shape*);
	virtual void Translate(const glm::vec3&, Collider*);
	const glm::vec3& Position() const;
	const glm::vec3& Position(Shape*) const;
	const glm::vec3& Position(Collider*) const;
	virtual void Rotate(const float&, const glm::vec3&);
	virtual void Rotate(const float&, const glm::vec3&, Shape*);
	virtual void Rotate(const float&, const glm::vec3&, Collider*);
	virtual void Rotation(const glm::quat&);
	virtual void Rotation(const glm::quat&, Shape*);
	virtual void Rotation(const glm::quat&, Collider*);
	const glm::quat& Rotation() const;
	const glm::quat& Rotation(Shape*) const;
	const glm::quat& Rotation(Collider*) const;
	virtual void Offset(const glm::vec3&);
	virtual void Offset(const glm::vec3&, Shape*);
	virtual void Offset(const glm::vec3&, Collider*);
	const glm::vec3& Offset() const;
	const glm::vec3& Offset(Shape*) const;
	const glm::vec3& Offset(Collider*) const;
	 glm::mat4 Model();
	 glm::mat4 Model(Shape*);
	 glm::mat4 Model(Collider*);

	// Shape Interface
	virtual void AddShape(Shape*);
	virtual void RemoveShape(Shape*);

	// Renderer Interface
	virtual void Render(const glm::mat4&, const glm::mat4&, Shape* = nullptr);
	virtual void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;

	// Collider Interface
	virtual void AddCollider(Collider*);
	virtual void RemoveCollider(Collider*);


protected:
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
	Transform mTransform;
	std::unique_ptr<Renderer> mRenderer;
	std::map<Shape*, Transform, CompareShapePtr> mShapeMap;
	std::map<Collider*, Collider*, CompareTransPtr> mColliderMap;

	virtual void ScaleShapes(const float&);
	virtual void ScaleColliders(const float&);
	virtual void TranslateShapes(const glm::vec3&);
	virtual void TranslateColliders(const glm::vec3&);
	virtual void RotateShapes(const float&, const glm::vec3&);
	virtual void RotateColliders(const float&, const glm::vec3&);
	virtual void RotationShapes(const glm::quat&);
	virtual void RotationColliders(const glm::quat&);
	virtual void OffsetShapes(const glm::vec3&);
	virtual void OffsetColliders(const glm::vec3&);
	std::map<Shape*, Transform, CompareShapePtr>::iterator GetShape(Shape*);
	std::map<Shape*, Transform, CompareShapePtr>::const_iterator GetShape(Shape*) const;
	std::map<Collider*, Collider*, CompareTransPtr>::iterator GetCollider(Collider*);
	std::map<Collider*, Collider*, CompareTransPtr>::const_iterator GetCollider(Collider*) const;
	bool ShapeIsMapped(Shape*) const;
	bool ColliderIsMapped(Collider*) const;
	

	
};

#endif

