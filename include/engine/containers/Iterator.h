#ifndef ITERATOR_HEADER_INCLUDED
#define ITERATOR_HEADER_INCLUDED
#include<iterator>
#include"engine/containers/IterItem.h"

namespace sd_app {
namespace engine {
namespace containers {
namespace impl {
namespace iterator {


/** @addtogroup EngineIterators */
/*@{*/
template<class T>
class Iterator {
public:
protected:
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;

  Iterator(pointer = nullptr);
  Iterator(const Iterator&);
  virtual ~Iterator();

  reference operator*();
  pointer operator->();
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);

  bool operator==(const Iterator&) const;
  bool operator!=(const Iterator&) const;

  Iterator& operator=(const Iterator&);
protected:
  IterItem<T> mPtr;
};
/*@}*/
} // namespace iterator
} // namespace impl
template<class T>
using Iterator = impl::iterator::Iterator<T>;
} // namespace containers
} // namespace engine
} // namespace sd_app


#ifndef ITERATOR_CC_INCLUDED
#include"engine/containers/Iterator.cc"
#endif // !ITERATOR_CC_INCLUDED
#endif // !ITERATOR_HEADER_INCLUDED
