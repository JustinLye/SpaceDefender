#include"engine/objects/GameObject.h"

GameObject::GameObject() :
	mTransform(Transform()),
	mRenderer(nullptr)
{

};

GameObject::~GameObject()
{
}

void GameObject::Render(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, Shape* shape)
{
#ifdef ENGINE_DEBUG
	assert(mRenderer != nullptr);
#endif
	try
	{
		if (shape == nullptr) /* if individual shape not specified, then render all shapes */
		{
			for (auto shape_ptr : mShapeMap)
			{
				mRenderer->Render(shape_ptr.first, glm::value_ptr(projection_matrix*view_matrix*shape_ptr.second.Model()));
			}
		}
		else
		{
			auto shape_ptr = GetShape(shape);
			mRenderer->Render(shape_ptr->first, glm::value_ptr(projection_matrix*view_matrix*shape_ptr->second.Model()));
		}
	}
	catch (std::exception& error)
	{
		throw std::runtime_error(std::string("Render failure: ") + error.what());
	}
}

void GameObject::AddShape(Shape* shape)
{
	if (!ShapeIsMapped(shape))
	{
		std::pair<Shape*, Transform> p(shape, Transform());
		p.second.Translate(mTransform.Position());
		p.second.Scale(mTransform.Scale());
		p.second.Rotation(mTransform.Rotation());
		mShapeMap.insert(p);
	}
}

void GameObject::RemoveShape(Shape* shape)
{
	if (ShapeIsMapped(shape))
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

void GameObject::Scale(const glm::vec3& scale, Shape* shape)
{
	if (!shape)
	{
		mTransform.Scale(scale);
		std::map<Shape*, Transform, CompareShapePtr>::iterator shape_ptr = mShapeMap.begin();
		while (shape_ptr != mShapeMap.end())
		{
			shape_ptr->second.Scale(scale);
			++shape_ptr;
		}
	}
	else
	{
		GetShape(shape)->second.Scale(scale);
	}
}

const glm::vec3& GameObject::Scale(Shape* shape) const
{
	if (shape)
	{
		return GetShape(shape)->second.Scale();
	}
	return mTransform.Scale();
}

void GameObject::Translate(const glm::vec3& translation, Shape* shape) 
{

	if (!shape)
	{
		mTransform.Translate(translation);
		std::map<Shape*, Transform, CompareShapePtr>::iterator shape_ptr = mShapeMap.begin();
		while (shape_ptr != mShapeMap.end())
		{
			shape_ptr->second.Translate(translation);
			++shape_ptr;
		}
	}
	else
	{
		GetShape(shape)->second.Translate(translation);
	}
}

const glm::vec3& GameObject::Position(Shape* shape) const
{
	if (shape)
	{
		return GetShape(shape)->second.Position();
	}
	return mTransform.Position();
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis, Shape* shape)
{
	if (!shape)
	{
		mTransform.Rotate(angle_degrees, rotation_axis);
		std::map<Shape*, Transform, CompareShapePtr>::iterator shape_ptr = mShapeMap.begin();
		while (shape_ptr != mShapeMap.end())
		{
			shape_ptr->second.Rotate(angle_degrees, rotation_axis);
			++shape_ptr;
		}
	}
	else
	{
		GetShape(shape)->second.Rotate(angle_degrees, rotation_axis);
	}
}

void GameObject::Rotation(const glm::quat& copy_quat, Shape* shape)
{
	if (shape)
	{
		GetShape(shape)->second.Rotation(copy_quat);
	}
	else
	{
		mTransform.Rotation(copy_quat);
	}
}

const glm::quat& GameObject::Rotation(Shape* shape) const
{
	if (shape)
	{
		return GetShape(shape)->second.Rotation();
	}
	return mTransform.Rotation();
}

glm::mat4 GameObject::Model(Shape* shape)
{
	if (shape)
	{
		return GetShape(shape)->second.Model();
	}
	return mTransform.Model();
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

std::map<Shape*, Transform, GameObject::CompareShapePtr>::iterator GameObject::GetShape(Shape* shape)
{
	auto result = mShapeMap.find(shape);
#ifdef ENGINE_DEBUG
	assert(result != mShapeMap.end());
#endif
	return result;
}

std::map<Shape*, Transform, GameObject::CompareShapePtr>::const_iterator GameObject::GetShape(Shape* shape) const
{
	auto result = mShapeMap.find(shape);
#ifdef ENGINE_DEBUG
	assert(result != mShapeMap.cend());
#endif
	return result;
}

bool GameObject::ShapeIsMapped(Shape* shape)
{
	return (mShapeMap.find(shape) != mShapeMap.end());
}

bool GameObject::operator()(const Shape* lhs, const Shape* rhs)
{
	return *lhs < *rhs;
}




