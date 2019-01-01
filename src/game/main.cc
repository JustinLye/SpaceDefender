#ifdef ENGINE_DEBUG

#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"game/SpaceDefender.h"

#include"engine/containers/IndexQueue.h"
#include"engine/util/UtiliDefs.h"
Player* player;
void TestFunction();
int main(int argc, char* argv[])
{
	try
	{
		/*TestFunction();
		return EXIT_SUCCESS;*/
		OpenGLUtility::Init();
		OpenGLOptions opts;
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		opts.mMonitor = monitors[0];
		SpaceDefender space_defender(opts);
		space_defender.Init();
		//??????
		player = space_defender.GetPlayer();
		//??????
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
	float a = VecToVecAngle({ 2.0f, 1.0f, -2.0f }, { 1.0f, 1.0f, 1.0f });
	std::cout << a << '\n';
	a = RadToDeg(a);
	std::cout << a << '\n';
}
