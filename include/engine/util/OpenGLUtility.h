#ifndef OPENGL_UTILITY_HEADER_INCLUDED
#define OPENGL_UTILITY_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include"engine/util/OpenGLOptions.h"

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

class OpenGLUtility
{
public:
	static void Init();
	static GLFWwindow* InitWindow(const OpenGLOptions&);
	static void HandleKeyCB(GLFWwindow*, int, int, int, int);
	static std::pair<int, int> GetScreenResolution(GLFWmonitor* = nullptr);
	static float GetScreenHeight(GLFWmonitor* = nullptr);
	static float GetScreenWidth(GLFWmonitor* = nullptr);
	static bool KeyDown(GLFWwindow*, int);
private:
	OpenGLUtility() {}
	OpenGLUtility(const OpenGLUtility&) {}
	OpenGLUtility(OpenGLUtility&&) {}
};

#endif