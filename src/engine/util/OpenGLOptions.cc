#include"engine/util/OpenGLOptions.h"
namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace opengl_options {
const unsigned int OpenGLOptions::DEFAULT_MAJOR_V = 3;
const unsigned int OpenGLOptions::DEFAULT_MINOR_V = 3;
const unsigned int OpenGLOptions::DEFAULT_PROFILE_MODE = GLFW_OPENGL_CORE_PROFILE;
const int OpenGLOptions::DEFAULT_WINDOW_H = 1080;
const int OpenGLOptions::DEFAULT_WINDOW_W = 1600;
const char* OpenGLOptions::DEFAULT_WINDOW_TITLE = "SpaceDefender";
const int OpenGLOptions::DEFAULT_WINDOW_RESIZABLE = GLFW_FALSE;
const OpenGLPolyMode OpenGLOptions::DEFAULT_POLY_MODE = { GL_LINE, GL_LINE };
const int OpenGLOptions::DEFAULT_WINDOW_DECORATED = GLFW_FALSE;
const int OpenGLOptions::DEFAULT_WINDOW_MAXIMIZED = GLFW_TRUE;
void(*OpenGLOptions::DEFAULT_KEYCB)(GLFWwindow*, int, int, int, int) = nullptr;
void(*OpenGLOptions::DEFAULT_ERRORCB)(int, const char*) = nullptr;
void(*OpenGLOptions::DEFAULT_FOCUSDB)(GLFWwindow*, int) = nullptr;
const int OpenGLOptions::DEFAULT_USE_NATIVE_ASPECT_RATIO = GLFW_TRUE;
const GLFWmonitor* OpenGLOptions::DEFAULT_MONITOR = nullptr;
const OpenGLVersion OpenGLOptions::OPENGL_VERSION_ARRAY[OpenGLOptions::OPENGL_VERSION_COUNT] =
{
	{3, 3},
	{3, 2},
	{3, 1},
	{3, 0},
	{2, 1},
	{2, 0},
	{1, 5},
	{1, 4},
	{1, 3},
	{1, 2},
	{1, 1},
	{1, 0}
};

const bool OpenGLOptions::DEFAULT_ENABLE_VSYNC = true;

/////////////////////////////////////////////////////////////
///\ fn OpenGLOptions::OpenGLOptions()
///\ brief Default constructor
///\ author Justin Lye
///\ date 04/08/2018
/////////////////////////////////////////////////////////////
OpenGLOptions::OpenGLOptions() :
	mOpenGLVersion({ DEFAULT_MAJOR_V, DEFAULT_MINOR_V }),
	mProfileMode(DEFAULT_PROFILE_MODE),
	mWindowH(DEFAULT_WINDOW_H),
	mWindowW(DEFAULT_WINDOW_W),
	mWindowTitle(DEFAULT_WINDOW_TITLE),
	mWindowResizable(DEFAULT_WINDOW_RESIZABLE),
	mEnableOptions(std::vector<GLenum>()),
	mWindowDecorated(DEFAULT_WINDOW_DECORATED),
	mWindowMaximized(DEFAULT_WINDOW_MAXIMIZED),
	mKeyCB(DEFAULT_KEYCB),
	mErrorCB(DEFAULT_ERRORCB),
	mFocusCB(DEFAULT_FOCUSDB),
	mUseNativeAspectRatio(DEFAULT_USE_NATIVE_ASPECT_RATIO),
	mMonitor(nullptr),
	mEnableVsync(DEFAULT_ENABLE_VSYNC)
{

}
} // namespace opengl_options
} // namespace impl
} // namespace util
} // namespace engine
} // namespace sd_app

