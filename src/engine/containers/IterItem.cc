#ifndef ITER_ITEM_CC_INCLUDED
#define ITER_ITEM_CC_INCLUDED

#include"engine/containers/IterItem.h"

template<class T>
IterItem<T>::IterItem(pointer ptr) :
	mPtr(ptr),
	mPrev(nullptr),
	mNext(nullptr)
{

}

template<class T>
IterItem<T>::IterItem(const IterItem& other) :
	mPtr(other.mPtr),
	mPrev(other.mPrev),
	mNext(other.mNext)
{

}

template<class T>
IterItem<T>::~IterItem()
{

}

template<class T>
typename IterItem<T>::reference IterItem<T>::operator*()
{
	return *mPtr;
}

template<class T>
typename IterItem<T>::pointer IterItem<T>::operator->()
{
	return mPtr;
}

template<class T>
IterItem<T>& IterItem<T>::operator++()
{
	if (mPtr != nullptr)
	{
		mPtr = mPtr->mNext;
	}
	return *this;
}

template<class T>
IterItem<T> IterItem<T>::operator++(int)
{
	IterItem ret_val = *this;
	operator++();
	return ret_val;
}

template<class T>
IterItem<T>& IterItem<T>::operator--()
{
	if (mPtr != nullptr)
	{
		mPtr = mPtr->mPrev;
	}
	return *this;
}

template<class T>
IterItem<T> IterItem<T>::operator--(int)
{
	IterItem ret_val = *this;
	operator--();
	return ret_val;
}

template<class T>
bool IterItem<T>::operator==(const IterItem& other) const
{
	if (mPtr != nullptr)
	{
		return *mPtr == *(other.mPtr);
	}
	else
	{
		return other.mPtr == nullptr;
	}
}

template<class T>
bool IterItem<T>::operator==(const T* ptr) const
{
	return mPtr == ptr;
}

template<class T>
bool IterItem<T>::operator!=(const IterItem& other) const
{
	if (mPtr != nullptr)
	{
		return *mPtr != *(other.mPtr);
	}
	else
	{
		return other.mPtr != nullptr;
	}
}

template<class T>
bool IterItem<T>::operator!=(const T* ptr) const
{
	return mPtr != ptr;
}

template<class T>
IterItem<T>& IterItem<T>::operator=(const IterItem& other)
{
	mPtr = other.mPtr;
	mNext = other.mNext;
	mPrev = other.mPrev;
	return *this;
}

#endif // !ITER_ITEM_CC_INCLUDED
