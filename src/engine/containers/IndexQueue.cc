#include"engine/containers/IndexQueue.h"

IndexQueue::IndexQueue(const unsigned int& max_cap) :
	Container(),
	mMaxCap(max_cap),
	mSize(max_cap),
	mFront(nullptr),
	mTail(nullptr)
{
	Initialize();
}

IndexQueue::~IndexQueue()
{

}

const unsigned int& IndexQueue::MaxCapacity() const
{
	return mMaxCap;
}

bool IndexQueue::Empty() const
{
	return Size() == 0;
}

const unsigned int& IndexQueue::Size() const
{
	return mSize;
}

IndexQueue::iterator::value_type IndexQueue::Front() const
{
	return iterator::value_type(*mFront);
}

IndexQueue::iterator::value_type IndexQueue::Back() const
{
	return iterator::value_type(*mTail);
}

IndexQueue::iterator IndexQueue::begin()
{
	return iterator(mFront);
}

void IndexQueue::PushBack(const iterator::reference& index)
{
	iterator::pointer element_ptr = LookupElement(index);
	if (!element_ptr)
	{
		//throw std::runtime_error(MessageStr(std::string("ERROR:\t Index ") + boost::lexical_cast<std::string>(index.mIndex.mId) + std::string(" is outsided index queue bounds of [0, ") + boost::lexical_cast<std::string>(mMaxCap) + std::string("]")));
	}
	// Make the new element the tail

}

IndexQueue::iterator::value_type IndexQueue::PopFront()
{
	if (Empty())
	{
		return iterator::value_type(*mPastLastElement);
	}

	// Copy element from front
	iterator::value_type result(*mFront);

	// Assign next element to front
	iterator::pointer temp = mFront;
	mFront = mFront->mNext;
	mFront->mPrev = &(*mPastLastElement);
	--mSize;

	// Point former front to end
	temp->mNext = &(*mPastLastElement);
	temp->mPrev = &(*mPastLastElement);
}

IndexQueue::iterator::pointer IndexQueue::LookupElement(const iterator::reference& index)
{
	iterator::pointer result = nullptr;
	if (!(index.mIndex.mId >= 0 && index.mIndex.mId < mMaxCap))
	{
		result = &mElements[index.mIndex.mId];
	}
	return result;
}