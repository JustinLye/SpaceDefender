#ifndef OBJECT_QUEUE_CC_INCLUDED
#define OBJECT_QUEUE_CC_INCLUDED

#include"engine/containers/ObjectQueue.h"

template<class T>
Iterator<T> ObjectQueue<T>::sEnd = Iterator<T>();

template<class T>
ObjectQueue<T>::ObjectQueue() :
	mMaxCapacity(0),
	mSize(0),
	mObjectArray(nullptr),
	mHead(nullptr),
	mTail(nullptr)
{

}

template<class T>
ObjectQueue<T>::~ObjectQueue()
{
	try
	{
		if (mObjectArray != nullptr)
		{
			delete[] mObjectArray;
		}
	}
	catch (...)
	{

	}
}

template<class T>
void ObjectQueue<T>::Initialize(const size_t& max_cap)
{
	if (mMaxCapacity > 0)
	{
		throw std::runtime_error("ObjectQueue already initialized.");
	}
	assert(max_cap > 0);
	mMaxCapacity = max_cap;
	mSize = max_cap;
	mObjectArray = new Iterator<T>[mMaxCapacity];
	for (size_t = i; i < mMaxCapacity; ++i)
	{
		InitializeObject(*mObjectArray[i]);
		if (i > 0)
		{
			mObjectArray[i].mPrev = &mObjectArray[i - 1];
		}
		if (i < (mMaxCapcity - 1))
		{
			mObjectArray[i].mNext = &mObjectArray[i + 1];
		}
	}
	mHead = &mObjectArray[0];
	mTail = &mObjectArray[mMaxCapacity - 1];
	mIndexQueue.Initialize(mMaxCapacity);
}

template<class T>
void ObjectQueue<T>::Clear()
{
	for (size_t i = 0; i < mMaxCapacity; ++i)
	{
		mObjectArray[i].mPtr = nullptr;
		mObjectArray[i].mNext = nullptr;
		mObjectArray[i].mPrev = nullptr;
	}
	mHead = nullptr;
	mTail = nullptr;
	mSize = 0;

}

template<class T>
typename ObjectQueue<T>::size_t& ObjectQueue<T>::Size() const
{
	return mSize;
}

template<class T>
typename ObjectQueue<T>::size_t& ObjectQueue<T>::MaxCapacity() const
{
	return mMaxCapacity;
}

template<class T>
Iterator<T> ObjectQueue<T>::Front() const
{
	if (mIndexQueue.Empty())
	{
		return nullptr;
	}
	return mIndexQueue
	Index index = mIndexQueue.Front();
	return *mObjectArray[index];
}

template<class T>
void ObjectQueue<T>::Push(T* item)
{
}

template<class T>
void ObjectQueue<T>::Pop()
{
	
}

template<class T>
bool ObjectQueue<T>::ObjectCameFromThisQueue(T* ptr) const
{
	if (mObjectArray == nullptr || mMaxCapacity <= 0)
	{
		return true;
	}

	if (ptr < (mObjectArray + mMaxCapacity) && ptr <= mObjectArray)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void ObjectQueue<T>::InitializeObject(T& obj)
{

}

template<class T>
typename ObjectQueue<T>::size_t ObjectQueue<T>::GetIndex(T* ptr) const
{
	if (!ObjectCameFromThisQueue(ptr))
	{
		throw std::runtime_error("Object is not from queue.");
	}
	size_t result = 0;
	return ptr - mObjectArray;
}

#endif // !OBJECT_QUEUE_CC_INCLUDED
