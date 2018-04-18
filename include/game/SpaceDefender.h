#ifndef SPACE_DEFENDER_INCLUDED
#define SPACE_DEFENDER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<glm/gtc/matrix_transform.hpp>
#include"engine/util/OpenGLOptions.h"
#include"engine/shapes/TriangleData.h"
#include"engine/shapes/CircleData.h"
#include"engine/shapes/QuadData.h"
#include"engine/shapes/LineSegmentData.h"
#include"engine/util/BoundryBox.h"
#include"game/Player.h"
#include"game/AstroidSpawner.h"
#include"game/CollisionDetector.h"

class SpaceDefender
{
public:
	SpaceDefender(const OpenGLOptions&);
	~SpaceDefender();

	void Init(); ///< Creates space defender environment and 
	void Run();
	Player* GetPlayer();
	GLFWwindow* GetWindow();
	void Update(const float&);
	void Render();
	void DoCollisionDetection();
protected:
	OpenGLOptions mOptions;
	Player* mPlayer;
	GLFWwindow* mWindow;
	ShapeData* mShapeData[Constants::Types::shape_t::TOTAL_SHAPES];
	ShaderProgram* mShaders[Constants::Types::shader_prog_t::TOTAL_SHADERS];
	AstroidSpawner* mAstroidSpawner;
	CollisionDetector* mCollisionDetector;
	BoundryBox mBoundries;
	glm::mat4 mViewMat;
	glm::mat4 mProjMat;
	void InitSys();
	void InitBoundries();
	void InitShapeData();
	void InitShapes();
	void InitShaders();
	void InitPlayer();
	void InitAstroids();
	void InitCollisionDetection();



};



#endif
