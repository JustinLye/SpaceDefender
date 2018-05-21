#ifdef ENGINE_DEBUG

#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"game/SpaceDefender.h"

#include"engine/containers/IndexQueue.h"

#ifdef ENGINE_DEBUG
Player* player;
#endif


void TestFunction();
int main(int argc, char* argv[])
{
	try
	{
		TestFunction();
		return EXIT_SUCCESS;
		OpenGLUtility::Init();
		OpenGLOptions opts;
		int monitor_count;
		GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
		opts.mMonitor = monitors[0];
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


void TestFunction()
{
	Index i;
	std::cout << i << '\n';
	std::cout << std::boolalpha << (!i) << '\n';
	Index y(10);
	std::cout << y << '\n';
	std::cout << std::boolalpha << (y == 10) << '\n';
	std::cout << std::boolalpha << (y == 11) << '\n';
	std::cout << std::boolalpha << (y == i) << '\n';
	Index z;
	std::cout << std::boolalpha << (z == i) << '\n';
	i = 10;
	std::cout << std::boolalpha << (i == 10 && i == y) << '\n';
	y = z;
	std::cout << std::boolalpha << (i == 10 && i == y) << '\n';
	Index::size_t q[3] = { 99, 42, 12 };
	y = 1;
	std::cout << q[y] << '\n';
}
