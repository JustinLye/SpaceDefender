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
#include"engine/util/KeyMap.h"
#include"engine/util/TextShader.h"
#include"engine/font/Font.h"
#include"engine/font/ArialFontData.h"
#include"engine/objects/Text.h"
#include"engine/objects/Canvas.h"
#include"game/Player.h"
#include"game/AstroidSpawner.h"
#include"game/CollisionDetector.h"
#include"game/ScoreText.h"

using namespace Constants::Input;
using namespace Constants::Types;
using namespace Constants::Font;
using namespace Constants::Shaders;
using namespace Constants::Rendering;
using namespace std::chrono;

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
	void DoCollisionDetection(const float&);

protected:
	
	OpenGLOptions mOptions;
	Player* mPlayer;
	GLFWwindow* mWindow;
	ShapeData* mShapeData[shape_t::TOTAL_SHAPES];
	ShaderProgram* mShaders[shader_prog_t::TOTAL_SHADERS];
	AstroidSpawner* mAstroidSpawner;
	CollisionDetector* mCollisionDetector;
	BoundryBox mBoundries;
	glm::mat4 mViewMat;
	glm::mat4 mProjMat;
	KeyStateMap mKeyStateMap;
	float mBoostChargeTime;
	FontData* mFontData[font_data_t::TOTAL_FONT_DATA_TYPES];
	Font* mFont[font_t::TOTAL_GAME_FONT_TYPES];
	ScoreText* mScoreText;
	Canvas* mCanvas;
	game_state_t mGameState;

	void InitSys();
	void InitBoundries();
	void InitShapeData();
	void InitShapes();
	void InitShaders();
	void InitFonts();
	void InitUI();
	void InitPlayer();
	void InitAstroids();
	void InitCollisionDetection();
	void InitKeyStateMap();
	void HandleInput();
	void UpdateKeyStates();

	void HandleLeftMovement();
	void HandleRightMovement();
	bool MoveLeft();
	bool MoveRight();
	bool KeyDown(const int&);
	bool UseBoost(const int&);
	float TimeSinceKeyChangeMs(const int&);

};



#endif
