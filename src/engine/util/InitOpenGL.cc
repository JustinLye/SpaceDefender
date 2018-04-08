#include"engine/util/InitOpenGL.h"

GLFWwindow* InitOpenGL::Initialize(const OpenGLOptions& opts)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opts.mMajorV);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opts.mMinorV);
	glfwWindowHint(GLFW_OPENGL_PROFILE, opts.mProfileMode);
	glfwWindowHint(GLFW_RESIZABLE, opts.mWindowResizable);
	glfwWindowHint(GLFW_DECORATED, opts.mWindowDecorated);
	glfwWindowHint(GLFW_MAXIMIZED, opts.mWindowMaximized);
	
	GLFWwindow* window = glfwCreateWindow(opts.mWindowW, opts.mWindowH, opts.mWindowTitle, glfwGetPrimaryMonitor(), NULL);
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);
	if (opts.mKeyCB == nullptr)
	{
		glfwSetKeyCallback(window, InitOpenGL::HandleKeyCB);
	}
	else
	{
		glfwSetKeyCallback(window, opts.mKeyCB);
	}
	glfwMakeContextCurrent(window);
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

void InitOpenGL::HandleKeyCB(GLFWwindow* window, int key, int action, int scan, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
}