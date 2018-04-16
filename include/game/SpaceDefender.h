#ifndef SPACE_DEFENDER_INCLUDED
#define SPACE_DEFENDER_INCLUDED

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

	Player* GetPlayer();
	void Update(const float&);
	void DoCollisionDetection();
protected:
	OpenGLOptions mOptions;
	Player* mPlayer;
	ShapeData* mShapeData[Constants::shape_t::TOTAL_SHAPES];
	ShaderProgram* mShaders[Constants::shader_prog_t::TOTAL_SHADERS];
	AstroidSpawner* mAstroidSpawner;
	CollisionDetector* mCollisionDetector;
	BoundryBox mBoundries;
	void InitSys();
	void InitBoundries();
	void InitShapeData();
	void InitShapes();
	void InitShaders();
	void InitPlayer();
	void InitAstroids();



};



#endif
