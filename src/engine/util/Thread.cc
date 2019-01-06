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
	mThread_id = std::this_thread::get_id();
	EntryPoint();
}

void Thread::Launch()
{
	if (mThread_id != std::thread::id())
	{
		throw std::runtime_error("Thread already running!");
	}
	std::thread New_thread(std::ref(*this));
	swap(New_thread);
}