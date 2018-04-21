#ifndef CONSTANTS_HEADER_INCLUDED
#define CONSTANTS_HEADER_INCLUDED
#include<string>
#include<glm/glm.hpp>

namespace Constants
{
	namespace Shaders
	{
		const int VERTEX_ATTRIB_POS = 0; ///< all vertex shaders used to render Shapes must have the vertex attribute location = 0
		const std::string DFLT_VERTEX_SHADER = "position.vert";
		const std::string DFLT_FRAGMENT_SHADER = "unicolor.frag";
		const std::string DFLT_COLOR_UNIFORM_NAME = "Color";
		const std::string DFLT_VERTEX_ATTRIB_NAME = "vVertex";
		const std::string DFLT_MVP_UNIFORM_NAME = "MVP";
		const std::string LASER_VERTEX_SHADER_NAME = "position.vert";
		const std::string LASER_FRAGMENT_SHADER_NAME = "unicolor.frag";
	}
	namespace Rendering
	{
		const glm::vec4 DFLT_SHAPE_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	namespace Geometry
	{
		const glm::mat4 IDENTITY_MATRIX = glm::mat4(1.0f);
	}
	namespace Time
	{
		const float TARGET_FRAME_RATE_IN_MS = 16.0f;
	}
	namespace Input
	{
		enum KEY_STATE : unsigned int
		{
			UNKNOWN,
			PRESSED,
			RELEASED,
			DOWN,
			UP
		};
	}
	namespace Types
	{
		enum DIRECTION : unsigned int
		{
			LEFT,
			RIGHT
		};
		enum shape_t : unsigned int
		{
			LINE_SEG,
			TRIANGLE,
			CIRCLE,
			QUAD,
			TOTAL_SHAPES
		};
		enum shader_prog_t : unsigned int
		{
			DEFAULT_SHADER_PROG,
			TOTAL_SHADERS
		};
		
		enum event_t : unsigned int
		{
			ACTIVATED_COLLIDABLE_OBJECT,
			TERMINATED_COLLIDABLE_OBJECT,
			OBJECT_OUT_OF_BOUNDS,
			COLLISION_REPORTED,
			TOTAL_EVENTS
		};

		enum object_t : unsigned int
		{
			GENERIC_OBJECT,
			LASER,
			ASTROID,
			PLAYER,
			TOTAL_GAME_OBJECT_TYPES
		};
	}
};


#endif