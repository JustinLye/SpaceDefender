#ifndef OBJECT_MANAGER_HEADER_INCLUDED
#define OBJECT_MANAGER_HEADER_INCLUDED

#include<queue>
#include<list>

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

	virtual int MaxCapacity() = 0;
	virtual int MaxActiveCapacity() = 0;
	virtual void Spawn() = 0;

	virtual void Init();
	virtual void Destroy();

	virtual void Update(const float&);
	virtual void Render();

protected:
	int mMaxCapacity;
	int mMaxActiveCapacity;
	std::queue<unsigned int> mIndexQueue;
	std::list<unsigned int> mActiveIndices;
	T** mObjects;

	virtual unsigned int Alloc();
	virtual void CustomAllocOps(const unsigned int&);
	virtual std::list<unsigned int>::iterator Dealloc(std::list<unsigned int>::iterator);
	virtual bool DestructionPred(T*) const;
};

#ifndef OBJECT_MANAGER_CC_INCLUDED
#include"engine/containers/ObjectManager.cc"
#endif // !OBJECT_MANAGER_CC_INCLUDED


#endif
