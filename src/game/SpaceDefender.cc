#include"game/SpaceDefender.h"

SpaceDefender::SpaceDefender(const OpenGLOptions& opts) :
	mOptions(opts),
	mPlayer(nullptr),
	mWindow(nullptr),
	mAstroidSpawner(nullptr)
{

}

SpaceDefender::~SpaceDefender()
{
}

void SpaceDefender::Init()
{
	InitSys();
	InitBoundries();
	InitShapeData();
	InitShapes();
	InitShaders();
	InitPlayer();
	InitAstroids();
	InitCollisionDetection();
}

void SpaceDefender::Run()
{
	glm::mat4 proj_mat = glm::ortho(0.0f, OpenGLUtility::GetScreenWidth(mOptions.mMonitor), 0.0f, OpenGLUtility::GetScreenHeight(mOptions.mMonitor), 0.1f, 100.0f);
	while (!glfwWindowShouldClose(mWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 view_mat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mPlayer->Update(1.0f / 60.0f);
		mPlayer->Render(proj_mat, view_mat);
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

Player* SpaceDefender::GetPlayer()
{
	return mPlayer;
}

GLFWwindow* SpaceDefender::GetWindow()
{
	return mWindow;
}

void SpaceDefender::Update(const float& dt)
{
	mPlayer->Update(dt);
	mAstroidSpawner->Update(dt);
}

void SpaceDefender::DoCollisionDetection()
{
	
}

void SpaceDefender::InitSys()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	OpenGLUtility::Init();
	mWindow = OpenGLUtility::InitWindow(mOptions);
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitBoundries()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	mBoundries.mLeft = 0.0f;
	mBoundries.mRight = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	mBoundries.mBottom = 0.0f;
	mBoundries.mTop = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitShapeData()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	mShapeData[Constants::Types::shape_t::CIRCLE] = new CircleData();
	mShapeData[Constants::Types::shape_t::LINE_SEG] = new LineSegmentData();
	mShapeData[Constants::Types::shape_t::QUAD] = new QuadData();
	mShapeData[Constants::Types::shape_t::TRIANGLE] = new TriangleData();
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitShapes()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
}

void SpaceDefender::InitShaders()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG] = new ShaderProgram();
	mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]->Init();
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitPlayer()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	Shape* ship = new Shape();
	ship->Buffer(mShapeData[Constants::Types::shape_t::TRIANGLE]);
	Shape* laser = new Shape();
	laser->Buffer(mShapeData[Constants::Types::shape_t::LINE_SEG]);
	LaserCannon* laser_cannon = new LaserCannon(laser, mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]);
	laser_cannon->LaserTermYPos(mBoundries.mTop * 1.05f);
	Renderer* renderer = new Renderer(mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG], GL_FILL);
	Collider* collider = new Collider();
	mPlayer = new Player();
	mPlayer->AddRenderer(renderer);
	mPlayer->AddShape(ship);
	mPlayer->AddCollider(collider);
	mPlayer->AttachCannon(laser_cannon);
	mPlayer->Scale(200.0f);
	mPlayer->Translate(glm::vec3(500.0f, 50.0f, 0.0f));
#ifdef COLLISION_DEBUG
	Shape* detection_circle = new Shape();
	detection_circle->Buffer(mShapeData[Constants::Types::shape_t::CIRCLE]);
	mPlayer->AddShape(detection_circle);
#endif
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitAstroids()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	Shape* astroid = new Shape();
	astroid->Buffer(mShapeData[Constants::Types::shape_t::CIRCLE]);

	mAstroidSpawner = new AstroidSpawner(astroid, mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]);
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " AstriodSpawner constructed...\n";
#endif
	mAstroidSpawner->MaxProjectileSpeed(100.0f);
	mAstroidSpawner->MinProjectileSpeed(50.0f);
	mAstroidSpawner->MaxScale(2.0f);
	mAstroidSpawner->MinScale(0.50f);
	mAstroidSpawner->MinRespawnWaitTime(300);
	mAstroidSpawner->MaxRespawnWaitTime(700);
	mAstroidSpawner->ProbabilityOfSpawn(30.0f);
	mAstroidSpawner->MaxXPos(mBoundries.mRight - (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->MinXPos(mBoundries.mLeft + (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->StartingYPos(mBoundries.mTop + (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->TerminateYPos(mBoundries.mBottom - (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}

void SpaceDefender::InitCollisionDetection()
{
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " starting...\n";
#endif
	mCollisionDetector = new CollisionDetector();
	mAstroidSpawner->AddObserver(mCollisionDetector);
	mPlayer->AddObserver(mCollisionDetector);
#ifdef ENGINE_DEBUG
	std::cout << __FUNCTION__ << " complete...\n";
#endif
}