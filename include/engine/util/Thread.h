#ifndef __THREAD_H_INCLUDED__
#define __THREAD_H_INCLUDED__

#define BOOST_THREAD_VERSION 2

#include<boost/thread/thread.hpp>
#include<boost/core/noncopyable.hpp>
#include<boost/core/ref.hpp>

class Thread :
	private boost::noncopyable,
	private boost::thread
{
public:
	using boost::thread::get_id;
	using boost::thread::join;
	using boost::thread::joinable;
	explicit Thread();
	virtual ~Thread();
	virtual void Launch();
	void operator()();
protected:
	virtual void EntryPoint() = 0;

	boost::thread::id mThread_id;
};

#endif
