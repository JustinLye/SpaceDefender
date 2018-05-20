#include"engine/containers/Container.h"

Index::Index(const unsigned int& id) :
	mId(id)
{

}

Index::Index(const Index& other) :
	mId(other.mId)
{

}

Index::Index(Index&& other) :
	mId(std::move(other.mId))
{

}

void Index::Clear()
{
	mId = NULL_ELEMENT_INDEX;
}

bool Index::operator!() const
{
	return mId == NULL_ELEMENT_INDEX;
}

bool Index::operator<(const Index& other) const
{
	return mId < other.mId;
}

bool Index::operator==(const Index& other) const
{
	return mId == other.mId;
}

bool Index::operator!=(const Index& other) const
{
	return mId != other.mId;
}

Index& Index::operator=(const Index& other)
{
	mId = other.mId;
	return *this;
}

Index& Index::operator=(const unsigned int& id)
{
	mId = id;
	return *this;
}

Index& Index::operator=(const int& id)
{
	mId = id >= 0 ? id : NULL_ELEMENT_INDEX;
	return *this;
}

Index::operator unsigned int() const
{
	return mId;
}

Index::operator int() const
{
	return mId;
}

Element::Element(const unsigned int& id) :
	mIndex(id),
	mNext(nullptr),
	mPrev(nullptr)
{

}

Element::Element(const Element& other) :
	mIndex(other.mIndex),
	mNext(other.mNext),
	mPrev(other.mPrev)
{

}

Element::Element(Element&& other) :
	mIndex(std::move(other.mIndex)),
	mNext(std::move(other.mNext)),
	mPrev(std::move(other.mPrev))
{

}

void Element::Clear()
{
	mIndex.Clear();
	mNext = nullptr;
	mPrev = nullptr;
}

bool Element::operator!() const
{
	return !mIndex;
}

bool Element::operator<(const Element& other) const
{
	return mIndex < other.mIndex;
}

bool Element::operator==(const Element& other) const
{
	return mIndex == other.mIndex;
}

Element& Element::operator=(const Element& other)
{
	mIndex = other.mIndex;
	mNext = other.mNext;
	mPrev = other.mPrev;
	return *this;
}

ElementIter::ElementIter(Element* element_ptr) :
	ptr(element_ptr)
{

}

ElementIter::ElementIter(const ElementIter& other) :
	ptr(other.ptr)
{

}

ElementIter& ElementIter::operator=(const ElementIter& other)
{
	ptr = other.ptr;
	return *this;
}

ElementIter::~ElementIter()
{

}

void ElementIter::swap(ElementIter& other)
{
	ElementIter tmp(*this);
	*this = other;
	other = tmp;
}

ElementIter::reference ElementIter::operator*()
{
	return *ptr;
}

ElementIter::pointer ElementIter::operator->()
{
	return ptr;
}

ElementIter& ElementIter::operator++()
{
	ptr = ptr->mNext;
	return *this;
}

ElementIter& ElementIter::operator--()
{
	ptr = ptr->mPrev;
	return *this;
}

ElementIter ElementIter::operator++(int)
{
	ElementIter tmp(*this);
	operator++();
	return tmp;
}

ElementIter ElementIter::operator--(int)
{
	ElementIter tmp(*this);
	operator--();
	return tmp;
}

bool ElementIter::operator==(const ElementIter& other) const
{
	return ptr->mIndex == other.ptr->mIndex;
}

bool ElementIter::operator!=(const ElementIter& other) const
{
	return ptr->mIndex != other.ptr->mIndex;
}

std::ostream& operator<<(std::ostream& os, const Element& element)
{
	element.Output(os);
	return os;
}

void Element::Output(std::ostream& os) const
{
	os << mIndex.mId;
}

Container::Container() :
	mElements(nullptr),
	mElementPastLast(Element()),
	mPastLastElement(&mElementPastLast)
{

}

Container::~Container()
{
	if (mElements != nullptr)
	{
		delete[] mElements;
	}
}

void Container::Clear()
{
	if (mElements == nullptr)
	{
		return;
	}
	for (unsigned int i = 0; i < MaxCapacity(); ++i)
	{
		mElements[i].Clear();
	}
}

bool Container::Empty() const
{
	return mElements == nullptr;
}

const unsigned int& Container::Size() const
{
	if (mElements == nullptr)
	{
		return 0;
	}
	return MaxCapacity();
}

Container::iterator Container::begin()
{
	return ElementIter(mElements == nullptr ? mPastLastElement : &mElements[0]);
}

Container::iterator Container::end()
{
	return mPastLastElement;
}

void Container::Initialize()
{
	if (mElements != nullptr)
	{
		delete[] mElements;
	}
	mElements = new Element[MaxCapacity()];
	Allocate();
}

void Container::Allocate()
{
	unsigned int max_cap = MaxCapacity();
	mElements[0].mIndex = 0;
	mElements[0].mNext = max_cap > 1 ? &mElements[1] : &mElementPastLast;
	mElements[0].mPrev = &mElementPastLast;
	if (max_cap > 1)
	{
		mElements[max_cap - 1].mIndex = max_cap - 1;
		mElements[max_cap - 1].mNext = &mElementPastLast;
		mElements[max_cap - 1].mPrev = max_cap > 2 ? &mElements[max_cap - 2] : &mElementPastLast;
	}
	for (int i = 1; i < max_cap - 1; ++i)
	{
		mElements[i].mIndex = i;
		mElements[i].mNext = &mElements[i + 1];
		mElements[i].mPrev = &mElements[i - 1];
	}
}


