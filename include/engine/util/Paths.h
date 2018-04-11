#ifndef ENGINE_PATHS_HEADER_INCLUDED
#define ENGINE_PATHS_HEADER_INCLUDED
#include<string>
#include<boost/lexical_cast.hpp>
#ifndef ENGINE_SHADER_BASE_PATH
#define ENGINE_SHADER_BASE_PATH "C:\\SpaceDefender\\shaders\\engine\\"
#define EngineShaderPath(filename) ENGINE_SHADER_BASE_PATH + boost::lexical_cast<std::string>(filename)
#endif
#endif