#ifndef MAIL_BOX_HEADER_INCLUDED
#define MAIL_BOX_HEADER_INCLUDED

#include<queue>
#include<mutex>
#include<condition_variable>

//////////////////////////////////////////////////
///\ class MailBox
///\ brief Used to send and receive messages
///\ author Justin Lye
///\ date 3/21/2018
//////////////////////////////////////////////////

template<typename T>
class MailBox : private std::queue<T>
{
	std::mutex mCheckMailMtx; ///< Exculsive access to send and receive mail
	std::condition_variable mMailReceivedEvent; ///< Notification when mailbox access is avail.
public:
	MailBox(); ///< Default constructor
	T GetMail(); ///< Pull next message from box
	void AcceptMail(T); ///< Receive a message into the box
	bool Empty() const; ///< Returns true if box is empty
};

#ifndef MAIL_BOX_CC_INCLUDED
#include"engine/util/MailBox.cc"
#endif

#endif