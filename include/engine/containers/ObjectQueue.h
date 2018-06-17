#ifndef OBJECT_QUEUE_HEADER_INCLUDED
#define OBJECT_QUEUE_HEADER_INCLUDED

#include"engine/containers/IndexQueue.h"
#include"engine/containers/Iterator.h"
#include"engine/util/UtiliDefs.h"

template<class T>
class ObjectQueue
{
public:
	typedef unsigned int size_t;
	typedef int index_t;
	ObjectQueue();
	virtual ~ObjectQueue();

	virtual void Initialize(const size_t&);
	virtual void Clear();

	size_t& Size() const;
	size_t& MaxCapacity() const;

	Iterator<T> Front() const;
	virtual void Push(T*);
	virtual void Pop();

private:
	static Iterator<T> sEnd;
protected:
	size_t mMaxCapacity;
	size_t mSize;
	index_t mNextIndex;
	T* mObjectArray;
	Iterator<T>* mHead;
	Iterator<T>* mTail;
	IndexQueue mIndexQueue;
	virtual bool ObjectCameFromThisQueue(T*) const;
	virtual void InitializeObject(T&);
	virtual size_t GetIndex(T*) const;
};

#ifndef OBJECT_QUEUE_CC_INCLUDED
#include"engine/containers/ObjectQueue.cc"
#endif // !OBJECT_QUEUE_CC_INCLUDED
#endif // !OBJECT_QUEUE_HEADER_INCLUDED
