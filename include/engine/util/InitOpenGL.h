#ifndef INIT_OPENGL_HEADER_INCLUDED
#define INIT_OPENGL_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include"engine/util/OpenGLOptions.h"

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

class InitOpenGL
{
public:
	static GLFWwindow* Initialize(const OpenGLOptions&);
	static void HandleKeyCB(GLFWwindow*, int, int, int, int);
	static std::pair<int, int> GetScreenResolution(GLFWmonitor* = nullptr);
private:
	InitOpenGL() {}
	InitOpenGL(const InitOpenGL&) {}
	InitOpenGL(InitOpenGL&&) {}
};

#endif