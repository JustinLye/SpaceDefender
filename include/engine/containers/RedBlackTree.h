#ifndef RED_BLACK_TREE_HEADER_INCLUDED
#define RED_BLACK_TREE_HEADER_INCLUDED

#include"engine/util/Constants.h"
using namespace Constants::Types;

template<class T>
class Leaf
{
public:
	Leaf();
	Leaf(const Leaf&);
	Leaf(Leaf&&);
	virtual ~Leaf();
	Leaf& operator=(const Leaf&);

protected:
	friend class RBTree;
	friend class LeafIter;
	color_t mColor;
	T mKey;
	T* mLeft;
	T* mRight;
	T* mPrev;
	T* mNext; //For array
	static Leaf* NIL;
};

template<class T>
class LeafIter
{
public:
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::bidirectional_iterator_tag iterator_category;

	reference operator*();
	pointer operator->();
	reference operator++();
	value_type operator++(int);
	reference operator--();
	value_type operator--(int);

	bool operator==(const LeafIter&);
	bool operator!=(const LeafIter&);

	reference operator=(const LeafIter&);

protected:
	pointer mPtr;

};

template<class T>
class RBTree
{
public:
	typedef unsigned int size_t;
	RBTree();
	RBTree(const RBTree);
	RBTree(RBTree&&);
	virtual ~RBTree();

	virtual void Initialize(const size_t&);
	virtual void Insert(const T&);
	virtual void 
protected:
	size_t mSize;
	size_t mMaxCap;
	Leaf<T>* mLeaves;

};

#endif // !RED_BLACK_TREE_HEADER_INCLUDED
