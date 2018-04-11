#include"engine/objects/GameObject.h"

GameObject::GameObject() :
	Transform(),
	mRenderer(nullptr)
{

};

GameObject::~GameObject()
{
}

void GameObject::Render(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
#ifdef ENGINE_DEBUG
	assert(mRenderer != nullptr);
#endif
	try
	{
		mRenderer->Render(glm::value_ptr(projection_matrix*view_matrix*Model()));
	}
	catch (std::exception& error)
	{
		throw std::runtime_error(std::string("Render failure: ") + error.what());
	}
}

void GameObject::Update(const float& dt)
{

}

void GameObject::AddRenderer(std::unique_ptr<Renderer> renderer)
{
//#ifdef ENGINE_DEBUG
//	assert(mRenderer == nullptr);
//#endif
	mRenderer = std::move(renderer);
}

void GameObject::PolyMode(const GLenum& poly_mode)
{
#ifdef ENGINE_DEBUG
	assert(mRenderer != nullptr);
#endif
	mRenderer->PolyMode(poly_mode);
}

const GLenum& GameObject::PolyMode() const
{
#ifdef ENGINE_DEBUG
	assert(mRenderer != nullptr);
#endif
	return mRenderer->PolyMode();
}