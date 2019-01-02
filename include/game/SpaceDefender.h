#ifndef SPACE_DEFENDER_INCLUDED
#define SPACE_DEFENDER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<thread>
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
#include"engine/objects/Button.h"
#include"engine/graphics/TextureShader.h"
#include"engine/objects/TexRenderer.h"
#include"engine/objects/ScrollingBackground.h"
#include"game/Player.h"
#include"game/AsteroidSpawner.h"
#include"game/CollisionDetector.h"
#include"game/ScoreText.h"
#include"game/ExplosionManager.h"
#include"game/EnemyShipManager.h"
#include"game/ActiveObjectTracker.h"

using namespace Constants::Input;
using namespace Constants::Types;
using namespace Constants::Font;
using namespace Constants::Shaders;
using namespace Constants::Rendering;
using namespace std::chrono;
using namespace Constants::Geometry;

/** @addtogroup GameWorld */
/*@{*/

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
	Texture* mTextures[texture_t::TOTAL_GAME_TEXTURES];
	AsteroidSpawner* mAsteroidSpawner;
	CollisionDetector* mCollisionDetector;
	ExplosionManager* mExplosionManager;
	EnemyShipManager* mEnemyShipManager;
	ActiveObjectTracker* mTracker;
	ScrollingBackground* mBackground;

	BoundryBox mBoundries;
	glm::mat4 mViewMat;
	glm::mat4 mProjMat;
	KeyStateMap mKeyStateMap;
	float mBoostChargeTime;
	FontData* mFontData[font_data_t::TOTAL_FONT_DATA_TYPES];
	Font* mFont[font_t::TOTAL_GAME_FONT_TYPES];
	ScoreText* mScoreText;
	ScoreText* mFPSText;
	ScoreText* mGunTempText;
	ScoreText* mWarningMessage;
	Canvas* mCanvas;
	game_state_t mGameState;
  mutable unsigned int mLastObjectInfoPrinted; ///< This is the object id of the last object printed (with mouse hover feature)

	void InitSys();
	void InitBoundries();
	void InitShapeData();
	void InitShapes();
	void InitShaders();
	void InitFonts();
	void InitUI();
	void InitTextures();
	void InitBackground();
	void InitPlayer();
	void InitTracker();
	void InitAsteroids();
	void InitExplosions();
	void InitEnemyShips();
	void InitCollisionDetection();
	void InitKeyStateMap();
	void HandleInput();
	void UpdateKeyStates();
  void MouseHoverObjectInfo() const; ///< prints object info 

	void HandleLeftMovement();
	void HandleRightMovement();
	bool MoveLeft();
	bool MoveRight();
	bool KeyDown(const int&);
	bool UseBoost(const int&);
	float TimeSinceKeyChangeMs(const int&);

};

/*@}*/

#endif
