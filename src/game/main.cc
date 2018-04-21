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


int main(int argc, char* argv[])
{
	try
	{
		OpenGLUtility::Init();
		OpenGLOptions opts;
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

