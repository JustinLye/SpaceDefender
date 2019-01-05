#ifndef __THREAD_H_INCLUDED__
#define __THREAD_H_INCLUDED__


#include<thread>
#include<functional>

/** @addtogroup EngineUtil */
/*@{*/

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


class Thread :
	private NonCopyable,
	private std::thread
{
public:
	using std::thread::get_id;
	using std::thread::join;
	using std::thread::joinable;
	explicit Thread();
	virtual ~Thread();
	virtual void Launch();
	void operator()();
protected:
	virtual void EntryPoint() = 0;

	std::thread::id mThread_id;
};
/*@}*/
#endif
