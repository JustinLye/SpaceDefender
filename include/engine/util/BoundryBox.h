#ifndef BOUNDRY_BOX_HEADER_INCLUDED
#define BOUNDRY_BOX_HEADER_INCLUDED


namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace boundry_box {

/** @addtogroup EngineUtil */
/*@{*/

struct BoundryBox
{
	float mLeft;
	float mRight;
	float mBottom;
	float mTop;
};
/*@}*/
}// namespace boundry_box
}// namespace impl
using BoundryBox = impl::boundry_box::BoundryBox;
}// namespace util
}// namespace engine
}// namespace sd_app
#endif