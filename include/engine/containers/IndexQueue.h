#ifndef INDEX_QUEUE_HEADER_INCLUDED
#define INDEX_QUEUE_HEADER_INCLUDED

#include<string>
#include<iterator>
#include<boost/lexical_cast.hpp>
#include<stdexcept>
#include"engine/util/UtiliDefs.h"
#include"engine/util/Constants.h"
#include"engine/util/DebugFunctions.h"
using namespace Constants::Containers;


/**
  @ingroup EngineIndicesAuxillary
  @struct Index
  @brief Used as index to element of IndexQueue
*/
struct Index
{
	typedef unsigned int size_t;
	Index(const size_t& = NULL_ELEMENT_INDEX);
	Index(const Index&);
	Index(Index&&);
	~Index();

	Index& operator=(const Index&);
	Index& operator=(const size_t&);
	bool operator!() const;
	operator size_t();
	operator const size_t&() const;

//protected:
	friend class IndexQueue;
	friend class IndexList;
	friend class IdxQueueIter;
	size_t mId;
	Index* mNext;
	Index* mPrev;
	static Index* PAST_END_INDEX; // Use as abstraction for end()
};

/**
  @ingroup EngineIndicesAuxillary
  @class IdxQueueIter
  @brief  Implements iterator concept with pointer to Index. Used by IndexQueue
*/
class IdxQueueIter
{
public:
	typedef std::ptrdiff_t difference_type;
	typedef Index value_type;
	typedef Index& reference;
	typedef Index* pointer;
	typedef std::bidirectional_iterator_tag iterator_category;

	IdxQueueIter(Index& = *Index::PAST_END_INDEX);
	IdxQueueIter(const IdxQueueIter&);
	~IdxQueueIter();

	void swap(IdxQueueIter&);

	reference operator*();
	pointer operator->();
	IdxQueueIter& operator++();
	IdxQueueIter operator++(int);
	IdxQueueIter& operator--();
	IdxQueueIter operator--(int);

	bool operator==(const IdxQueueIter&);
	bool operator!=(const IdxQueueIter&);

	IdxQueueIter& operator=(const IdxQueueIter&);

protected:
	Index* mIdx;
};

/** @addtogroup EngineIndicesContainers */
/*@{*/
class IndexQueue
{
public:
	typedef unsigned int size_t;
	IndexQueue();
	virtual ~IndexQueue();
	
	void Insert(const Index&);
	void Pop();
	void Clear();

	const Index& Front() const;
	const Index& Back() const;
	IdxQueueIter Begin();
	IdxQueueIter End();
	bool Empty() const;
	const size_t& Size() const;
	const size_t& MaxCap() const;
	virtual void Initialize(const size_t&);

protected:
	size_t mSize;
	size_t mMaxCap;
	Index* mIndices;
	Index* mFront;
	Index* mTail;

	
};

class IndexList :
	protected IndexQueue
{
public:
	using IndexQueue::size_t;
	using IndexQueue::Insert;
	using IndexQueue::Clear;
	using IndexQueue::Begin;
	using IndexQueue::End;
	using IndexQueue::Empty;
	using IndexQueue::Size;
	using IndexQueue::MaxCap;
	using IndexQueue::Initialize;

	IndexList();
	virtual ~IndexList();

	void Remove(const Index&);
protected:

};
/*@}*/
#endif