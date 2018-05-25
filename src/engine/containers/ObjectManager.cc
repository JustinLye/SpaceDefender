#ifndef OBJECT_MANAGER_CC_INCLUDED
#define OBJECT_MANAGER_CC_INCLUDED
#include"engine/containers/ObjectManager.h"

template<class T>
ObjectManager<T>::ObjectManager() :
	mObjects(nullptr)
{

}

template<class T>
ObjectManager<T>::~ObjectManager()
{
	Destroy();
}

template<class T>
unsigned int ObjectManager<T>::ActiveObjectCount() const
{
	return mActiveIndices.size();
}

template<class T>
void ObjectManager<T>::Init()
{
#ifdef ENGINE_DEBUG
	DebugMessage("");
#endif
	CustomInitOps();
	mMaxCapacity = MaxCapacity();
	mMaxActiveCapacity = MaxActiveCapacity();
	mObjects = new T*[mMaxCapacity];
#ifdef ENGINE_DEBUG
	DebugMessage(mMaxActiveCapacity);
	if (mMaxCapacity <= 0)
	{
		DebugMessage("WARNING: Max Capacity is less than or equal to 0");
	}
#endif
	mIndexQueue.Initialize(MaxCapacity());
	DebugMessage(mIndexQueue.MaxCap());
	
	for (int i = 0; i < mMaxCapacity; ++i)
	{
		mObjects[i] = ConstructObject();
		//mIndexQueue.push(i);
	}
}

template<class T>
void ObjectManager<T>::Destroy()
{
	if (mObjects != nullptr)
	{
		delete[] mObjects;
	}
}

template<class T>
void ObjectManager<T>::Update(const float& dt)
{
	CustomUpdateOps(dt);
	std::list<unsigned int>::iterator iter = mActiveIndices.begin();
	while (iter != mActiveIndices.end())
	{
		T* object = mObjects[*iter];
		object->Update(dt);
		if (DestructionPred(object))
		{
			iter = Dealloc(iter);
		}
		else
		{
			++iter;
		}
	}
}

template<class T>
void ObjectManager<T>::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	std::list<unsigned int>::iterator iter = mActiveIndices.begin();
	while (iter != mActiveIndices.end())
	{
		mObjects[*iter]->Render(proj_mat, view_mat);
		++iter;
	}
}

template<class T>
unsigned int ObjectManager<T>::Alloc()
{
	unsigned int result = NOT_INDEX;
	if (!mIndexQueue.Empty() && (int)mActiveIndices.size() < mMaxActiveCapacity)
	{
		//result = mIndexQueue.front();
		result = mIndexQueue.Front();
		//mIndexQueue.pop();
		mIndexQueue.Pop();
		CustomAllocOps(result);
		mActiveIndices.push_back(result);
	}
	return result;
}


template<class T>
void ObjectManager<T>::CustomAllocOps(const unsigned int& index)
{

}

template<class T>
void ObjectManager<T>::CustomDeallocOps(const unsigned int& index)
{

}

template<class T>
void ObjectManager<T>::CustomInitOps()
{

}

template<class T>
void ObjectManager<T>::CustomUpdateOps(const float& dt)
{

}

template<class T>
std::list<unsigned int>::iterator ObjectManager<T>::Dealloc(std::list<unsigned int>::iterator iter)
{
	//mIndexQueue.push(*iter);
	mIndexQueue.Insert(*iter);
	CustomDeallocOps(*iter);
	return mActiveIndices.erase(iter);
}

template<class T>
bool ObjectManager<T>::DestructionPred(T* object) const
{
	return false;
}

#endif