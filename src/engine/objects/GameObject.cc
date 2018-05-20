#include"engine/objects/GameObject.h"

unsigned int GameObject::NextObjectId = 0;

GameObject::GameObject() :
	Subject(),
	mTransform(Transform()),
	mRenderer(nullptr),
	mRigidBody(nullptr),
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

const Constants::Types::object_t& GameObject::Type() const
{
	return Constants::Types::object_t::GENERIC_OBJECT;
}

void GameObject::Collide(const GameObject& object) const
{

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
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::Mass(const float& mass)
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	mRigidBody->Mass(mass);
}

void GameObject::Force(const glm::vec3& force)
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	mRigidBody->Force(force);
}

void GameObject::Damping(const float& damping)
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	mRigidBody->Damping(damping);
}

const float& GameObject::Mass() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->Mass();
}

const float& GameObject::InverseMass() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->InverseMass();
}

const glm::vec3& GameObject::Force() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->Force();
}

const float& GameObject::Damping() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->Damping();
}

const glm::vec3& GameObject::Velocity() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->Velocity();
}

const glm::vec3& GameObject::Acceleration() const
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	return mRigidBody->Acceleration();
}

const Transform& GameObject::GetTransform() const
{
	return mTransform;
}

void GameObject::JumpToPosition(const Transform& transform)
{
	JumpToPosition(transform.Position());
}

void GameObject::JumpToPosition(const glm::vec3& pos)
{
	mTransform.JumpToPosition(pos);
	JumpToPositionOnDrawableObjects(pos);
	JumpToPositionOnColliders(pos);
	JumpToPositionOnObjects(pos);
}

void GameObject::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	RenderGameObjects(proj_mat, view_mat);
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	RenderDrawableObjects(proj_mat, view_mat);
	
}

void GameObject::Render(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, DrawableObject* object)
{
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	auto shape_ptr = GetDrawableObject(object);
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

void GameObject::AddDrawableObject(DrawableObject* object)
{
	if (!DrawableObjectIsMapped(object))
	{
		std::pair<DrawableObject*, Transform> p(object, Transform());
		p.second.Translate(mTransform.Position());
		p.second.Scale(mTransform.Scale().x);
		p.second.Rotation(mTransform.Rotation());
		mDrawableObjectMap.insert(p);
	}
}

void GameObject::RemoveDrawableObject(DrawableObject* object)
{
	if (DrawableObjectIsMapped(object))
	{
		mDrawableObjectMap.erase(object);
	}
}


void GameObject::Update(const float& dt)
{
	if (mRigidBody != nullptr)
	{
		mRigidBody->Update(dt);
		Translate(mRigidBody->Velocity());
	}
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

void GameObject::AddRigidBody(RigidBody* rb)
{
	mRigidBody = rb;
}

// SCALING OPS

void GameObject::Scale(const float& scale)
{
	mTransform.Scale(scale);
	ScaleDrawableObjects(scale);
	ScaleColliders(scale);
	ScaleObjects(scale);
	CustomScaleActions(scale);
}

void GameObject::ResetScale()
{
	mTransform.ResetScale();
	ResetScaleOnDrawableObjects();
	ResetScaleOnColliders();
	ResetScaleOnObjects();
}

void GameObject::Scale(const float& scale, DrawableObject* object)
{
	GetDrawableObject(object)->second.Scale(scale);
}

void GameObject::Scale(const float& scale, Collider* collider)
{
	GetCollider(collider)->second->Scale(scale);
}

void GameObject::Scale(const float& scale, GameObject* object)
{
	GetGameObject(object)->second->Scale(scale);
}

void GameObject::Scale(const glm::vec3& scale)
{
	mTransform.Scale(scale);
	ScaleDrawableObjects(scale);
	ScaleColliders(scale);
	ScaleObjects(scale);
	CustomScaleActions(scale);
}

const glm::vec3& GameObject::Scale() const
{
	return mTransform.Scale();
}

const glm::vec3& GameObject::Scale(DrawableObject* object) const
{
	return GetDrawableObject(object)->second.Scale();
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
	TranslateDrawableObjects(translation);
	TranslateColliders(translation);
	TranslateObjects(translation);
	CustomTranslateActions(translation);
}

void GameObject::Translate(const glm::vec3& translation, DrawableObject* object) 
{
	GetDrawableObject(object)->second.Translate(translation);
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

const glm::vec3& GameObject::Position(DrawableObject* object) const
{
	return GetDrawableObject(object)->second.Position();
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
	RotateDrawableObjects(angle_degrees, rotation_axis);
	RotateColliders(angle_degrees, rotation_axis);
	RotateObjects(angle_degrees, rotation_axis);
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis, DrawableObject* object)
{
	GetDrawableObject(object)->second.Rotate(angle_degrees, rotation_axis);
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
	RotationDrawableObjects(copy_quat);
	RotationColliders(copy_quat);
	RotationObjects(copy_quat);
}

void GameObject::Rotation(const glm::quat& copy_quat, DrawableObject* object)
{
	GetDrawableObject(object)->second.Rotation(copy_quat);
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

const glm::quat& GameObject::Rotation(DrawableObject* object) const
{
	return GetDrawableObject(object)->second.Rotation();
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
	OffsetDrawableObjects(offset_vec);
	OffsetColliders(offset_vec);
	OffsetObjects(offset_vec);
}

void GameObject::Offset(const glm::vec3& offset_vec, DrawableObject* object)
{
	GetDrawableObject(object)->second.Offset(offset_vec);
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

const glm::vec3& GameObject::Offset(DrawableObject* object) const
{
	return GetDrawableObject(object)->second.Offset();
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

glm::mat4 GameObject::Model(DrawableObject* object)
{
	return GetDrawableObject(object)->second.Model();
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

void GameObject::Spawn(const Transform& transform)
{
	Match(transform);
	if (mColliderMap.size() > 0)
	{
		Notify(*this, Constants::Types::event_t::ACTIVATED_COLLIDABLE_OBJECT);
	}
}

void GameObject::Despawn() const
{
#ifdef COLLISION_DEBUG
	std::cout << __FUNCTION__ << '\n';
#endif
	if (mColliderMap.size() > 0)
	{
		Notify(*this, Constants::Types::event_t::TERMINATED_COLLIDABLE_OBJECT);
	}
}

void GameObject::OutOfBounds() const
{
#ifdef COLLISION_DEBUG
	std::cout << __FUNCTION__ << '\n';
#endif
	Notify(*this, Constants::Types::event_t::OBJECT_OUT_OF_BOUNDS);
}

bool GameObject::CollisionDetected(const Collider* collider) const
{
	std::map<Collider*, Collider*, CompareTransPtr>::const_iterator iter = mColliderMap.cbegin();
	bool result = false;
	while (iter != mColliderMap.end())
	{
		result = iter->second->CollisionDetected(*collider);
		if (result)
		{
			break;
		}
		++iter;
	}
	return result;
}

bool GameObject::CollisionDetected(const GameObject& object) const
{
	auto object_colliders = object.GetColliders();
	auto current_collider = object_colliders.first;
	while (current_collider != object_colliders.second)
	{
		if (CollisionDetected(current_collider->second))
		{
			return true;
		}
		++current_collider;
	}
	return false;
}

std::pair<GameObject::const_collider_iter, GameObject::const_collider_iter> GameObject::GetColliders() const
{
	return std::pair<const_collider_iter, const_collider_iter>(mColliderMap.cbegin(), mColliderMap.cend());
}

void GameObject::ScaleDrawableObjects(const float& scale)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
	{
		iter->second.Scale(scale);
		++iter;
	}
}

void GameObject::ScaleDrawableObjects(const glm::vec3& scale)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::ScaleColliders(const glm::vec3& scale)
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

void GameObject::ScaleObjects(const glm::vec3& scale)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->Scale(scale);
		++iter;
	}
}

void GameObject::ResetScaleOnDrawableObjects()
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
	{
		iter->second.ResetScale();
		++iter;
	}
}

void GameObject::ResetScaleOnColliders()
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->ResetScale();
		++iter;
	}
}

void GameObject::ResetScaleOnObjects()
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->ResetScale();
		++iter;
	}
}

void GameObject::TranslateDrawableObjects(const glm::vec3& translation)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::RotateDrawableObjects(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::RotationDrawableObjects(const glm::quat& rotation)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::OffsetDrawableObjects(const glm::vec3& offset_vec)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

void GameObject::JumpToPositionOnDrawableObjects(const glm::vec3& pos)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
	{
		iter->second.Offset(pos);
		++iter;
	}
}

void GameObject::JumpToPositionOnColliders(const glm::vec3& pos)
{
	std::map<Collider*, Collider*, CompareTransPtr>::iterator iter = mColliderMap.begin();
	while (iter != mColliderMap.end())
	{
		iter->second->Offset(pos);
		++iter;
	}
}

void GameObject::JumpToPositionOnObjects(const glm::vec3& pos)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	while (iter != mGameObjectMap.end())
	{
		iter->second->JumpToPosition(pos);
		++iter;
	}
}

void GameObject::RenderDrawableObjects(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	std::map<DrawableObject*, Transform, CompareDrawObjPtr>::iterator iter = mDrawableObjectMap.begin();
	while (iter != mDrawableObjectMap.end())
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

std::map<DrawableObject*, Transform, GameObject::CompareDrawObjPtr>::iterator GameObject::GetDrawableObject(DrawableObject* shape)
{
	auto result = mDrawableObjectMap.find(shape);
#ifdef ENGINE_DEBUG
	assert(result != mDrawableObjectMap.end());
#endif
	return result;
}

std::map<DrawableObject*, Transform, GameObject::CompareDrawObjPtr>::const_iterator GameObject::GetDrawableObject(DrawableObject* shape) const
{
	auto result = mDrawableObjectMap.find(shape);
#ifdef ENGINE_DEBUG
	assert(result != mDrawableObjectMap.cend());
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

bool GameObject::DrawableObjectIsMapped(DrawableObject* object) const
{
	return (mDrawableObjectMap.find(object) != mDrawableObjectMap.cend());
}

bool GameObject::ColliderIsMapped(Collider* collider) const
{
	return (mColliderMap.find(collider) != mColliderMap.cend());
}

bool GameObject::ObjectIsMapped(GameObject* object) const
{
	return (mGameObjectMap.find(object) != mGameObjectMap.cend());
}

void GameObject::ReportCollision() const
{
	Notify(*this, Constants::Types::event_t::COLLISION_REPORTED);
}

void GameObject::ResetRigidBody()
{
#ifdef ENGINE_DEBUG
	assert(mRigidBody != nullptr);
#endif
	mRigidBody->Reset();
}

bool GameObject::operator<(const GameObject& other) const
{
	return mId < other.Id();
}

bool GameObject::operator==(const GameObject& other) const
{
	return mId == other.Id();
}