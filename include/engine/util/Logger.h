#ifndef LOGGER_HEADER_INCLUDED
#define LOGGER_HEADER_INCLUDED

#include<string>
#include<fstream>
#include<map>
#include<cassert>
#include"engine/util/MailBox.h"
#include"engine/util/Thread.h"


namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace logger {

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
} // namespace logger
} // namespace impl
using Logger = impl::logger::Logger;
} // namespace util
} // namespace engine
} // namespace sd_app
#endif // !LOGGER_HEADER_INCLUDED
