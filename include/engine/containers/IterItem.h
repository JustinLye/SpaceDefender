#ifndef ITER_ITEM_HEADER_INCLUDED
#define ITER_ITEM_HEADER_INCLUDED

template<class T>
struct IterItem
{
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;

	IterItem(pointer);
	IterItem(const IterItem&);
	virtual ~IterItem();

	reference operator*();
	pointer operator->();
	IterItem& operator++();
	IterItem operator++(int);
	IterItem& operator--();
	IterItem operator--(int);

	bool operator==(const IterItem&) const;
	bool operator==(const T*) const;
	bool operator!=(const IterItem&) const;
	bool operator!=(const T*) const;

	IterItem& operator=(const IterItem&);

	T* mPtr;
	IterItem* mPrev;
	IterItem* mNext;
};

#ifndef ITER_ITEM_CC_INCLUDED
#include"engine/containers/IterItem.cc"
#endif // !ITER_ITEM_CC_INCLUDED
#endif // !ITER_ITEM_HEADER_INCLUDED
