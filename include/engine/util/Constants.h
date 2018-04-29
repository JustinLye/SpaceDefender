#ifndef CONSTANTS_HEADER_INCLUDED
#define CONSTANTS_HEADER_INCLUDED
#include<string>
#include<glad/glad.h>
#include<glm/glm.hpp>

namespace Constants
{
	namespace Shaders
	{
		const int VERTEX_ATTRIB_POS = 0; ///< all vertex shaders used to render Shapes must have the vertex attribute location = 0
		const std::string DFLT_VERTEX_SHADER = "position.vert";
		const std::string DFLT_FRAGMENT_SHADER = "unicolor.frag";
		const std::string TEXT_VERTEX_SHADER = "text.vert";
		const std::string TEXT_FRAGMENT_SHADER = "text.frag";
		const std::string DFLT_COLOR_UNIFORM_NAME = "Color";
		const std::string TEXT_COLOR_UNIFORM_NAME = "TextColor";
		const std::string DFLT_VERTEX_ATTRIB_NAME = "vVertex";
		const std::string TEXT_PROJ_UNIFORM_NAME = "Projection";
		const std::string DFLT_MVP_UNIFORM_NAME = "MVP";
		const std::string LASER_VERTEX_SHADER_NAME = "position.vert";
		const std::string LASER_FRAGMENT_SHADER_NAME = "unicolor.frag";
		const std::string DFLT_PROJ_UNIFORM_NAME = "Projection";
	}
	namespace Rendering
	{
		const glm::vec4 DFLT_SHAPE_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		const GLenum DFLT_POLY_MODE = GL_LINES;
		const glm::vec4 SCORE_TEXT_COLOR = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	namespace Geometry
	{
		const glm::mat4 IDENTITY_MATRIX = glm::mat4(1.0f);
	}
	namespace Time
	{
		const float TARGET_FRAME_RATE_IN_MS = 16.0f;
	}
	namespace Physics
	{
		const float DFLT_MASS = 1.0f;
		const float DFLT_DAMPING = 0.999f;
	}
	namespace Font
	{
		const std::string SCORE_FONT_FILENAME = "arial.ttf";
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
			TEXT_SHADER_PROG,
			TOTAL_SHADERS
		};
		
		enum event_t : unsigned int
		{
			ACTIVATED_COLLIDABLE_OBJECT,
			TERMINATED_COLLIDABLE_OBJECT,
			OBJECT_OUT_OF_BOUNDS,
			COLLISION_REPORTED,
			ASTROID_TO_ASTROID_COLLISION,
			PLAYER_DESTROYED_ASTROID,
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

		enum font_data_t : unsigned int
		{
			ARIAL_FONT_DATA,
			TOTAL_FONT_DATA_TYPES
		};

		enum font_t : unsigned int
		{
			SCORE_FONT,
			PAUSE_FONT,
			TOTAL_GAME_FONT_TYPES
		};
		enum game_state_t : unsigned int
		{
			INIT_GAME_STATE,
			ACTIVE_GAMEPLAY,
			PAUSED,
			TOTAL_GAME_STATE_TYPES
		};
	}
};


#endif