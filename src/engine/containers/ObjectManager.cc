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
void ObjectManager<T>::Init()
{
	mMaxCapacity = MaxCapacity();
	mMaxActiveCapacity = MaxActiveCapacity();
	mObjects = new T*[mMaxCapacity];
	for (int i = 0; i < mMaxCapacity)
	{
		mObjects[i] = new T();
		mIndexQueue.push(i);
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
void ObjectManager<T>::Render()
{
	std::list<unsigned int>::iterator iter = mActiveIndices.begin();
	while (iter != mActiveIndices.end())
	{
		mObjects[*iter]->Render();
		++iter;
	}
}

template<class T>
unsigned int ObjectManager<T>::Alloc()
{
	unsigned int result = NOT_INDEX;
	if (!mIndexQueue.empty() && mActiveIndices.size() < mMaxActiveCapacity)
	{
		result = mIndexQueue.front();
		mIndexQueue.pop();
		CustomerAllocOps(result);
	}
	return result;
}


template<class T>
void ObjectManager<T>::CustomAllocOps(const unsigned int& index)
{

}

template<class T>
std::list<unsigned int>::iterator ObjectManager<T>::Dealloc(std::list<unsigned int>::iterator iter)
{
	mIndexQueue.push(*iter);
	return mActiveIndices.erase(iter);
}

template<class T>
bool ObjectManager<T>::DestructionPred(T* object) const
{
	return false;
}

#endif