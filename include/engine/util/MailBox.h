#ifndef MAIL_BOX_HEADER_INCLUDED
#define MAIL_BOX_HEADER_INCLUDED

#include<queue>
#include<mutex>
#include<condition_variable>

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace mailbox {
//////////////////////////////////////////////////
///\ class MailBox
///\ brief Used to send and receive messages
///\ author Justin Lye
///\ date 3/21/2018
//////////////////////////////////////////////////
/** @addtogroup EngineUtil */
/*@{*/
template<class T>
class MailBox : private std::queue<T> {
  std::mutex mCheckMailMtx; ///< Exculsive access to send and receive mail
  std::condition_variable mMailReceivedEvent; ///< Notification when mailbox access is avail.
  using std::queue<T>::empty;
  using std::queue<T>::front;
  using std::queue<T>::pop;
  using std::queue<T>::push;
public:
  MailBox(); ///< Default constructor
  T GetMail(); ///< Pull next message from box
  void AcceptMail(T); ///< Receive a message into the box
  bool Empty() const; ///< Returns true if box is empty
};
/*@}*/
} // namespace mailbox
} // namespace impl
template<class T>
using MailBox = impl::mailbox::MailBox<T>;
} // namespace util
} // namespace engine
} // namespace sd_app
#ifndef MAIL_BOX_CC_INCLUDED
#include"engine/util/MailBox.cc"
#endif

#endif