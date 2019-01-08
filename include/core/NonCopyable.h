#ifndef NONCOPYABLE_HEADER_INCLUDED
#define NONCOPYABLE_HEADER_INCLUDED
namespace sd_app {
namespace core {
namespace impl {
namespace noncopyable {
class NonCopyable {
public:
  NonCopyable() {}
  NonCopyable(NonCopyable&&) {}
  NonCopyable& operator=(NonCopyable&&) {}
  virtual ~NonCopyable() {}
private:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

};
} // namespace noncopyable
} // namespace impl
using NonCopyable = impl::noncopyable::NonCopyable;
} // namespace core
} // namespace sd_app

#endif // !NONCOPYABLE_HEADER_INCLUDED
