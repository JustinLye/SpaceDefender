#include"game/SpaceDefender.h"

namespace sd_app {
namespace game {
namespace impl {
namespace space_defender {

SpaceDefender::SpaceDefender(const OpenGLOptions& opts) :
	mOptions(opts),
	mPlayer(nullptr),
	mWindow(nullptr),
	mAsteroidSpawner(nullptr),
	mTracker(nullptr),
	mViewMat(IDENTITY_MATRIX),
	mProjMat(IDENTITY_MATRIX),
	mScoreText(nullptr),
	mGameState(game_state_t::INIT_GAME_STATE),
	mBackground(nullptr),
  mLastObjectInfoPrinted(NOT_AN_OBJECT)
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
	InitFonts();
	InitUI();
	InitTextures();
	InitBackground();
	InitTracker();
	InitPlayer();
	InitAsteroids();
	InitExplosions();
	InitEnemyShips();
	InitCollisionDetection();
}

void SpaceDefender::Run()
{
	mScoreText->Message("Score: ");
	mGameState = game_state_t::ACTIVE_GAMEPLAY;
	Button* button = new Button();
	QuadData* quad_data = new QuadData();
	Shape* button_shape = new Shape();
	button_shape->Buffer(quad_data);
	Text* button_text = new Text();
	button_text->FontPtr(mFont[PAUSE_FONT]);
	button_text->Scale(1.0f);
	button_text->Message("Paused");
	button_text->XBearing(mBoundries.mRight / 2.0f - 100.0f);
	button_text->YBearing(mBoundries.mTop / 2.0f - 50.0f);
	button_shape->Buffer(quad_data);
	button->AddDrawableObject(button_shape);
	button->Scale(glm::vec3(100.0f, 25.0f, 0.0f));
	button->AddRenderer(new Renderer(mShaders[DEFAULT_SHADER_PROG]));
	button->AddText(button_text);
	button->Translate(glm::vec3(mBoundries.mRight / 2.0f, mBoundries.mTop / 2.0f, 1.0f));
	button->FillColor(glm::vec4(0.3f, 0.9f, 0.3f, 0.0f));
	button->TextColor(glm::vec4(0.0f, 1.0f, 0.0f, .70f));
	button->Projection(mProjMat);
	button->View(mViewMat);

	glEnable(GL_TEXTURE_2D);

	auto begin_time = high_resolution_clock::now();
	auto last_frame_time = high_resolution_clock::now();
	auto next_frame_time = high_resolution_clock::now();
	float fps60 = 1.0f / 60.0f;
	unsigned int frame_count = 0;
	double start_time = glfwGetTime();
	double current_time = glfwGetTime();
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float refresh_rate = (float)OpenGLUtility::GetRefreshRate(mOptions.mMonitor);
	
	if (refresh_rate <= 0.0f)
	{
		throw std::runtime_error("Failed to get refresh rate\n");
	}
	std::cout << "Timer frequency " << glfwGetTimerFrequency() << '\n';
	float dt = 1.0f / refresh_rate;
	time_point<steady_clock> frame_start = high_resolution_clock::now();
	auto wait_time = milliseconds(9);
	bool show_overheat_warn = false;
	time_point<steady_clock> last_show_overheat_warn_swap = high_resolution_clock::now();
	long show_overheat_warn_interval = 175; // in milliseconds

	while (!glfwWindowShouldClose(mWindow))
	{

		double start_frame_time = glfwGetTime();
		auto now = high_resolution_clock::now().time_since_epoch();
		auto target_time = now + wait_time;
		
		switch (mGameState)
		{
		case game_state_t::ACTIVE_GAMEPLAY:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			if (!glfwGetWindowAttrib(mWindow, GLFW_FOCUSED))
			{
				mGameState = game_state_t::PAUSED;
				continue;
			}
			HandleInput();
			Update(dt);
			DoCollisionDetection(dt);
			if (mPlayer->GunOverHeated())
			{
				if (duration_cast<milliseconds>(high_resolution_clock::now() - last_show_overheat_warn_swap).count() > show_overheat_warn_interval)
				{
					show_overheat_warn = !show_overheat_warn;
					last_show_overheat_warn_swap = high_resolution_clock::now();
				}
			}
			else
			{
				show_overheat_warn = false;
			}
			if (show_overheat_warn)
			{
				mWarningMessage->Message("GUN IS OVERHEATED!");
			}
			else
			{
				mWarningMessage->Message("");
			}
			mGunTempText->Message("Gun Temp: " + std::to_string((int)mPlayer->CurrentGunTemp()));
			Render();
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
			break;
		case game_state_t::PAUSED:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			if (glfwGetWindowAttrib(mWindow, GLFW_FOCUSED) && glfwGetInputMode(mWindow, GLFW_CURSOR) != GLFW_CURSOR_NORMAL)
			{
				glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			HandleInput();
			Render();
			if (mPlayer->GunOverHeated())
			{
				mWarningMessage->Message("GUN IS OVERHEATED!!");
			} else
			{
				mWarningMessage->Message("");
				mGunTempText->Message("Gun Temp: " + std::to_string((int)mPlayer->CurrentGunTemp()));
			}
			button->Render();
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
			break;
		}
		++frame_count;
		if (duration_cast<milliseconds>(high_resolution_clock::now() - begin_time).count() >= 999)
		{
			mFPSText->Message(std::string("FPS: ") + std::to_string(frame_count));
			frame_count = 0;
			begin_time = high_resolution_clock::now();
		}
		std::this_thread::sleep_until(time_point<steady_clock>(target_time));
		//std::cout << "frame time: " << (glfwGetTime() - start_frame_time) * 1000.0f << " ms.\n";
		
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

void SpaceDefender::Update(float dt)
{
	mPlayer->Update(dt);
	mAsteroidSpawner->Update(dt);
	mExplosionManager->Update(dt);
	mEnemyShipManager->Update(dt);
	mBackground->Update(dt);
}

void SpaceDefender::Render()
{
	mPlayer->Render(mProjMat, mViewMat);
	mAsteroidSpawner->Render(mProjMat, mViewMat);
	mExplosionManager->Render(mProjMat, mViewMat);
	mEnemyShipManager->Render(mProjMat, mViewMat);
	mCanvas->Render();
	mBackground->Render(IDENTITY_MATRIX, IDENTITY_MATRIX);
}

void SpaceDefender::DoCollisionDetection(float dt)
{
	mCollisionDetector->DoDetection(dt);
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

	mProjMat = glm::ortho(0.0f, mBoundries.mRight, 0.0f, mBoundries.mTop, 0.01f, 1000.0f);
	mViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void SpaceDefender::InitShapeData()
{
	mShapeData[shape_t::CIRCLE] = new CircleData();
	mShapeData[shape_t::LINE_SEG] = new LineSegmentData();
	mShapeData[shape_t::QUAD] = new QuadData();
	mShapeData[shape_t::TRIANGLE] = new TriangleData();
}

void SpaceDefender::InitShapes()
{
}

void SpaceDefender::InitShaders()
{
	mShaders[shader_prog_t::DEFAULT_SHADER_PROG] = new ShaderProgram();
	mShaders[shader_prog_t::DEFAULT_SHADER_PROG]->Init();
	mShaders[shader_prog_t::TEXT_SHADER_PROG] = new TextShader();
	mShaders[shader_prog_t::TEXT_SHADER_PROG]->Init();
	mShaders[shader_prog_t::TEXT_SHADER_PROG]->Use();
	glUniformMatrix4fv((*mShaders[shader_prog_t::TEXT_SHADER_PROG])(TEXT_PROJ_UNIFORM_NAME), 1, GL_FALSE, glm::value_ptr(mProjMat));
	mShaders[shader_prog_t::TEXT_SHADER_PROG]->UnUse();
	mShaders[shader_prog_t::TEXTURE_SHADER_PROG] = new TextureShader();
	mShaders[shader_prog_t::TEXTURE_SHADER_PROG]->Init();
	glUniform1i((*(mShaders[shader_prog_t::TEXTURE_SHADER_PROG]))(TEXTURE_SAMPLER_NAME), 0);

	
}

void SpaceDefender::InitFonts()
{
	mFontData[font_data_t::ARIAL_FONT_DATA] = new ArialFontData();
	
	mFont[font_t::SCORE_FONT] = new Font();
	mFont[font_t::SCORE_FONT]->Data(mFontData[font_data_t::ARIAL_FONT_DATA]);
	mFont[font_t::SCORE_FONT]->Shader(mShaders[shader_prog_t::TEXT_SHADER_PROG]);
	mFont[font_t::SCORE_FONT]->Color(SCORE_TEXT_COLOR);
	mFont[font_t::SCORE_FONT]->Projection(glm::ortho(mBoundries.mLeft, mBoundries.mRight, mBoundries.mBottom, mBoundries.mTop));
	mFont[font_t::SCORE_FONT]->Init();

	mFont[font_t::PAUSE_FONT] = new Font();
	mFont[font_t::PAUSE_FONT]->Data(mFontData[font_data_t::ARIAL_FONT_DATA]);
	mFont[font_t::PAUSE_FONT]->Shader(mShaders[shader_prog_t::TEXT_SHADER_PROG]);
	mFont[font_t::PAUSE_FONT]->Color(SCORE_TEXT_COLOR);
	mFont[font_t::PAUSE_FONT]->Projection(glm::ortho(mBoundries.mLeft, mBoundries.mRight, mBoundries.mBottom, mBoundries.mTop));
	mFont[font_t::PAUSE_FONT]->Init();

	
	
}

void SpaceDefender::InitUI()
{
	mScoreText = new ScoreText();
	mScoreText->XBearing(mBoundries.mLeft + mBoundries.mRight * 0.05f);
	mScoreText->YBearing(mBoundries.mLeft + mBoundries.mTop * 0.95f);
	mScoreText->Scale(1.0f);
	mScoreText->FontPtr(mFont[font_t::SCORE_FONT]);

	mFPSText = new ScoreText();
	mFPSText->XBearing(mBoundries.mLeft + mBoundries.mRight * 0.05f);
	mFPSText->YBearing(mBoundries.mBottom + mBoundries.mTop * 0.05f);
	mFPSText->Scale(0.5);
	mFPSText->FontPtr(mFont[font_t::SCORE_FONT]);

	mGunTempText = new ScoreText();
	mGunTempText->XBearing(mBoundries.mLeft + mBoundries.mRight * 0.85f);
	mGunTempText->YBearing(mBoundries.mBottom + mBoundries.mTop * 0.05f);
	mGunTempText->Scale(0.50f);
	mGunTempText->FontPtr(mFont[font_t::SCORE_FONT]);

	mWarningMessage = new ScoreText();
	mWarningMessage->XBearing(mBoundries.mLeft + mBoundries.mRight * 0.33f);
	mWarningMessage->YBearing(mBoundries.mBottom + mBoundries.mTop * 0.45f);
	mWarningMessage->Scale(1.2f);
	mWarningMessage->FontPtr(mFont[font_t::SCORE_FONT]);

	mCanvas = new Canvas();
	mCanvas->AddUIObject(mScoreText);
	mCanvas->AddUIObject(mFPSText);
	mCanvas->AddUIObject(mGunTempText);
	mCanvas->AddUIObject(mWarningMessage);
}

void SpaceDefender::InitTextures()
{
	for (int i = 0; i < texture_t::TOTAL_GAME_TEXTURES; ++i)
	{
		mTextures[i] = new Texture();
	}
	mTextures[texture_t::PLAYER_SHIP]->LoadFromFile(EngineTexPath(PLAYER_SHIP_TEXTURE_FILENAME));
	mTextures[texture_t::GREEN_LASER]->LoadFromFile(EngineTexPath(GREEN_LASER_TEXTURE_FILENAME));
	mTextures[texture_t::WHITE_LASER]->LoadFromFile(EngineTexPath(WHITE_LASER_TEXTURE_FILE_NAME));
	mTextures[texture_t::BRIGHTNESS_STEPS_LASER]->LoadFromFile(EngineTexPath(BRIGHTNESS_STEPS_LASER_TEXTURE_FILE_NAME));
	mTextures[texture_t::CARTOON_ASTEROID]->LoadFromFile(EngineTexPath(CARTOON_ASTEROID_TEXTURE_FILENAME));
	mTextures[texture_t::SPACE_BACKGROUND]->LoadFromFile(EngineTexPath(SPACE_BACKGROUND_TEXTURE_FILENAME));
	mTextures[texture_t::SPACE_BACKGROUND2]->LoadFromFile(EngineTexPath(SPACE_BACKGROUND2_TEXTURE_FILENAME));
	mTextures[texture_t::EXPLOSION]->LoadFromFile(EngineTexPath(EXPLOSION_TEXTURE_FILENAME));
	mTextures[texture_t::LASER_EXPLOSION]->LoadFromFile(EngineTexPath(LASER_EXPLOSION_TEXTURE_FILENAME));
	mTextures[texture_t::ENEMY_SHIP_TEXTURE]->LoadFromFile(EngineTexPath(ENEMY_SHIP_TEXTURE_FILENAME));
}

void SpaceDefender::InitBackground()
{
	mBackground = new ScrollingBackground();
	mBackground->ScrollSpeed(0.10f * (1.0f / 60.0f));
	mBackground->MaxYOffset(2.15f);
	Transform transform;
	transform.Offset(glm::vec3(0.0f, -2.50f, 0.0f));
	mBackground->StartingPosition(transform);

	GameObject* b1 = new GameObject();
	GameObject* b2 = new GameObject();
	GameObject* b3 = new GameObject();

	b1->AddRenderer(new TexRenderer(mShaders[shader_prog_t::TEXTURE_SHADER_PROG]));
	b1->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND]);
	b1->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND2]);
	b2->AddRenderer(new TexRenderer(mShaders[shader_prog_t::TEXTURE_SHADER_PROG]));
	b2->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND]);
	b2->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND2]);
	b3->AddRenderer(new TexRenderer(mShaders[shader_prog_t::TEXTURE_SHADER_PROG]));
	b3->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND]);
	b3->AddDrawableObject(mTextures[texture_t::SPACE_BACKGROUND2]);

	b2->Offset(glm::vec3(0.0f, -1.75f, 0.0f));
	b3->Offset(glm::vec3(0.0f, -2.75f, 0.0f));

	mBackground->AddBackground(b1);
	mBackground->AddBackground(b2);
	mBackground->AddBackground(b3);


}

void SpaceDefender::InitPlayer()
{
	float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	float sh = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);

	// Setup laser cannon
	
	LaserCannon* laser_cannon = new LaserCannon(mTextures[texture_t::BRIGHTNESS_STEPS_LASER], mShaders[shader_prog_t::TEXTURE_SHADER_PROG]);
	laser_cannon->LaserTermYPos(mBoundries.mTop * 1.01f);
	laser_cannon->ProjectileSpeed(sh * 0.10f);
	laser_cannon->CooldownTime(80.0f);
	TexRenderer* renderer = new TexRenderer(mShaders[shader_prog_t::TEXTURE_SHADER_PROG], { GL_FILL, GL_FILL });
	Collider* collider = new Collider();
	RigidBody* rb = new RigidBody();
	mPlayer = new Player();
	mPlayer->AddRenderer(renderer);
	mPlayer->AddDrawableObject(mTextures[texture_t::PLAYER_SHIP]);
#ifdef COLLISION_DEBUG
	Shape* detection_circle = new Shape();
	detection_circle->Buffer(mShapeData[shape_t::CIRCLE]);
	mPlayer->AddDrawableObject(detection_circle);
#endif
	mPlayer->AddCollider(collider);
	mPlayer->AddRigidBody(rb);
	mPlayer->Mass(0.65f);
	mPlayer->Damping(0.75f);
	mPlayer->AttachCannon(laser_cannon);
	mPlayer->Scale(sw*0.025f);
	mPlayer->Translate(glm::vec3(sw/2.0f, sh*0.09f, 0.0f));
	laser_cannon->Translate(glm::vec3(1.0f, sh * 0.05f, 0.0f)); // adjust laser cannon
	laser_cannon->Scale(0.5f);
	laser_cannon->AddObserver(mTracker);
}

void SpaceDefender::InitTracker()
{
	mTracker = new ActiveObjectTracker();
}

void SpaceDefender::InitAsteroids()
{

	mAsteroidSpawner = new AsteroidSpawner(mTextures[texture_t::CARTOON_ASTEROID], mShaders[shader_prog_t::TEXTURE_SHADER_PROG]);
	float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	float sh = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);
	//mAsteroidSpawner->MaxProjectileSpeed(sw*0.010f);
	//mAsteroidSpawner->MinProjectileSpeed(sw*0.0005f);
	mAsteroidSpawner->MaxProjectileSpeed(sh*0.010f);
	mAsteroidSpawner->MinProjectileSpeed(sh*0.0005f);
	mAsteroidSpawner->MaxScale(sw*0.03f);
	mAsteroidSpawner->MinScale(sw*0.005f);
	mAsteroidSpawner->MinRespawnWaitTime(100);
	mAsteroidSpawner->MaxRespawnWaitTime(700);
	mAsteroidSpawner->MinHitPoints(3);
	mAsteroidSpawner->MaxHitPoints(9);
	mAsteroidSpawner->MaxRotationSpeed(1.0f);
	mAsteroidSpawner->MinRotationSpeed(-1.0f);
	mAsteroidSpawner->ProbabilityOfSpawn(20.0f);
	mAsteroidSpawner->MaxXPos(mBoundries.mRight - (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAsteroidSpawner->MinXPos(mBoundries.mLeft + (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAsteroidSpawner->StartingYPos(mBoundries.mTop + (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.075f));
	mAsteroidSpawner->TerminateYPos(mBoundries.mBottom - (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	mAsteroidSpawner->AddObserver(mScoreText);
	mAsteroidSpawner->AddObserver(mTracker);
	
}

void SpaceDefender::InitExplosions()
{
	mExplosionManager = new ExplosionManager(mTextures[texture_t::LASER_EXPLOSION], mShaders[shader_prog_t::TEXTURE_SHADER_PROG]);
	mExplosionManager->ExpansionSpeed(mBoundries.mRight*0.02f);
	mExplosionManager->MaxExpansion(mBoundries.mRight*0.012f);
	mExplosionManager->MinExpansion(mBoundries.mRight*0.00075f);
	mExplosionManager->InitScale(mBoundries.mRight*0.0005f);
	mPlayer->AddObserver(mExplosionManager);
}

void SpaceDefender::InitEnemyShips()
{
	mEnemyShipManager = new EnemyShipManager(mTextures[texture_t::ENEMY_SHIP_TEXTURE], mShaders[shader_prog_t::TEXTURE_SHADER_PROG]);
	float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
	float sh = OpenGLUtility::GetScreenHeight(mOptions.mMonitor);
	mEnemyShipManager->MaxProjectileSpeed(sh*0.00020f);
	mEnemyShipManager->MinProjectileSpeed(sh*0.00020f);
	mEnemyShipManager->ShipScale(glm::vec3(sw*0.02f));
	mEnemyShipManager->MinRespawnWaitTime(600);
	mEnemyShipManager->MaxRespawnWaitTime(2000);
	mEnemyShipManager->HitPoints(2);
	mEnemyShipManager->ProbabilityOfSpawn(10.0f);
	mEnemyShipManager->MaxXPos(mBoundries.mRight - (sw * 0.05f));
	mEnemyShipManager->MinXPos(mBoundries.mLeft + (sw *0.05f));
	//mEnemyShipManager->StartingYPos(mBoundries.mTop + (sh * 0.075f));
	mEnemyShipManager->StartingYPos(mBoundries.mTop - (sh * 0.075f));
	mEnemyShipManager->TerminateYPos(mBoundries.mBottom - (sh * 0.05f));
	mEnemyShipManager->MaxPlacementAttempts(5);
	mEnemyShipManager->AddObserver(mScoreText);
	mEnemyShipManager->AddObserver(mTracker);
	mEnemyShipManager->AddActiveObjectTracker(mTracker);
}

void SpaceDefender::InitCollisionDetection()
{
	mCollisionDetector = new CollisionDetector();
	mAsteroidSpawner->AddObserver(mCollisionDetector);
	mPlayer->AddObserver(mCollisionDetector);
	mEnemyShipManager->AddObserver(mCollisionDetector);
}

void SpaceDefender::InitKeyStateMap()
{
	mKeyStateMap.AddKey(GLFW_KEY_ESCAPE);
	mKeyStateMap.AddKey(GLFW_KEY_SPACE);
	mKeyStateMap.AddKey(GLFW_KEY_A);
	mKeyStateMap.AddKey(GLFW_KEY_LEFT);
	mKeyStateMap.AddKey(GLFW_KEY_D);
	mKeyStateMap.AddKey(GLFW_KEY_RIGHT);
	mKeyStateMap.AddKey(GLFW_KEY_UP);
}

void SpaceDefender::HandleInput()
{
	UpdateKeyStates();
	if (mKeyStateMap[GLFW_KEY_P].mState == KEY_STATE::PRESSED)
	{
		if (mGameState == game_state_t::ACTIVE_GAMEPLAY)
		{
			mGameState = game_state_t::PAUSED;
			glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else if (mGameState == game_state_t::PAUSED)
		{
			mGameState = game_state_t::ACTIVE_GAMEPLAY;
			glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	if (mKeyStateMap[GLFW_KEY_ESCAPE].mState == KEY_STATE::PRESSED && mGameState == game_state_t::PAUSED)
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
		return;
	}
	if (mGameState == game_state_t::ACTIVE_GAMEPLAY)
	{
		HandleLeftMovement();
		HandleRightMovement();
		if (!MoveLeft() && !MoveRight() && mPlayer->Boost() > 1.0f)
		{
			mPlayer->Boost(1.0f);
		}

		if (mKeyStateMap[GLFW_KEY_SPACE].mState == KEY_STATE::DOWN || mKeyStateMap[GLFW_KEY_SPACE].mState == KEY_STATE::PRESSED)
		{
			mPlayer->FireCannon();
		} else if (KeyDown(GLFW_KEY_UP))
		{
			mPlayer->FireCannon();
		}
	}
	if (mGameState == game_state_t::PAUSED)
	{
    MouseHoverObjectInfo();
	}

}

void SpaceDefender::MouseHoverObjectInfo() const {
  double xpos = 0.0;
  double ypos = 0.0;
  glfwGetCursorPos(mWindow, &xpos, &ypos);
  if (xpos >= mBoundries.mLeft && xpos <= mBoundries.mRight && ypos >= mBoundries.mBottom && ypos <= mBoundries.mTop) {
    Transform transform;
    transform.Translate(glm::vec3(xpos, mBoundries.mTop - ypos, 0.0f));
    float sw = OpenGLUtility::GetScreenWidth(mOptions.mMonitor);
    transform.Scale(sw * 0.002f);
    std::vector<const GameObject*> close_objects;
    mTracker->ObjectScan(transform, close_objects);
    if (close_objects.size() > 0 && close_objects[0]->Id() != mLastObjectInfoPrinted) {
      mLastObjectInfoPrinted = close_objects[0]->Id();
      std::cout << "Object: " << TypeToString(close_objects[0]->Type()) << '\t' << close_objects[0]->GetTransform() << '\n';
    }
  }
}

void SpaceDefender::HandleLeftMovement()
{
	if (MoveLeft())
	{
		mPlayer->Strafe(direction_t::LEFT);
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
		mPlayer->Strafe(direction_t::RIGHT);
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

} // namespace space_defender
} // namespace impl
} // namespace game
} // namespace sd_app