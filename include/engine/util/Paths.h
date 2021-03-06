#ifndef ENGINE_PATHS_HEADER_INCLUDED
#define ENGINE_PATHS_HEADER_INCLUDED
#include<string>
/** @addtogroup EngineUtil */
/*@{*/
#ifndef ENGINE_SHADER_BASE_PATH
#define ENGINE_SHADER_BASE_PATH "C:\\SpaceDefender\\shaders\\engine\\"
#define EngineShaderPath(filename) ENGINE_SHADER_BASE_PATH + std::string(filename)
#endif
#ifndef ENGINE_FONT_BASE_PATH
#define ENGINE_FONT_BASE_PATH "C:\\SpaceDefender\\font\\"
#define EngineFontPath(filename) ENGINE_FONT_BASE_PATH + std::string(filename)
#endif
#ifndef ENGINE_TEX_BASE_PATH
#define ENGINE_TEX_BASE_PATH "C:\\SpaceDefender\\textures\\"
#define EngineTexPath(filename) ENGINE_TEX_BASE_PATH + std::string(filename)
#endif

#ifndef ENGINE_LOG_BASE_PATH
#define ENGINE_LOG_BASE_PATH "C:\\SpaceDefender\\logs\\"
#define LogFilePath(filename) ENGINE_LOG_BASE_PATH + std::string(filename)
#endif // !ENGINE_LOG_BASE_PATH
/*@}*/


#endif