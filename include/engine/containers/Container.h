/** \cond HIDDEN_SYMBOLS */
#ifndef CONTAINER_HEADER_INCLUDED
#define CONTAINER_HEADER_INCLUDED

#include<iterator>
#include<iostream>
#include"engine/util/Constants.h"

using namespace Constants::Containers;

struct Index
{
	// Constructors
	Index(const unsigned int& = NULL_ELEMENT_INDEX);
	Index(const Index&);
	Index(Index&&);

	// Member functions
	void Clear();

	// Observation ops.
	bool operator!() const;
	bool operator<(const Index&) const;
	bool operator==(const Index&) const;
	bool operator!=(const Index&) const;

	// Assignment ops.
	Index& operator=(const Index&);
	Index& operator=(const unsigned int&);
	Index& operator=(const int&);

	// Implict conversion ops.
	operator unsigned int() const;
	operator int() const;
	
	// State
	unsigned int mId;
};

struct Element
{
	Element(const unsigned int& = NULL_ELEMENT_INDEX);
	Element(const Element&);
	Element(Element&&);

	void Clear();

	bool operator!() const;
	bool operator<(const Element&) const;
	bool operator==(const Element&) const;

	Element& operator=(const Element&);

	Index mIndex;
	friend std::ostream& operator<<(std::ostream&, const Element&);
protected:
	Element* mNext;
	Element* mPrev;
	void Output(std::ostream&) const;
	friend class ElementIter;
	friend class Container;
	friend class IndexQueue;
};


class ElementIter
{
public:
	typedef std::ptrdiff_t difference_type;
	typedef Element value_type;
	typedef Element* pointer;
	typedef Element& reference;
	typedef std::bidirectional_iterator_tag iterator_category;

	ElementIter(Element* = nullptr);
	ElementIter(const ElementIter&);
	ElementIter& operator=(const ElementIter&);
	~ElementIter();
	void swap(ElementIter&);

	reference operator*();
	pointer operator->();
	ElementIter& operator++();
	ElementIter& operator--();
	ElementIter operator++(int);
	ElementIter operator--(int);
	bool operator==(const ElementIter&) const;
	bool operator!=(const ElementIter&) const;

protected:
	Element* ptr;
};

class Container
{
public:
	typedef ElementIter iterator;

	Container();
	virtual ~Container();
	
	virtual void Clear();
	virtual bool Empty() const;
	virtual const unsigned int& Size() const;

	virtual iterator begin();
	virtual iterator end();

	virtual const unsigned int& MaxCapacity() const = 0;
protected:
	virtual void Initialize();
	virtual void Allocate();
	Element* mElements;
	Element mElementPastLast;
	ElementIter mPastLastElement;
};

#endif
/** \endcond */