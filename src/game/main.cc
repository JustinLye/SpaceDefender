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
		/*TestFunction();
		return EXIT_SUCCESS;*/
		OpenGLUtility::Init();
		OpenGLOptions opts;
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
}
