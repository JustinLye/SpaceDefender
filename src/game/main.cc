#ifdef ENGINE_DEBUG
#define COLLISION_DEBUG
#endif
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/InitOpenGL.h"
#include"engine/shapes/Triangle.h"
#include"engine/shapes/Circle.h"
#include"engine/objects/Renderer.h"

#ifdef ENGINE_DEBUG
Shape* triangle;
Shape* circle;
Renderer* renderer;
Renderer* circle_renderer;
#endif

int main(int argc, char* argv[])
{
	try
	{
		OpenGLOptions opts;
		opts.mWindowResizable = GLFW_TRUE;
		GLFWwindow* window = InitOpenGL::Initialize(opts);
#ifdef ENGINE_DEBUG
		triangle = new Triangle();
		circle = new Circle();
		renderer = new Renderer(triangle, GL_FILL);
		circle_renderer = new Renderer(circle, GL_FILL);
		circle_renderer->Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
#endif
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.8f));
			renderer->Render(glm::value_ptr(model));
			circle_renderer->Render(glm::value_ptr(glm::mat4(1.0f)));
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
