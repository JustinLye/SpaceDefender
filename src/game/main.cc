#ifdef ENGINE_DEBUG
#define COLLISION_DEBUG
#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/InitOpenGL.h"
#include"engine/shapes/Triangle.h"
#include"engine/shapes/Circle.h"
#include"engine/shapes/Quad.h"
#include"engine/objects/GameObject.h"

#ifdef ENGINE_DEBUG
Triangle* triangle;
Circle* circle;
GameObject* game_object;
#endif

int main(int argc, char* argv[])
{
	try
	{
		OpenGLOptions opts;
		GLFWwindow* window = InitOpenGL::Initialize(opts);
#ifdef ENGINE_DEBUG
		namespace chrono = std::chrono;
		triangle = new Triangle();
		circle = new Circle();
		game_object = new GameObject();
		game_object->AddRenderer(std::unique_ptr<Renderer>(new Renderer()));
		game_object->AddShape(circle);
		game_object->AddShape(triangle);
		float fixed_update_ms = Constants::Time::TARGET_FRAME_RATE_IN_MS;
		glm::mat4 proj_mat = glm::ortho(0.0f, 2560.0f, 0.0f, 1080.0f, 0.1f, 100.0f);
		//glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), 64.0f / 27.0f, 0.001f, 1000.0f);
		glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
		game_object->Scale(glm::vec3(200.0f, 200.0f, 0.0f));
		game_object->Translate(glm::vec3(1500.0f, 500.0f, 0.0f));
		game_object->Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
		game_object->Translate(glm::vec3(0.0f, -0.025f, 0.0f), circle);
		game_object->Scale(glm::vec3(1.15, 1.15f, 0.0f), circle);

		
		
		auto loop_start_time = chrono::high_resolution_clock::now();
#endif
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef ENGINE_DEBUG
			auto start_time = chrono::high_resolution_clock::now();
			game_object->Rotate(.0060f, glm::vec3(0.0f, 0.0f, 1.0f));
			
			glm::mat4 view_mat = glm::lookAt(cam_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			game_object->Render(proj_mat, view_mat);
#endif
			glfwSwapBuffers(window);
			glfwPollEvents();
#ifdef ENGINE_DEBUG
			chrono::duration<double, std::milli> elapsed = chrono::high_resolution_clock::now() - start_time;
			std::this_thread::sleep_for(chrono::milliseconds((long)(fixed_update_ms - elapsed.count())));
#endif
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
