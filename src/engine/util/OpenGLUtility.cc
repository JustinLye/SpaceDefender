#include"engine/util/OpenGLUtility.h"

OpenGLOptions OpenGLUtility::sOpenGLOpts;
int OpenGLUtility::sLastOpenGLErrorCode = 0;
int OpenGLUtility::sVersionArrayIndex = 0;
OpenGLVersion OpenGLUtility::sOpenGLVersion = { OpenGLOptions::DEFAULT_MAJOR_V, OpenGLOptions::DEFAULT_MINOR_V };
bool OpenGLUtility::sFilledInRemainingOpts = false;
int OpenGLUtility::sRetryAttempts = 0;
const int OpenGLUtility::MAX_RETRY_ATTEMPTS = 20;

void OpenGLUtility::Init()
{
	glfwInit();
}

GLFWwindow* OpenGLUtility::InitWindow(const OpenGLOptions& opts)
{
	sOpenGLOpts = opts;
	SetErrorCB();	
	GLFWwindow* window = nullptr;
	bool try_again = true;
	while (try_again)
	{
		SetWindowHints();
		window = glfwCreateWindow(sOpenGLOpts.mWindowW, sOpenGLOpts.mWindowH, sOpenGLOpts.mWindowTitle, sOpenGLOpts.mMonitor, NULL);
		try_again = (window) ? false : TryAgain();
	}
	if (!window)
	{
		throw std::runtime_error("FATALITY!! OpenGL could not be initialized.");
	}

	FinishUpInitialization(window);
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

void OpenGLUtility::HandleWindowFocusCB(GLFWwindow* window, int focused)
{
	if (focused)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void OpenGLUtility::HandleErrorCB(int error_code, const char* description)
{
	std::cout << "OpenGL ERROR [" << error_code << "] " << description << '\n';
	sLastOpenGLErrorCode = error_code;
}

std::pair<int, int> OpenGLUtility::GetScreenResolution(GLFWmonitor* monitor)
{
	const GLFWvidmode* mode = GetVidMode(monitor);
	return std::pair<int,int>({ mode->width, mode->height });
}

int OpenGLUtility::GetRefreshRate(GLFWmonitor* monitor)
{
	const GLFWvidmode* mode = GetVidMode(monitor);
	return mode->refreshRate;
}

int OpenGLUtility::LastOpenGLErrorCode()
{
	return sLastOpenGLErrorCode;
}

const GLFWvidmode* OpenGLUtility::GetVidMode(GLFWmonitor* monitor)
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

void OpenGLUtility::SetErrorCB()
{
	if (sOpenGLOpts.mErrorCB == nullptr)
	{
		sOpenGLOpts.mErrorCB = &OpenGLUtility::HandleErrorCB;
	}
	glfwSetErrorCallback(sOpenGLOpts.mErrorCB);
}

void OpenGLUtility::SetWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, sOpenGLOpts.mOpenGLVersion.mMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, sOpenGLOpts.mOpenGLVersion.mMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, sOpenGLOpts.mProfileMode);
	glfwWindowHint(GLFW_RESIZABLE, sOpenGLOpts.mWindowResizable);
	glfwWindowHint(GLFW_DECORATED, sOpenGLOpts.mWindowDecorated);
	glfwWindowHint(GLFW_MAXIMIZED, sOpenGLOpts.mWindowMaximized);
	FillInRemainingOpts();
}

void OpenGLUtility::FillInRemainingOpts()
{
	if (sFilledInRemainingOpts)
	{
		return;
	}
	sFilledInRemainingOpts = true;
	if (sOpenGLOpts.mMonitor == nullptr)
	{
		sOpenGLOpts.mMonitor = glfwGetPrimaryMonitor();
	}
	if (sOpenGLOpts.mUseNativeAspectRatio)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(sOpenGLOpts.mMonitor);
		sOpenGLOpts.mWindowW = mode->width;
		sOpenGLOpts.mWindowH = mode->height;
	}
	if (sOpenGLOpts.mEnableVsync)
	{
		glfwSwapInterval(1);
	}
	if (sOpenGLOpts.mKeyCB == nullptr)
	{
		sOpenGLOpts.mKeyCB = &OpenGLUtility::HandleKeyCB;
	}
	if (sOpenGLOpts.mFocusCB == nullptr)
	{
		sOpenGLOpts.mFocusCB = &OpenGLUtility::HandleWindowFocusCB;
	}
}

bool OpenGLUtility::TryAgain()
{
	++sRetryAttempts;
	if (sRetryAttempts > MAX_RETRY_ATTEMPTS)
	{
		return false;
	}
	switch (sLastOpenGLErrorCode)
	{
	case GLFW_INVALID_VALUE:
		if (sOpenGLOpts.mProfileMode != GLFW_OPENGL_ANY_PROFILE)
		{
			sOpenGLOpts.mProfileMode = GLFW_OPENGL_ANY_PROFILE;
		}
		break;
	case GLFW_VERSION_UNAVAILABLE:
		++sVersionArrayIndex;
		if (sVersionArrayIndex >= OpenGLOptions::OPENGL_VERSION_COUNT)
		{
			return false;
		}
		sOpenGLOpts.mOpenGLVersion = OpenGLOptions::OPENGL_VERSION_ARRAY[sVersionArrayIndex];
		if (sOpenGLOpts.mOpenGLVersion.mMajor < 3 || (sOpenGLOpts.mOpenGLVersion.mMajor == 3 && sOpenGLOpts.mOpenGLVersion.mMajor < 3))
		{
			sOpenGLOpts.mProfileMode = GLFW_OPENGL_ANY_PROFILE;
		}
		break;
	}
	return true;

}

void OpenGLUtility::FinishUpInitialization(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, sOpenGLOpts.mKeyCB);
	glfwSetWindowFocusCallback(window, OpenGLUtility::HandleWindowFocusCB);
	
	int sw, sh;
	glfwGetFramebufferSize(window, &sw, &sh);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glPolygonMode(GL_FRONT, sOpenGLOpts.mPolyMode.FRONT);
	glPolygonMode(GL_BACK, sOpenGLOpts.mPolyMode.BACK);
	glViewport(0, 0, sw, sh);
	for (auto opt : sOpenGLOpts.mEnableOptions)
	{
		glEnable(opt);
	}
}