#ifndef MAIL_BOX_CC_INCLUDED
#define MAIL_BOX_CC_INCLUDED

#include"engine/util/MailBox.h"

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace mailbox {

#ifdef BUILD_MAIL_BOX_CC
#endif

///////////////////////////////////////////////
///\ fn MailBox<T>::Empty() const
///\ returns true if box is empty
///\ author Justin Lye
///\ date 03/21/2018
///////////////////////////////////////////////

template<class T>
inline bool MailBox<T>::Empty() const
{
	return empty();
}

template<class T>
MailBox<T>::MailBox() :
	std::queue<T>()
{

}

template<class T>
T MailBox<T>::GetMail()
{
	std::unique_lock<std::mutex> lockbox(mCheckMailMtx);
	while (empty())
	{
		mMailReceivedEvent.wait(lockbox);
	}
	T mail = front();
	pop();
	return mail;
}

template<class T>
void MailBox<T>::AcceptMail(T mail)
{
	std::unique_lock<std::mutex> lockbox(mCheckMailMtx);
	try
	{
		push(mail);
	} catch (std::exception& error)
	{
		throw std::runtime_error(error.what());
	} catch (...)
	{
		throw std::runtime_error("Unknown error thrown");
	}
	mMailReceivedEvent.notify_all();
}
} // namespace mailbox
} // namespace impl
} // namespace util
} // namespace engine
} // namespace sd_app

#endif