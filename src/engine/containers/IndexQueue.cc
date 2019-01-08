#include"engine/containers/IndexQueue.h"

namespace sd_app {
namespace engine {
namespace containers {
namespace impl {
Index* Index::PAST_END_INDEX = new Index();

Index::Index(const size_t& index) :
  mId(index),
  mNext(PAST_END_INDEX),
  mPrev(PAST_END_INDEX) {

}

Index::Index(const Index& other) :
  mId(other.mId),
  mNext(other.mNext),
  mPrev(other.mPrev) {}

Index::Index(Index&& other) :
  mId(std::move(other.mId)),
  mNext(std::move(other.mNext)),
  mPrev(std::move(other.mPrev)) {

}

Index::~Index() {

}

Index& Index::operator=(const Index& other) {
  mId = other.mId;
  mNext = other.mNext;
  mPrev = other.mPrev;
  return *this;
}

Index& Index::operator=(const size_t& index) {
  mId = index;
  return *this;
}

bool Index::operator!() const {
  return mId == NULL_ELEMENT_INDEX;
}

Index::operator size_t() {
  return mId;
}

Index::operator const size_t&() const {
  return mId;
}

IdxQueueIter::IdxQueueIter(Index& idx) :
  mIdx(&idx) {

}

IdxQueueIter::IdxQueueIter(const IdxQueueIter& other) :
  mIdx(other.mIdx) {}

IdxQueueIter::~IdxQueueIter() {

}

void IdxQueueIter::swap(IdxQueueIter& other) {
  Index* temp = mIdx;
  mIdx = other.mIdx;
  other.mIdx = temp;
}

IdxQueueIter::reference IdxQueueIter::operator*() {
  return *mIdx;
}

IdxQueueIter::pointer IdxQueueIter::operator->() {
  return mIdx;
}

IdxQueueIter& IdxQueueIter::operator++() {
  mIdx = mIdx->mNext;
  return *this;
}

IdxQueueIter IdxQueueIter::operator++(int) {
  IdxQueueIter ret_val = *this;
  operator++();
  return ret_val;
}

IdxQueueIter& IdxQueueIter::operator--() {
  mIdx = mIdx->mPrev;
  return *this;
}

IdxQueueIter IdxQueueIter::operator--(int) {
  IdxQueueIter ret_val = *this;
  operator--();
  return ret_val;
}

bool IdxQueueIter::operator==(const IdxQueueIter& other) {
  return *mIdx == *other.mIdx;
}

bool IdxQueueIter::operator!=(const IdxQueueIter& other) {
  return *mIdx != *other.mIdx;
}

IdxQueueIter& IdxQueueIter::operator=(const IdxQueueIter& other) {
  this->mIdx = other.mIdx;
  return *this;
}


IndexQueue::IndexQueue() :
  mSize(0),
  mMaxCap(0),
  mIndices(nullptr),
  mFront(Index::PAST_END_INDEX),
  mTail(Index::PAST_END_INDEX) {}

IndexQueue::~IndexQueue() {
  if (mIndices != nullptr) {
    try {
      delete[] mIndices;
    } catch (...) {

    }
  }
}

void IndexQueue::Insert(const Index& index) {
#ifdef ENGINE_DEBUG

  if (!(index >= 0 && index < mMaxCap)) {
    DebugMessage(std::to_string(index) + std::string(" is out of bounds [") + std::to_string(0) + std::string(", ") + std::to_string(mMaxCap) + std::string("]"));
    throw std::runtime_error("Attempted to insert value outside bounds");
  }
  assert(mIndices != nullptr);
#endif

  if (mIndices[index] == *Index::PAST_END_INDEX) {
    if (mFront == Index::PAST_END_INDEX) {
      mFront = &mIndices[index];
      mTail = mFront;
    } else {
      Index* temp = mTail;
      mTail = &mIndices[index];
      temp->mNext = mTail;
      mTail->mPrev = temp;
    }
    mIndices[index] = index;
    ++mSize;
  }
}

void IndexQueue::Pop() {
  if (mFront != Index::PAST_END_INDEX) {
    Index* temp = mFront;
    if (mFront == mTail) {
      mFront = Index::PAST_END_INDEX;
      mTail = mFront;
    } else {
      mFront = mFront->mNext;
      mFront->mPrev = Index::PAST_END_INDEX;
    }
    *temp = *Index::PAST_END_INDEX;
    --mSize;
  }
}

void IndexQueue::Clear() {
  while (mFront != Index::PAST_END_INDEX) {
    Pop();
  }
  mFront = Index::PAST_END_INDEX;
  mTail = Index::PAST_END_INDEX;
}

const Index& IndexQueue::Front() const {
  return *mFront;
}

const Index& IndexQueue::Back() const {
  return *mTail;
}

IdxQueueIter IndexQueue::Begin() {
  return IdxQueueIter(*mFront);
}

IdxQueueIter IndexQueue::End() {
  return *Index::PAST_END_INDEX;
}

bool IndexQueue::Empty() const {
  return (mSize == 0);
}

const IndexQueue::size_t& IndexQueue::Size() const {
  return mSize;
}

const IndexQueue::size_t& IndexQueue::MaxCap() const {
  return mMaxCap;
}

void IndexQueue::Initialize(const size_t& max_cap) {
#ifdef ENGINE_DEBUG
  assert(max_cap > 0);
  assert(mIndices == nullptr);
  DebugMessage(max_cap);
#endif
  mMaxCap = max_cap;
  DebugMessage(mMaxCap);
  mSize = max_cap;
  mIndices = new Index[mMaxCap];
  for (size_t i = 0; i < mMaxCap; ++i) {
    mIndices[i] = i;
    if (i > 0) {
      mIndices[i].mPrev = &mIndices[i - 1];
    }
    if (i < (mSize - 1)) {
      mIndices[i].mNext = &mIndices[i + 1];
    }
  }
  mFront = &mIndices[0];
  mTail = &mIndices[mMaxCap - 1];
}

IndexList::IndexList() :
  IndexQueue() {
  Clear();
}

IndexList::~IndexList() {

}

void IndexList::Remove(const Index& index) {
#ifdef ENGINE_DEBUG
  assert(mIndices != nullptr);
#endif
  if (mIndices[index] != *Index::PAST_END_INDEX) {
    Index* temp = &mIndices[index];
    if (mSize == 1) {
      Clear();
      return;
    } else if (temp == mFront) {
      mFront = mFront->mNext;
      mFront->mPrev = Index::PAST_END_INDEX;
    } else if (temp == mTail) {
      mTail = mTail->mPrev;
      mTail->mNext = Index::PAST_END_INDEX;
    } else {
      temp->mNext->mPrev = temp->mPrev;
      temp->mPrev->mNext = temp->mNext;
    }
    *temp = *Index::PAST_END_INDEX;
    --mSize;
  }
}
namespace index_queue {
} // namespace index_queue
} // namespace impl
} // namespace containers
} // namespace engine
} // namespace sd_app

