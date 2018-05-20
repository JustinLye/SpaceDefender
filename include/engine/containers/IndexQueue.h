#ifndef INDEX_QUEUE_HEADER_INCLUDED
#define INDEX_QUEUE_HEADER_INCLUDED

#include<string>
#include<boost/lexical_cast.hpp>
#include<stdexcept>
#include"engine/containers/Container.h"
#include"engine/util/UtiliDefs.h"

class IndexQueue :
	public Container
{
public:
	IndexQueue(const unsigned int& = 0);
	virtual ~IndexQueue();
	const unsigned int& MaxCapacity() const;
	bool Empty() const override;
	const unsigned int& Size() const override;
	iterator::value_type Front() const;
	iterator::value_type Back() const;
	virtual iterator begin() override;
	virtual void PushBack(const iterator::reference&);
	virtual iterator::value_type PopFront();
protected:
	unsigned int mMaxCap;
	unsigned int mSize;
	iterator::pointer mFront;
	iterator::pointer mTail;
	virtual void Allocate() override;
	iterator::pointer LookupElement(const iterator::reference&);



};

#endif