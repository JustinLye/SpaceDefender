#include"engine/objects/GameObject.h"

unsigned int GameObject::NextObjectId = 0;

GameObject::GameObject() :
	mTransform(Transform()),
	mRenderer(nullptr),
	mId(++NextObjectId)
{

};

GameObject::~GameObject()
{
}

const unsigned int& GameObject::Id() const
{
	return mId;
}

void GameObject::Match(const Transform& transform)
{
	mTransform.Match(transform);
	MatchShapes(transform);
	MatchColliders(transform);
	MatchGameObjects(transform);
}

void GameObject::MatchShapes(const Transform& transform)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Match(transform);
		++iter;
	}
}

void GameObject::MatchColliders(const Transform& transform)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Match(transform);
		++iter;
	}
}

void GameObject::MatchGameObjects(const Transform& transform)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Match(transform);
		++iter;
	}
}

const Transform& GameObject::GetTransform() const
{
	return mTransform;
}

void GameObject::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	RenderShapes(proj_mat, view_mat);
	RenderGameObjects(proj_mat, view_mat);
}

void GameObject::Render(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, Shape* shape)
{
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	auto shape_ptr = GetShape(shape);
	mRenderer->Render(shape_ptr->first, glm::value_ptr(projection_matrix*view_matrix*shape_ptr->second.Model()));
}

void GameObject::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat, GameObject* object)
{
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	auto object_ptr = GetGameObject(object);
	object_ptr->second->Render(proj_mat, view_mat);
}

void GameObject::AddShape(Shape* shape)
{
	if (!ShapeIsMapped(shape))
	{
		std::pair<Shape*, Transform> p(shape, Transform());
		p.second.Translate(mTransform.Position());
		p.second.Scale(mTransform.Scale().x);
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
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Update(dt);
		++iter;
	}
}

void GameObject::AddRenderer(Renderer* renderer)
{
//#ifdef ENGINE_DEBUG
//	assert(mRenderer == nullptr);
//#endif
	mRenderer = renderer;
}

// SCALING OPS

void GameObject::Scale(const float& scale)
{
	mTransform.Scale(scale);
	ScaleShapes(scale);
	ScaleColliders(scale);
	ScaleObjects(scale);
}

void GameObject::Scale(const float& scale, Shape* shape)
{
	GetShape(shape)->second.Scale(scale);
}

void GameObject::Scale(const float& scale, Collider* collider)
{
	GetCollider(collider)->second->Scale(scale);
}

void GameObject::Scale(const float& scale, GameObject* object)
{
	GetGameObject(object)->second->Scale(scale);
}

const glm::vec3& GameObject::Scale() const
{
	return mTransform.Scale();
}

const glm::vec3& GameObject::Scale(Shape* shape) const
{
	return GetShape(shape)->second.Scale();
}

const glm::vec3& GameObject::Scale(Collider* collider) const
{
	return GetCollider(collider)->second->Scale();
}

const glm::vec3& GameObject::Scale(GameObject* object) const
{
	return GetGameObject(object)->second->Scale();
}

// TRANSLATE OPS
void GameObject::Translate(const glm::vec3& translation)
{
	mTransform.Translate(translation);
	TranslateShapes(translation);
	TranslateColliders(translation);
	TranslateObjects(translation);
}

void GameObject::Translate(const glm::vec3& translation, Shape* shape) 
{
	GetShape(shape)->second.Translate(translation);
}

void GameObject::Translate(const glm::vec3& translation, Collider* collider)
{
	GetCollider(collider)->second->Translate(translation);
}

void GameObject::Translate(const glm::vec3& translation, GameObject* object)
{
	GetGameObject(object)->second->Translate(translation);
}

const glm::vec3& GameObject::Position() const
{
	return mTransform.Position();
}

const glm::vec3& GameObject::Position(Shape* shape) const
{
	return GetShape(shape)->second.Position();
}

const glm::vec3& GameObject::Position(Collider* collider) const
{
	return GetCollider(collider)->second->Position();
}

const glm::vec3& GameObject::Position(GameObject* object) const
{
	return GetGameObject(object)->second->Position();
}

// ROTATION OPS

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	mTransform.Rotate(angle_degrees, rotation_axis);
	RotateShapes(angle_degrees, rotation_axis);
	RotateColliders(angle_degrees, rotation_axis);
	RotateObjects(angle_degrees, rotation_axis);
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis, Shape* shape)
{
	GetShape(shape)->second.Rotate(angle_degrees, rotation_axis);
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis, Collider* collider)
{
	GetCollider(collider)->second->Rotate(angle_degrees, rotation_axis);
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis, GameObject* object)
{
	GetGameObject(object)->second->Rotate(angle_degrees, rotation_axis);
}

void GameObject::Rotation(const glm::quat& copy_quat)
{
	mTransform.Rotation(copy_quat);
	RotationShapes(copy_quat);
	RotationColliders(copy_quat);
	RotationObjects(copy_quat);
}

void GameObject::Rotation(const glm::quat& copy_quat, Shape* shape)
{
	GetShape(shape)->second.Rotation(copy_quat);
}

void GameObject::Rotation(const glm::quat& copy_quat, Collider* collider)
{
	GetCollider(collider)->second->Rotation(copy_quat);
}

void GameObject::Rotation(const glm::quat& copy_quat, GameObject* object)
{
	GetGameObject(object)->second->Rotation(copy_quat);
}

const glm::quat& GameObject::Rotation() const
{
	return mTransform.Rotation();
}

const glm::quat& GameObject::Rotation(Shape* shape) const
{
	return GetShape(shape)->second.Rotation();
}

const glm::quat& GameObject::Rotation(Collider* collider) const
{
	return GetCollider(collider)->second->Rotation();
}

const glm::quat& GameObject::Rotation(GameObject* object) const
{
	return GetGameObject(object)->second->Rotation();
}

// OFFSET OPS

void GameObject::Offset(const glm::vec3& offset_vec)
{
	mTransform.Offset(offset_vec);
	OffsetShapes(offset_vec);
	OffsetColliders(offset_vec);
	OffsetObjects(offset_vec);
}

void GameObject::Offset(const glm::vec3& offset_vec, Shape* shape_ptr)
{
	GetShape(shape_ptr)->second.Offset(offset_vec);
}

void GameObject::Offset(const glm::vec3& offset_vec, Collider* collider_ptr)
{
	GetCollider(collider_ptr)->second->Offset(offset_vec);
}

void GameObject::Offset(const glm::vec3& offset_vec, GameObject* object)
{
	GetGameObject(object)->second->Offset(offset_vec);
}

const glm::vec3& GameObject::Offset() const
{
	return mTransform.Offset();
}

const glm::vec3& GameObject::Offset(Shape* shape_ptr) const
{
	return GetShape(shape_ptr)->second.Offset();
}

const glm::vec3& GameObject::Offset(Collider* collider_ptr) const
{
	return GetCollider(collider_ptr)->second->Offset();
}

const glm::vec3& GameObject::Offset(GameObject* object) const
{
	return GetGameObject(object)->second->Offset();
}

glm::mat4 GameObject::Model()
{
	return mTransform.Model();
}

glm::mat4 GameObject::Model(Shape* shape)
{
	return GetShape(shape)->second.Model();
}

glm::mat4 GameObject::Model(Collider* collider)
{
	return GetCollider(collider)->second->Model();
}

glm::mat4 GameObject::Model(GameObject* object)
{
	return GetGameObject(object)->second->Model();
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

void GameObject::AddCollider(Collider* collider)
{
	if (!ColliderIsMapped(collider))
	{
		mColliderMap.insert({ collider, collider });
	}
}

void GameObject::RemoveCollider(Collider* collider)
{
	mColliderMap.erase(collider);
}

void GameObject::AddGameObject(GameObject* object)
{
	if (!ObjectIsMapped(object))
	{
		mGameObjectMap.insert({ object, object });
	}
}

void GameObject::RemoveGameObject(GameObject* object)
{
	mGameObjectMap.erase(object);
}

void GameObject::ScaleShapes(const float& scale)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Scale(scale);
		++iter;
	}
}

void GameObject::ScaleColliders(const float& scale)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Scale(scale);
		++iter;
	}
}

void GameObject::ScaleObjects(const float& scale)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Scale(scale);
		++iter;
	}
}

void GameObject::TranslateShapes(const glm::vec3& translation)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Translate(translation);
		++iter;
	}
}

void GameObject::TranslateColliders(const glm::vec3& translation)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Translate(translation);
		++iter;
	}
}

void GameObject::TranslateObjects(const glm::vec3& translation)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Translate(translation);
		++iter;
	}
}

void GameObject::RotateShapes(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Rotate(angle_degrees, rotation_axis);
		++iter;
	}
}

void GameObject::RotateColliders(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Rotate(angle_degrees, rotation_axis);
		++iter;
	}
}

void GameObject::RotateObjects(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Rotate(angle_degrees, rotation_axis);
		++iter;
	}
}

void GameObject::RotationShapes(const glm::quat& rotation)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Rotation(rotation);
		++iter;
	}
}

void GameObject::RotationColliders(const glm::quat& rotation)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Rotation(rotation);
		++iter;
	}
}

void GameObject::RotationObjects(const glm::quat& rotation)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Rotation(rotation);
		++iter;
	}
}

void GameObject::OffsetShapes(const glm::vec3& offset_vec)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		iter->second.Offset(offset_vec);
		++iter;
	}
}

void GameObject::OffsetColliders(const glm::vec3& offset_vec)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Offset(offset_vec);
		++iter;
	}
}

void GameObject::OffsetObjects(const glm::vec3& offset_vec)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Offset(offset_vec);
		++iter;
	}
}

void GameObject::RenderShapes(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	std::map<Shape*, Transform, CompareShapePtr>::iterator iter = mShapeMap.begin();
	while (iter != mShapeMap.end())
	{
		mRenderer->Render(iter->first, glm::value_ptr(proj_mat * view_mat * iter->second.Model()));
		++iter;
	}
}

void GameObject::RenderGameObjects(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Render(proj_mat, view_mat);
		++iter;
	}
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

std::map<Collider*, Collider*, GameObject::CompareTransPtr>::iterator GameObject::GetCollider(Collider* collider)
{
	auto result = mColliderMap.find(collider);
#ifdef ENGINE_DEBUG
	assert(result != mColliderMap.end());
#endif
	return result;
}

std::map<Collider*, Collider*, GameObject::CompareTransPtr>::const_iterator GameObject::GetCollider(Collider* collider) const
{
	auto result = mColliderMap.find(collider);
#ifdef ENGINE_DEBUG
	assert(result != mColliderMap.cend());
#endif
	return result;
}

std::map<GameObject*, GameObject*, GameObject::CompareGameObjectPtr>::iterator GameObject::GetGameObject(GameObject* object)
{
	auto result = mGameObjectMap.find(object);
#ifdef ENGINE_DEBUG
	assert(result != mGameObjectMap.end());
#endif
	return result;
}

std::map<GameObject*, GameObject*, GameObject::CompareGameObjectPtr>::const_iterator GameObject::GetGameObject(GameObject* object) const
{
	auto result = mGameObjectMap.find(object);
#ifdef ENGINE_DEBUG
	assert(result != mGameObjectMap.cend());
#endif
	return result;
}

bool GameObject::ShapeIsMapped(Shape* shape) const
{
	return (mShapeMap.find(shape) != mShapeMap.cend());
}

bool GameObject::ColliderIsMapped(Collider* collider) const
{
	return (mColliderMap.find(collider) != mColliderMap.cend());
}

bool GameObject::ObjectIsMapped(GameObject* object) const
{
	return (mGameObjectMap.find(object) != mGameObjectMap.cend());
}

bool GameObject::operator<(const GameObject& other) const
{
	return mId < other.Id();
}

bool GameObject::operator==(const GameObject& other) const
{
	return mId == other.Id();
}