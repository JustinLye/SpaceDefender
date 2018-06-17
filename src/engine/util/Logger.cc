#include"engine/util/Logger.h"

Logger::Logger(const char* path) :
	mShutdown(false),
	mPath(path)
{
	Open();
}

Logger::~Logger()
{
}

void Logger::Log(const std::string& msg)
{
	mMailBox.AcceptMail(msg);
}

void Logger::Close()
{
	mShutdown = true;
	Log("Shutting down");
}

void Logger::Open()
{
	assert(mPath != "");
	mFile.open(mPath);
	assert(mFile.is_open());
}

void Logger::EntryPoint()
{
	EventLoop();
}

void Logger::EventLoop()
{
	while (!mShutdown)
	{
		std::string str = mMailBox.GetMail();
		mFile << str << '\n';
	}
}