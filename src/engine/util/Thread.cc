#include "engine/util/Thread.h"
#include <iostream>
Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::operator()()
{
	mThread_id = boost::this_thread::get_id();
	EntryPoint();
}

void Thread::Launch()
{
	if (mThread_id != boost::thread::id())
	{
		throw std::runtime_error("Thread already running!");
	}
	boost::thread New_thread(boost::ref(*this));
	swap(New_thread);
}