#ifndef ITER_ITEM_HEADER_INCLUDED
#define ITER_ITEM_HEADER_INCLUDED


namespace sd_app {
namespace engine {
namespace containers {
namespace impl {
namespace iter_item {
/** @addtogroup EngineIterators */
/*@{*/
template<class T>
struct IterItem {
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;

  IterItem(pointer);
  IterItem(const IterItem&);
  virtual ~IterItem();

  reference operator*();
  pointer operator->();
  IterItem& operator++();
  IterItem operator++(int);
  IterItem& operator--();
  IterItem operator--(int);

  bool operator==(const IterItem&) const;
  bool operator==(const T*) const;
  bool operator!=(const IterItem&) const;
  bool operator!=(const T*) const;

  IterItem& operator=(const IterItem&);

  T* mPtr;
  IterItem* mPrev;
  IterItem* mNext;
};
/*@}*/
} // namespace iter_item
} // namespace impl
using IterItem = impl::iter_item::IterItem;
} // namespace containers
} // namespace engine
} // namespace sd_app


#ifndef ITER_ITEM_CC_INCLUDED
#include"engine/containers/IterItem.cc"
#endif // !ITER_ITEM_CC_INCLUDED
#endif // !ITER_ITEM_HEADER_INCLUDED
