#ifndef INDEX_QUEUE_HEADER_INCLUDED
#define INDEX_QUEUE_HEADER_INCLUDED

#include<string>
#include<iterator>
#include<boost/lexical_cast.hpp>
#include<stdexcept>
#include"engine/util/UtiliDefs.h"
#include"engine/util/Constants.h"

using namespace Constants::Containers;

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

protected:
	friend class IndexQueue;
	friend class IdxQueueIter;
	size_t mId;
	Index* mNext;
	Index* mPrev;
	static Index* PAST_END_INDEX; // Use as abstraction for end()
};

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

	void swap(const IdxQueueIter&);

	reference operator*();
	reference operator->();
	reference operator++();
	value_type operator++(int);
	reference operator--();
	value_type operator--(int);

	bool operator==(const IdxQueueIter&);
	bool operator!=(const IdxQueueIter&);

	IdxQueueIter& operator=(const IdxQueueIter&);


protected:
	Index* idx;
};



class IndexQueue
{
public:

protected:
	Index* mIndices;
};

#endif