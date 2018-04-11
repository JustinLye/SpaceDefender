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
		game_object->AddRenderer(std::unique_ptr<Renderer>(new Renderer(triangle)));
		
		float fixed_update_ms = Constants::Time::TARGET_FRAME_RATE_IN_MS;
		glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), 64.0f / 27.0f, 0.001f, 1000.0f);
		glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
		game_object->Scale(glm::vec3(0.10, 0.10f, 0.0f));
		game_object->Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
		auto loop_start_time = chrono::high_resolution_clock::now();
		bool swap_poly = true;
		bool swap_renderer = true;
		bool swap_2 = true;
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
			if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - loop_start_time).count() > 3000)
			{
				if (swap_poly)
				{
					swap_poly = false;
					game_object->PolyMode(GL_LINE);
				}
			}
			if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - loop_start_time).count() > 6000)
			{
				if (swap_renderer)
				{
					swap_renderer = false;
					game_object->AddRenderer(std::make_unique<Renderer>(circle));
				}
			}
			if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - loop_start_time).count() > 9000)
			{
				if (swap_2)
				{
					swap_2 = false;
					game_object->AddRenderer(std::make_unique<Renderer>(new Quad()));
				}
			}
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
