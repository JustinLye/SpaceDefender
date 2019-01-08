#ifndef CIRCLE_DATA_HEADER_INCLUDED
#define CIRCLE_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace circle_data {
/** @addtogroup EngineShapes */
/*@{*/
class CircleData :
	public ShapeData
{
public:
	CircleData();
	virtual ~CircleData();
	virtual unsigned int VertCount();
	virtual unsigned int IndexCount();
	virtual GLenum PrimType();
protected:
	virtual void InitializeData();

};
/*@}*/
} // namespace circle_data
} // namespace impl
using CircleData = impl::circle_data::CircleData;
} // namespace shapes
} // namespace engine
} // namespace sd_app
#endif