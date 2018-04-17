#ifdef ENGINE_DEBUG

#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"game/SpaceDefender.h"

#ifdef ENGINE_DEBUG
Player* player;
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
			player->Strafe(Constants::Types::DIRECTION::LEFT);
		}
		break;
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		if (action != GLFW_RELEASE)
		{
			player->Strafe(Constants::Types::DIRECTION::RIGHT);
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
		SpaceDefender space_defender(opts);
		space_defender.Init();
		player = space_defender.GetPlayer();
		space_defender.Run();
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << '\n';
	}

	return EXIT_SUCCESS;
}

