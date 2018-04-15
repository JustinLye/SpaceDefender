#ifdef ENGINE_DEBUG
#define COLLISION_DEBUG
#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/OpenGLUtility.h"
#include"engine/shapes/TriangleData.h"
#include"engine/shapes/CircleData.h"
#include"engine/shapes/QuadData.h"
#include"engine/shapes/LineSegmentData.h"
#include"game/Player.h"

#ifdef ENGINE_DEBUG
TriangleData* triangle_data;
Shape* triangle;
Shape* circle;
CircleData* circle_data;
LineSegmentData* line_seg_data;
Shape* laser;
Player* player;
ShaderProgram* shader_prog;
LaserCannon* laser_cannon;
#endif
void HandleKey(GLFWwindow*, int, int, int, int);
void HandleKey(GLFWwindow* window, int key, int scan, int action, int mods)
{
	
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		if (action != GLFW_RELEASE)
		{
			player->Strafe(Constants::Movement::DIRECTION::LEFT);
		}
		break;
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		if (action != GLFW_RELEASE)
		{
			player->Strafe(Constants::Movement::DIRECTION::RIGHT);
		}
		break;
	case GLFW_KEY_SPACE:
		if (action != GLFW_RELEASE)
		{
			player->FireCannon();
		}
		break;
	}
}
int main(int argc, char* argv[])
{
	try
	{
		OpenGLUtility::Init();
		OpenGLOptions opts;
		opts.mKeyCB = HandleKey;
		int monitor_count;
		GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
		opts.mMonitor = monitors[1];
		GLFWwindow* window = OpenGLUtility::InitWindow(opts);
#ifdef ENGINE_DEBUG
		namespace chrono = std::chrono;
		float fixed_update_ms = Constants::Time::TARGET_FRAME_RATE_IN_MS;
		float sw, sh;
		std::pair<int, int> screen_dims = OpenGLUtility::GetScreenResolution(opts.mMonitor);
		sw = (float)screen_dims.first;
		sh = (float)screen_dims.second;
		glm::mat4 proj_mat = glm::ortho(0.0f, sw, 0.0f, sh, 0.1f, 100.0f);
		glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
		
		triangle_data = new TriangleData();
		circle_data = new CircleData();
		line_seg_data = new LineSegmentData();
		triangle = new Shape();
		circle = new Shape();
		Shape* line_seg = new Shape();
		shader_prog = new ShaderProgram();
		shader_prog->Init();
		Renderer* renderer = new Renderer(shader_prog, GL_FILL);
		triangle->Buffer(triangle_data);
		circle->Buffer(circle_data);
		line_seg->Buffer(line_seg_data);
		player = new Player();
		player->AddRenderer(renderer);
		player->AddShape(triangle);
		player->AddShape(circle);
		player->Offset(glm::vec3(0.0f, 0.005f * sh, 0.0f), triangle);
		player->Scale(50.0f);
		player->Translate(glm::vec3(sw/2.0f, 0.05f * sh, 0.0f));
		
		laser = new Shape();
		laser->Buffer(line_seg_data);
		laser_cannon = new LaserCannon(laser, shader_prog);
		laser_cannon->CooldownTime(400.0f);
		laser_cannon->ProjectileSpeed(100.0f);
		player->AttachCannon(laser_cannon);

		auto loop_start_time = chrono::high_resolution_clock::now();
		int counter = 0;
#endif
		chrono::duration<double, std::milli> elapsed = chrono::milliseconds(0);
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef ENGINE_DEBUG
			auto start_time = chrono::high_resolution_clock::now();
			glm::mat4 view_mat = glm::lookAt(cam_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			player->Update(elapsed.count()/1000.0f);
			player->Render(proj_mat, view_mat);
#endif
			glfwSwapBuffers(window);
			glfwPollEvents();
#ifdef ENGINE_DEBUG
			elapsed = chrono::high_resolution_clock::now() - start_time;
			//std::this_thread::sleep_for(chrono::milliseconds((long)(fixed_update_ms - elapsed.count())));
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

