#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED

#include"engine/objects/Renderer.h"
#include"engine/objects/Transform.h"

class GameObject :
	public Transform
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(const float&);
	virtual void AddRenderer(std::unique_ptr<Renderer>);

	// Renderer Interface
	virtual void Render(const glm::mat4&, const glm::mat4&);
	virtual void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;


protected:
	std::unique_ptr<Renderer> mRenderer;
};

#endif