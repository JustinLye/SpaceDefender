#include"engine/util/OpenGLOptions.h"

const unsigned int OpenGLOptions::DEFAULT_MAJOR_V = 3;
const unsigned int OpenGLOptions::DEFAULT_MINOR_V = 3;
const unsigned int OpenGLOptions::DEFAULT_PROFILE_MODE = GLFW_OPENGL_CORE_PROFILE;
const int OpenGLOptions::DEFAULT_WINDOW_H = 1080;
const int OpenGLOptions::DEFAULT_WINDOW_W = 1600;
const char* OpenGLOptions::DEFAULT_WINDOW_TITLE = "SpaceDefender";
const int OpenGLOptions::DEFAULT_WINDOW_RESIZABLE = GLFW_FALSE;
const std::pair<GLenum, GLenum> OpenGLOptions::DEFAULT_POLY_MODE = { GL_FRONT_AND_BACK, GL_LINE };
const int OpenGLOptions::DEFAULT_WINDOW_DECORATED = GLFW_FALSE;
const int OpenGLOptions::DEFAULT_WINDOW_MAXIMIZED = GLFW_TRUE;
void(*OpenGLOptions::DEFAULT_KEYCB)(GLFWwindow*, int, int, int, int) = nullptr;

/////////////////////////////////////////////////////////////
///\ fn OpenGLOptions::OpenGLOptions()
///\ brief Default constructor
///\ author Justin Lye
///\ date 04/08/2018
/////////////////////////////////////////////////////////////
OpenGLOptions::OpenGLOptions() :
	mMajorV(DEFAULT_MAJOR_V),
	mMinorV(DEFAULT_MINOR_V),
	mProfileMode(DEFAULT_PROFILE_MODE),
	mWindowH(DEFAULT_WINDOW_H),
	mWindowW(DEFAULT_WINDOW_W),
	mWindowTitle(DEFAULT_WINDOW_TITLE),
	mWindowResizable(DEFAULT_WINDOW_RESIZABLE),
	mEnableOptions(std::vector<GLenum>()),
	mWindowDecorated(DEFAULT_WINDOW_DECORATED),
	mWindowMaximized(DEFAULT_WINDOW_MAXIMIZED),
	mKeyCB(DEFAULT_KEYCB)
{

}