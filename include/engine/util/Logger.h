#ifndef LOGGER_HEADER_INCLUDED
#define LOGGER_HEADER_INCLUDED

#include<string>
#include<fstream>
#include<map>
#include<boost/filesystem.hpp>
#include"engine/util/MailBox.h"
#include"engine/util/Thread.h"


/** @addtogroup EngineUtil */
/*@{*/
class Logger :
	public Thread
{

public:
	Logger(const char*);
	virtual ~Logger();
	
	void Log(const std::string&);
	void Close();
protected:
	bool mShutdown;
	const char* mPath;
	MailBox<std::string> mMailBox;
	std::ofstream mFile;
	
	void Open();
	void EntryPoint();
	virtual void EventLoop();
};
/*@}*/

#endif // !LOGGER_HEADER_INCLUDED
