#ifndef OPENGL_OPTIONS_HEADER_INCLUDED
#define OPENGL_OPTIONS_HEADER_INCLUDED

#include<string>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

/////////////////////////////////////////////////////////
///\ struct OpenGLOptions
///\ brief Used to specific OpenGL init options
///\ author Justin Lye
///\ date 04/08/2018
/////////////////////////////////////////////////////////
struct OpenGLOptions
{
	// Constants
	static const unsigned int DEFAULT_MAJOR_V;
	static const unsigned int DEFAULT_MINOR_V;
	static const unsigned int DEFAULT_PROFILE_MODE;
	static const int DEFAULT_WINDOW_H;
	static const int DEFAULT_WINDOW_W;
	static const char* DEFAULT_WINDOW_TITLE;
	static const int DEFAULT_WINDOW_RESIZABLE;
	static const std::pair<GLenum, GLenum> DEFAULT_POLY_MODE;
	static const int DEFAULT_WINDOW_MAXIMIZED;
	static const int DEFAULT_WINDOW_DECORATED;
	static void(*DEFAULT_KEYCB)(GLFWwindow*, int, int, int, int);
	// Members
	unsigned int mMajorV; ///< OpenGL Major version number
	unsigned int mMinorV; ///< OpenGL Minor version number
	unsigned int mProfileMode; ///< OpenGL profile mode
	int mWindowH; ///< Init window height
	int mWindowW; ///< Init window width
	const char* mWindowTitle; ///< Window title
	int mWindowResizable; ///< Specifies if window can be resized
	std::pair<GLenum, GLenum> mPolyMode; ///< Specifies init polymode
	std::vector<GLenum> mEnableOptions; ///< Vector of glEnable() options
	int mWindowMaximized;
	int mWindowDecorated;
	void(*mKeyCB)(GLFWwindow*, int, int, int, int); ///< Key callback

	// Methods
	OpenGLOptions(); ///< Default constructor
};


#endif // !OPENGL_OPTIONS_HEADER_INCLUDED
