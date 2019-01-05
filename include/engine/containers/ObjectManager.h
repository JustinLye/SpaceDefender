#ifndef OBJECT_MANAGER_HEADER_INCLUDED
#define OBJECT_MANAGER_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<queue>
#include<list>
#include<glm/glm.hpp>
#include"engine/util/Constants.h"
#include"engine/containers/IndexQueue.h"
/** @addtogroup EngineObjectContainers */
/*@{*/
//////////////////////////////////////////////////
///\ class ObjectManager
///\ brief Provoides generic interface for object
///  managment
///
///  Assumes objects have update and render methods.
///  If you're using this container for objects
///  that do no have update and render methods, then
///  you will need to override the Update() and Render()
///  method to do nothing.
///
///\ author Justin Lye
///\ date 04/08/2018
//////////////////////////////////////////////////
template<class T>
class ObjectManager
{
public:

	static constexpr unsigned int NOT_INDEX = ~0;

	ObjectManager();
	virtual ~ObjectManager();

	unsigned int ActiveObjectCount() const;

	virtual int MaxCapacity() = 0;
	virtual int MaxActiveCapacity() = 0;

	virtual void Init();
	virtual void Destroy();

	virtual void Update(float);
	virtual void Render(const glm::mat4& = Constants::Geometry::IDENTITY_MATRIX, const glm::mat4& = Constants::Geometry::IDENTITY_MATRIX);

protected:
	int mMaxCapacity;
	int mMaxActiveCapacity;
	IndexQueue mIndexQueue;
	std::list<unsigned int> mActiveIndices;
	T** mObjects;

	virtual unsigned int Alloc();
	virtual T* ConstructObject() = 0;
	virtual void CustomAllocOps(unsigned int);
	virtual void CustomDeallocOps(unsigned int);
	virtual void CustomInitOps();
	virtual void CustomUpdateOps(float);
	virtual std::list<unsigned int>::iterator Dealloc(std::list<unsigned int>::iterator);
	virtual bool DestructionPred(T*) const;
};

#ifndef OBJECT_MANAGER_CC_INCLUDED
#include"engine/containers/ObjectManager.cc"
#endif // !OBJECT_MANAGER_CC_INCLUDED

/*@}*/
#endif
