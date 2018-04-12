#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED


#include"engine/objects/Renderer.h"
#include"engine/objects/Transform.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(const float&);
	virtual void AddRenderer(std::unique_ptr<Renderer>);

	// Transform Interface and individual shape tranforms
	virtual void Scale(const glm::vec3&, Shape* = nullptr);
	const glm::vec3& Scale(Shape* = nullptr) const;
	virtual void Translate(const glm::vec3&, Shape* = nullptr);
	const glm::vec3& Position(Shape* = nullptr) const;
	virtual void Rotate(const float&, const glm::vec3&, Shape* = nullptr);
	virtual void Rotation(const glm::quat&, Shape* = nullptr);
	const glm::quat& Rotation(Shape* = nullptr) const;
	glm::mat4 Model(Shape* = nullptr);

	// Shape Interface
	virtual void AddShape(Shape*);
	virtual void RemoveShape(Shape*);

	// Renderer Interface
	virtual void Render(const glm::mat4&, const glm::mat4&, Shape* = nullptr);
	virtual void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;


protected:
	struct CompareShapePtr
	{
		bool operator()(const Shape* lhs, const Shape* rhs) const
		{
			return *lhs < *rhs;
		}
	};
	Transform mTransform;
	std::map<Shape*, Transform, CompareShapePtr> mShapeMap;
	std::unique_ptr<Renderer> mRenderer;
	std::map<Shape*, Transform, CompareShapePtr>::iterator GetShape(Shape*);
	std::map<Shape*, Transform, CompareShapePtr>::const_iterator GetShape(Shape*) const;
	bool ShapeIsMapped(Shape*);
	bool operator()(const Shape*, const Shape*);
};

#endif

