#ifdef ENGINE_DEBUG

#endif
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"game/SpaceDefender.h"

#include"engine/containers/Container.h"

#ifdef ENGINE_DEBUG
Player* player;
#endif

class TestContainer :
	public Container
{
public:
	TestContainer(const unsigned int& max_cap = 10) :
		Container(),
		mMaxCap(max_cap)
	{
		Initialize(); 
	}
	~TestContainer() {}
	const unsigned int& MaxCapacity() const { return mMaxCap; }
	unsigned int mMaxCap;
};

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
	TestContainer container;
	TestContainer::iterator b = container.begin();

	while (b != container.end())
	{
		std::cout << *b << '\n';
		++b;
	}
}
