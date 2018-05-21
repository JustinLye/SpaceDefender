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