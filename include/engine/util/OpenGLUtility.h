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
	static void HandleWindowFocusCB(GLFWwindow*, int);
	static void HandleErrorCB(int, const char*);
	static std::pair<int, int> GetScreenResolution(GLFWmonitor* = nullptr);
	static float GetScreenHeight(GLFWmonitor* = nullptr);
	static float GetScreenWidth(GLFWmonitor* = nullptr);
	static bool KeyDown(GLFWwindow*, int);
	static int GetRefreshRate(GLFWmonitor* = nullptr);
	static int LastOpenGLErrorCode();
private:
	static OpenGLOptions sOpenGLOpts;
	static int sLastOpenGLErrorCode;
	static int sVersionArrayIndex;
	static OpenGLVersion sOpenGLVersion;
	static bool sFilledInRemainingOpts;
	OpenGLUtility() {}
	OpenGLUtility(const OpenGLUtility&) {}
	OpenGLUtility(OpenGLUtility&&) {}
	static const GLFWvidmode* GetVidMode(GLFWmonitor* = nullptr);
	static void SetErrorCB();
	static void SetWindowHints();
	static void FillInRemainingOpts();
	static bool TryAgain();
	static void FinishUpInitialization(GLFWwindow*);
	
};

#endif