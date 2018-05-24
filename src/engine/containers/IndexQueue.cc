#include"engine/containers/IndexQueue.h"

Index* Index::PAST_END_INDEX = new Index();

Index::Index(const size_t& index) :
	mId(index),
	mNext(PAST_END_INDEX),
	mPrev(PAST_END_INDEX)
{

}

Index::Index(const Index& other) :
	mId(other.mId),
	mNext(other.mNext),
	mPrev(other.mPrev)
{
}

Index::Index(Index&& other) :
	mId(std::move(other.mId)),
	mNext(std::move(other.mNext)),
	mPrev(std::move(other.mPrev))
{

}

Index::~Index()
{

}

Index& Index::operator=(const Index& other)
{
	mId = other.mId;
	mNext = other.mNext;
	mPrev = other.mPrev;
	return *this;
}

Index& Index::operator=(const size_t& index)
{
	mId = index;
	return *this;
}

bool Index::operator!() const
{
	return mId == NULL_ELEMENT_INDEX;
}

Index::operator size_t()
{
	return mId;
}

Index::operator const size_t&() const
{
	return mId;
}

IdxQueueIter::IdxQueueIter(Index& idx) :
	mIdx(&idx)
{

}

IdxQueueIter::IdxQueueIter(const IdxQueueIter& other) :
	mIdx(other.mIdx)
{
}

IdxQueueIter::~IdxQueueIter()
{

}

void IdxQueueIter::swap(IdxQueueIter& other)
{
	Index* temp = mIdx;
	mIdx = other.mIdx;
	other.mIdx = temp;
}

IdxQueueIter::reference IdxQueueIter::operator*()
{
	return *mIdx;
}

IdxQueueIter::pointer IdxQueueIter::operator->()
{
	return mIdx;
}

IdxQueueIter& IdxQueueIter::operator++()
{
	mIdx = mIdx->mNext;
	return *this;
}

IdxQueueIter IdxQueueIter::operator++(int)
{
	IdxQueueIter ret_val = *this;
	operator++();
	return ret_val;
}

IdxQueueIter& IdxQueueIter::operator--()
{
	mIdx = mIdx->mPrev;
	return *this;
}

IdxQueueIter IdxQueueIter::operator--(int)
{
	IdxQueueIter ret_val = *this;
	operator--();
	return ret_val;
}

bool IdxQueueIter::operator==(const IdxQueueIter& other)
{
	return *mIdx == *other.mIdx;
}

bool IdxQueueIter::operator!=(const IdxQueueIter& other)
{
	return *mIdx != *other.mIdx;
}

IdxQueueIter& IdxQueueIter::operator=(const IdxQueueIter& other)
{
	this->mIdx = other.mIdx;
	return *this;
}


IndexQueue::IndexQueue(const size_t& max_cap) :
	mSize(max_cap),
	mMaxCap(max_cap),
	mIndices(new Index[max_cap]),
	mFront(Index::PAST_END_INDEX),
	mTail(Index::PAST_END_INDEX)
{
	Initialize();
}

IndexQueue::~IndexQueue()
{
	try
	{
		delete[] mIndices;
	}
	catch (...)
	{

	}
}

void IndexQueue::Insert(const Index& index)
{
	assert(index >= 0 && index < mMaxCap);
	DebugMessage("");
	if (mIndices[index] == *Index::PAST_END_INDEX)
	{
		if (mFront == Index::PAST_END_INDEX)
		{
			DebugMessage("");
			mFront = &mIndices[index];
			mTail = mFront;
		}
		else
		{
			DebugMessage("");
			Index* temp = mTail;
			mTail = &mIndices[index];
			temp->mNext = mTail;
			mTail->mPrev = temp;
		}
		mIndices[index] = index;
		++mSize;
	}
}

void IndexQueue::Pop()
{
	if (mFront != Index::PAST_END_INDEX)
	{
		Index* temp = mFront;
		if (mFront == mTail)
		{
			mFront = Index::PAST_END_INDEX;
			mTail = mFront;
		}
		else
		{
			mFront = mFront->mNext;
			mFront->mPrev = Index::PAST_END_INDEX;
		}
		*temp = *Index::PAST_END_INDEX;
		--mSize;
	}
}

void IndexQueue::Clear()
{
	while (mFront != Index::PAST_END_INDEX)
	{
		Pop();
	}
	mFront = Index::PAST_END_INDEX;
	mTail = Index::PAST_END_INDEX;
}

const Index& IndexQueue::Front() const
{
	return *mFront;
}

const Index& IndexQueue::Back() const
{
	return *mTail;
}

IdxQueueIter IndexQueue::Begin()
{
	return IdxQueueIter(*mFront);
}

IdxQueueIter IndexQueue::End()
{
	return *Index::PAST_END_INDEX;
}

bool IndexQueue::Empty() const
{
	return (mSize == 0);
}

const IndexQueue::size_t& IndexQueue::Size() const
{
	return mSize;
}

const IndexQueue::size_t& IndexQueue::MaxCap() const
{
	return mMaxCap;
}

void IndexQueue::Initialize()
{
	for (size_t i = 0; i < mMaxCap; ++i)
	{
		mIndices[i] = i;
		if (i > 0)
		{
			mIndices[i].mPrev = &mIndices[i - 1];
		}
		if (i < (mSize - 1))
		{
			mIndices[i].mNext = &mIndices[i + 1];
		}
	}
	mFront = &mIndices[0];
	mTail = &mIndices[mMaxCap - 1];
}

IndexList::IndexList(const size_t& max_cap) :
	IndexQueue(max_cap)
{
	Clear();
}

IndexList::~IndexList()
{

}

void IndexList::Remove(const Index& index)
{
	if (mIndices[index] != *Index::PAST_END_INDEX)
	{
		Index* temp = &mIndices[index];
		if (mSize == 1)
		{
			DebugMessage("");
			Clear();
			return;
		}
		else if (temp == mFront)
		{
			DebugMessage("");
			mFront = mFront->mNext;
			mFront->mPrev = Index::PAST_END_INDEX;
		}
		else if (temp == mTail)
		{
			DebugMessage("");
			mTail = mTail->mPrev;
			mTail->mNext = Index::PAST_END_INDEX;
		}
		else
		{
			DebugMessage("");
			temp->mNext->mPrev = temp->mPrev;
			temp->mPrev->mNext = temp->mNext;
		}
		*temp = *Index::PAST_END_INDEX;
		--mSize;
	}
}