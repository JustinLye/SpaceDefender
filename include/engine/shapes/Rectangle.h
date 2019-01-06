#ifndef RECTANGLE_HEADER_INCLUDED
#define RECTANGLE_HEADER_INCLUDED


/** @addtogroup EngineShapes */
/*@{*/
struct Origin
{
	float x;
	float y;
};

struct Size
{
	float x;
	float y;
};

struct Rectangle
{
	Origin mOrigin;
	Size mSize;
};
/*@}*/
#endif