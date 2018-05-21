#ifndef DEBUG_FUNCTIONS_HEADER_INCLUDED
#define DEBUG_FUNCTIONS_HEADER_INCLUDED

#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace engine
{
	namespace debug
	{
		void Print4x4Matrix(glm::mat4);
		void Print4x4Matrix(const float*);		
	}

#ifndef DEBUG_MESSAGE
#define DebugMessage(msg) std::cout << __FILE__ << "    " << __FUNCTION__ << " [" << __LINE__ << "] " << msg << '\n';
#endif
};

#endif