#include"engine/util/InitOpenGL.h"
int main(int argc, char* argv[])
{
	OpenGLOptions opts;
	GLFWwindow* window = InitOpenGL::Initialize(opts);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
