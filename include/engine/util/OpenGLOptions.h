#ifndef OPENGL_OPTIONS_HEADER_INCLUDED
#define OPENGL_OPTIONS_HEADER_INCLUDED

#include<string>
#include<vector>
#include<glad/glad.h>
#include<glfw/glfw3.h>

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace opengl_options {
/** @addtogroup EngineUtil */
/*@{*/
/////////////////////////////////////////////////////////
///\ struct OpenGLVersion
///\ brief Used to hold major and minor OpenGL verion
///\ author Justin Lye
///\ date 05/21/2018
/////////////////////////////////////////////////////////
struct OpenGLVersion {
  int mMajor;
  int mMinor;
};

/////////////////////////////////////////////////////////
///\ struct OpenGLPolyMode
///\ brief Used to hold front and back poly modes
///\ author Justin Lye
///\ date 05/21/2018
/////////////////////////////////////////////////////////
struct OpenGLPolyMode {
  enum face_t {
    FRONT,
    BACK
  };
  int mPolyMode[2];
  int& operator[](const face_t& face) { return mPolyMode[face]; }
  const int& operator[](const face_t& face) const { return mPolyMode[face]; }
};


/////////////////////////////////////////////////////////
///\ struct OpenGLOptions
///\ brief Used to specific OpenGL init options
///\ author Justin Lye
///\ date 04/08/2018
/////////////////////////////////////////////////////////
struct OpenGLOptions {
  // Constants
  static const unsigned int DEFAULT_MAJOR_V;
  static const unsigned int DEFAULT_MINOR_V;
  static const unsigned int DEFAULT_PROFILE_MODE;
  static const int DEFAULT_WINDOW_H;
  static const int DEFAULT_WINDOW_W;
  static const char* DEFAULT_WINDOW_TITLE;
  static const int DEFAULT_WINDOW_RESIZABLE;
  static const OpenGLPolyMode DEFAULT_POLY_MODE;
  static const int DEFAULT_WINDOW_MAXIMIZED;
  static const int DEFAULT_WINDOW_DECORATED;
  static void(*DEFAULT_KEYCB)(GLFWwindow*, int, int, int, int);
  static void(*DEFAULT_ERRORCB)(int, const char*);
  static void(*DEFAULT_FOCUSDB)(GLFWwindow*, int);
  static const int DEFAULT_USE_NATIVE_ASPECT_RATIO;
  static const GLFWmonitor* DEFAULT_MONITOR;
  static constexpr int OPENGL_VERSION_COUNT = 12;
  static const OpenGLVersion OPENGL_VERSION_ARRAY[OPENGL_VERSION_COUNT];
  static const bool DEFAULT_ENABLE_VSYNC;
  // Members
  OpenGLVersion mOpenGLVersion; ///< OpenGLVersion
  unsigned int mProfileMode; ///< OpenGL profile mode
  int mWindowH; ///< Init window height
  int mWindowW; ///< Init window width
  const char* mWindowTitle; ///< Window title
  int mWindowResizable; ///< Specifies if window can be resized
  OpenGLPolyMode mPolyMode; ///< Specifies init polymode
  std::vector<GLenum> mEnableOptions; ///< Vector of glEnable() options
  int mWindowMaximized;
  int mWindowDecorated;
  int mUseNativeAspectRatio;
  GLFWmonitor* mMonitor;
  void(*mKeyCB)(GLFWwindow*, int, int, int, int); ///< Key callback
  void(*mErrorCB)(int, const char*); ///< GLFW error callback
  void(*mFocusCB)(GLFWwindow*, int); ///< Window focus callback
  bool mEnableVsync; ///< Set swap interval to 1

  // Methods
  OpenGLOptions(); ///< Default constructor
};
/*@}*/

} // namespace opengl_options
} // namespace impl
using OpenGLVersion = impl::opengl_options::OpenGLVersion;
using OpenGLPolyMode = impl::opengl_options::OpenGLPolyMode;
using OpenGLOptions = impl::opengl_options::OpenGLOptions;
} // namespace util
} // namespace engine
} // namespace sd_app



#endif // !OPENGL_OPTIONS_HEADER_INCLUDED
