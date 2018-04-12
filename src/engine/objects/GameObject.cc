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

void GameObject::AddShape(Shape* shape)
{
	auto shape_ptr = mShapeMap.find(shape);
	if (shape_ptr == mShapeMap.end())
	{
		std::pair<Shape*, Transform> p(shape, Transform());
		p.second.Translate(mTransformData.mPosition);
		p.second.Scale(mTransformData.mScale);
		p.second.Rotation(mTransformData.mRotation);
		mShapeMap.insert(p);
	}
}

void GameObject::RemoveShape(Shape* shape)
{
	auto shape_ptr = mShapeMap.find(shape);
	if (shape_ptr != mShapeMap.end())
	{
		mShapeMap.erase(shape);
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

bool GameObject::operator()(const Shape* lhs, const Shape* rhs)
{
	return *lhs < *rhs;
}