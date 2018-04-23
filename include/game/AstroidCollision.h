#ifndef ASTROID_COLLISION_HEADER_INCLUDED
#define ASTROID_COLLISION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/Astroid.h"

class AstroidCollision : 
	public GameObject
{
public:
	AstroidCollision(const unsigned int&, const unsigned int&);
	~AstroidCollision();
	std::pair<const unsigned int&, const unsigned int&> GetAstroidIds() const;
protected:
	unsigned int mAstroid_1;
	unsigned int mAstroid_2;
};

#endif