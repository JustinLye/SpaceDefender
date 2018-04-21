#include"game/SpaceDefender.h"

SpaceDefender::SpaceDefender(const OpenGLOptions& opts) :
	mOptions(opts),
	mPlayer(nullptr),
	mWindow(nullptr),
	mAstroidSpawner(nullptr),
	mViewMat(Constants::Geometry::IDENTITY_MATRIX),
	mProjMat(Constants::Geometry::IDENTITY_MATRIX)
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
	
	while (!glfwWindowShouldClose(mWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		HandleInput();
		Update(1.0f / 60.0f);
		DoCollisionDetection();
		Render();
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

void SpaceDefender::Render()
{
	mPlayer->Render(mProjMat, mViewMat);
	mAstroidSpawner->Render(mProjMat, mViewMat);
}

void SpaceDefender::DoCollisionDetection()
{
	mCollisionDetector->DoDetection();
}

void SpaceDefender::InitSys()
{
	OpenGLUtility::Init();
	mWindow = OpenGLUtility::InitWindow(mOptions);
}

void SpaceDefender::InitBoundries()
{
	mBoundries.mLeft = 0.0f;
	mBoundries.mRight = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	mBoundries.mBottom = 0.0f;
	mBoundries.mTop = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);

	mProjMat = glm::ortho(0.0f, mBoundries.mRight, 0.0f, mBoundries.mTop, 0.1f, 100.0f);
	mViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void SpaceDefender::InitShapeData()
{
	mShapeData[Constants::Types::shape_t::CIRCLE] = new CircleData();
	mShapeData[Constants::Types::shape_t::LINE_SEG] = new LineSegmentData();
	mShapeData[Constants::Types::shape_t::QUAD] = new QuadData();
	mShapeData[Constants::Types::shape_t::TRIANGLE] = new TriangleData();
}

void SpaceDefender::InitShapes()
{
}

void SpaceDefender::InitShaders()
{
	mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG] = new ShaderProgram();
	mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]->Init();
}

void SpaceDefender::InitPlayer()
{
	float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	float sh = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);
	Shape* ship = new Shape();
	ship->Buffer(mShapeData[Constants::Types::shape_t::TRIANGLE]);

	// Setup laser cannon
	Shape* laser = new Shape();
	laser->Buffer(mShapeData[Constants::Types::shape_t::LINE_SEG]);
	LaserCannon* laser_cannon = new LaserCannon(laser, mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]);
	laser_cannon->LaserTermYPos(mBoundries.mTop * 1.05f);
	laser_cannon->ProjectileSpeed(sh * 0.050f);
	laser_cannon->CooldownTime(100.0f);
	Renderer* renderer = new Renderer(mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG], GL_FILL);
	Collider* collider = new Collider();
	mPlayer = new Player();
	mPlayer->AddRenderer(renderer);
	mPlayer->AddShape(ship);
	mPlayer->AddCollider(collider);
	mPlayer->AttachCannon(laser_cannon);
	mPlayer->Scale(sw*0.015f);
	mPlayer->Translate(glm::vec3(sw/2.0f, sh*0.08f, 0.0f));
	laser_cannon->Translate(glm::vec3(1.0f, sh * 0.05f, 0.0f)); // adjust laser cannon
	
#ifdef COLLISION_DEBUG
	Shape* detection_circle = new Shape();
	detection_circle->Buffer(mShapeData[Constants::Types::shape_t::CIRCLE]);
	mPlayer->AddShape(detection_circle);
#endif
}

void SpaceDefender::InitAstroids()
{
	Shape* astroid = new Shape();
	astroid->Buffer(mShapeData[Constants::Types::shape_t::CIRCLE]);

	mAstroidSpawner = new AstroidSpawner(astroid, mShaders[Constants::Types::shader_prog_t::DEFAULT_SHADER_PROG]);
	float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	mAstroidSpawner->MaxProjectileSpeed(sw*0.30f);
	mAstroidSpawner->MinProjectileSpeed(sw*0.025f);
	mAstroidSpawner->MaxScale(sw*0.05f);
	mAstroidSpawner->MinScale(sw*0.03f);
	mAstroidSpawner->MinRespawnWaitTime(100);
	mAstroidSpawner->MaxRespawnWaitTime(700);
	mAstroidSpawner->ProbabilityOfSpawn(10.0f);
	mAstroidSpawner->MaxXPos(mBoundries.mRight - (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->MinXPos(mBoundries.mLeft + (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->StartingYPos(mBoundries.mTop + (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->TerminateYPos(mBoundries.mBottom - (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	
	
}

void SpaceDefender::InitCollisionDetection()
{
	mCollisionDetector = new CollisionDetector();
	mAstroidSpawner->AddObserver(mCollisionDetector);
	mPlayer->AddObserver(mCollisionDetector);
}

void SpaceDefender::InitKeyStateMap()
{
	mKeyStateMap.AddKey(GLFW_KEY_ESCAPE);
	mKeyStateMap.AddKey(GLFW_KEY_SPACE);
	mKeyStateMap.AddKey(GLFW_KEY_A);
	mKeyStateMap.AddKey(GLFW_KEY_LEFT);
	mKeyStateMap.AddKey(GLFW_KEY_D);
	mKeyStateMap.AddKey(GLFW_KEY_RIGHT);
}

void SpaceDefender::HandleInput()
{
	UpdateKeyStates();
	if (mKeyStateMap[GLFW_KEY_ESCAPE].mState == KEY_STATE::DOWN || mKeyStateMap[GLFW_KEY_ESCAPE].mState == KEY_STATE::PRESSED)
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}

	HandleLeftMovement();
	HandleRightMovement();
	if (!MoveLeft() && !MoveRight() && mPlayer->Boost() > 1.0f)
	{
		mPlayer->Boost(1.0f);
	}

	if (mKeyStateMap[GLFW_KEY_SPACE].mState == KEY_STATE::DOWN || mKeyStateMap[GLFW_KEY_SPACE].mState == KEY_STATE::PRESSED)
	{
		mPlayer->FireCannon();
	}

}

void SpaceDefender::HandleLeftMovement()
{
	if (MoveLeft())
	{
		mPlayer->Strafe(DIRECTION::LEFT);
		if (UseBoost(GLFW_KEY_A) || UseBoost(GLFW_KEY_LEFT))
		{
			mPlayer->Boost(2.0f);
		}
	}
}

void SpaceDefender::HandleRightMovement()
{
	if (MoveRight())
	{
		mPlayer->Strafe(DIRECTION::RIGHT);
		if (UseBoost(GLFW_KEY_D) || UseBoost(GLFW_KEY_RIGHT))
		{
			mPlayer->Boost(2.0f);
		}
	}
}


bool SpaceDefender::KeyDown(const int& key)
{
	return mKeyStateMap[key].mState == KEY_STATE::DOWN || mKeyStateMap[key].mState == KEY_STATE::PRESSED;
}

bool SpaceDefender::MoveLeft()
{
	return KeyDown(GLFW_KEY_A) || KeyDown(GLFW_KEY_LEFT);
}

bool SpaceDefender::MoveRight()
{
	return KeyDown(GLFW_KEY_D) || KeyDown(GLFW_KEY_RIGHT);
}

bool SpaceDefender::UseBoost(const int& key)
{
	return mPlayer->Boost() < 2.0f && ((float)duration_cast<milliseconds>(high_resolution_clock::now() - mKeyStateMap[key].mLastChanged).count() > mBoostChargeTime);
}


void SpaceDefender::UpdateKeyStates()
{
	KeyStateMap::iterator iter = mKeyStateMap.Begin();
	while (iter != mKeyStateMap.End())
	{
		switch (glfwGetKey(mWindow, iter->first))
		{
		case GLFW_PRESS:
			switch (iter->second.mState)
			{
			case KEY_STATE::UNKNOWN:
			case KEY_STATE::RELEASED:
			case KEY_STATE::UP:
				iter->second.mState = KEY_STATE::PRESSED;
				iter->second.mLastChanged = high_resolution_clock::now();
				break;
			default:
				iter->second.mState = KEY_STATE::DOWN;
				break;
			}
			break;
		case GLFW_RELEASE:
			if (iter->second.mState == KEY_STATE::RELEASED)
			{
				iter->second.mState = KEY_STATE::UP;
			}
			else
			{
				iter->second.mState = KEY_STATE::RELEASED;
				iter->second.mLastChanged = high_resolution_clock::now();
			}
			
			break;
		case GLFW_REPEAT:
			iter->second.mState = KEY_STATE::DOWN;
			break;
		}
		++iter;
	}
}

float SpaceDefender::TimeSinceKeyChangeMs(const int& key)
{
	return (float)duration_cast<milliseconds>(high_resolution_clock::now() - mKeyStateMap[key].mLastChanged).count();
}