#include"game/SpaceDefender.h"

SpaceDefender::SpaceDefender(const OpenGLOptions& opts) :
	mOptions(opts),
	mPlayer(nullptr),
	mAstroidSpawner(nullptr)
{

}

SpaceDefender::~SpaceDefender()
{
}

void SpaceDefender::Init()
{
	InitSys();
	InitShapeData();
	InitShapes();
	InitShaders();
	InitPlayer();
	InitAstroids();
}

Player* SpaceDefender::GetPlayer()
{

}

void SpaceDefender::Update(const float& dt)
{
	mPlayer->Update(dt);
	mAstroidSpawner->Update(dt);
	
}

void SpaceDefender::InitSys()
{
	OpenGLUtility::Init();
	OpenGLUtility::InitWindow(mOptions);
}

void SpaceDefender::InitShapeData()
{

	mShapeData[Constants::shape_t::CIRCLE] = new CircleData();
	mShapeData[Constants::shape_t::LINE_SEG] = new LineSegmentData();
	mShapeData[Constants::shape_t::QUAD] = new QuadData();
	mShapeData[Constants::shape_t::TRIANGLE] = new TriangleData();
}

void SpaceDefender::InitShapes()
{

}

void SpaceDefender::InitShaders()
{
	mShaders[Constants::shader_prog_t::DEFAULT_SHADER_PROG] = new ShaderProgram();
	mShaders[Constants::shader_prog_t::DEFAULT_SHADER_PROG]->Init();
}

void SpaceDefender::InitPlayer()
{
	Shape* ship = new Shape();
	ship->Buffer(mShapeData[Constants::shape_t::TRIANGLE]);
	Shape* laser = new Shape();
	laser->Buffer(mShapeData[Constants::shape_t::LINE_SEG]);
	LaserCannon* laser_cannon = new LaserCannon(laser, mShaders[Constants::shader_prog_t::DEFAULT_SHADER_PROG]);
	Renderer* renderer = new Renderer(mShaders[Constants::shader_prog_t::DEFAULT_SHADER_PROG], GL_FILL);
	Collider* collider = new Collider();
	mPlayer = new Player();
	mPlayer->AddRenderer(renderer);
	mPlayer->AddShape(ship);
	mPlayer->AddCollider(collider);
	mPlayer->AttachCannon(laser_cannon);

#ifdef COLLISION_DEBUG
	Shape* detection_circle = new Shape();
	detection_circle->Buffer(mShapeData[Constants::shape_t::CIRCLE]);
	mPlayer->AddShape(detection_circle);
#endif

}

void SpaceDefender::InitAstroids()
{
	Shape* astroid = new Shape();
	astroid->Buffer(mShapeData[Constants::shape_t::CIRCLE]);

	mAstroidSpawner = new AstroidSpawner(astroid, mShaders[Constants::shader_prog_t::DEFAULT_SHADER_PROG]);
	mAstroidSpawner->MinProjectileSpeed(50.0f);
	mAstroidSpawner->MaxProjectileSpeed(100.0f);
	mAstroidSpawner->MaxScale(2.0f);
	mAstroidSpawner->MinScale(0.50f);
	mAstroidSpawner->MinRespawnWaitTime(300);
	mAstroidSpawner->MaxRespawnWaitTime(700);
	mAstroidSpawner->ProbabilityOfSpawn(30.0f);
	mAstroidSpawner->MinXPos(mBoundries.mLeft + (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->MaxXPos(mBoundries.mRight - (OpenGLUtility::GetScreenWidth(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->StartingYPos(mBoundries.mTop + (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	mAstroidSpawner->TerminateYPos(mBoundries.mBottom - (OpenGLUtility::GetScreenHeight(mOptions.mMonitor)*0.05f));
	

}