#include"engine/util/OpenGLUtility.h"

void OpenGLUtility::Init()
{
	glfwInit();
}

GLFWwindow* OpenGLUtility::InitWindow(const OpenGLOptions& opts)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opts.mMajorV);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opts.mMinorV);
	glfwWindowHint(GLFW_OPENGL_PROFILE, opts.mProfileMode);
	glfwWindowHint(GLFW_RESIZABLE, opts.mWindowResizable);
	glfwWindowHint(GLFW_DECORATED, opts.mWindowDecorated);
	glfwWindowHint(GLFW_MAXIMIZED, opts.mWindowMaximized);
	int window_width = opts.mWindowW;
	int window_height = opts.mWindowH;
	GLFWmonitor* monitor = opts.mMonitor;
	if (!monitor)
	{
		monitor = glfwGetPrimaryMonitor();
	}
#ifdef ENGINE_DEBUG
	if (opts.mUseNativeAspectRatio)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window_width = mode->width;
		window_height = mode->height;
	}
#endif
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, opts.mWindowTitle, monitor, NULL);
	glfwMakeContextCurrent(window);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (opts.mKeyCB == nullptr)
	{
		glfwSetKeyCallback(window, OpenGLUtility::HandleKeyCB);
	}
	else
	{
		std::cout << __FUNCTION__ << '\n';
		glfwSetKeyCallback(window, opts.mKeyCB);
	}
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
	
	glPolygonMode(opts.mPolyMode.first, opts.mPolyMode.second);
	glViewport(0, 0, sw, sh);
	for (auto opt : opts.mEnableOptions)
	{
		glEnable(opt);
	}
	return window;
}

void OpenGLUtility::HandleKeyCB(GLFWwindow* window, int key, int action, int scan, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		//glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
}

std::pair<int, int> OpenGLUtility::GetScreenResolution(GLFWmonitor* monitor)
{
	if (!monitor)
	{
		monitor = glfwGetPrimaryMonitor();
	}
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!mode)
	{
		throw std::runtime_error("GLFW could not get screen resolution. Possible causes are GLFW is not initialized or a platform error occurred. Either way you should handle this exception by 1) init glfw first or 2) have backup/default resolution ready");
	}
	return std::pair<int,int>({ mode->width, mode->height });
}

float OpenGLUtility::GetScreenHeight(GLFWmonitor* monitor)
{
	return (float)GetScreenResolution(monitor).second;
}

float OpenGLUtility::GetScreenWidth(GLFWmonitor* monitor)
{
	return (float)GetScreenResolution(monitor).first;
}

bool OpenGLUtility::KeyDown(GLFWwindow* window, int key)
{
	return (glfwGetKey(window, key) != GLFW_RELEASE);
}