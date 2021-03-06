#ifndef ITERATOR_CC_INCLUDED
#define ITERATOR_CC_INCLUDED

#include"engine/containers/Iterator.h"

#ifdef BUILD_ITERATOR
#endif

template<class T>
Iterator<T>::Iterator(pointer ptr) :
	mPtr(ptr)
{
}

template<class T>
Iterator<T>::Iterator(const Iterator& other) :
	mPtr(IterItem(other.mPtr))
{
}

template<class T>
Iterator<T>::~Iterator()
{

}

template<class T>
typename Iterator<T>::reference Iterator<T>::operator*()
{
	return *mPtr;
}

template<class T>
typename Iterator<T>::pointer Iterator<T>::operator->()
{
	return mPtr.operator->();
}

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
	++mPtr;
	return mPtr;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int)
{
	Iterator ret_val = *this;
	operator++();
	return ret_val;
}

template<class T>
Iterator<T>& Iterator<T>::operator--()
{
	--mPtr;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator--(int)
{
	Iterator ret_val = *this;
	operator--();
	return ret_val;
}

template<class T>
bool Iterator<T>::operator==(const Iterator& other) const
{
	return *mPtr == *(other.mPtr);
}

template<class T>
bool Iterator<T>::operator!=(const Iterator& other) const
{
	return *mPtr != *(other.mPtr);
}

template<class T>
Iterator<T>& Iterator<T>::operator=(const Iterator& other)
{
	mPtr = other.mPtr;
	return *this;
}
#endif // !ITERATOR_CC_INCLUDED
