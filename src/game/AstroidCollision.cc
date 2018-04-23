#include"game/AstroidCollision.h"

AstroidCollision::AstroidCollision(const unsigned int& astroid_1, const unsigned int& astroid_2) :
	GameObject(),
	mAstroid_1(astroid_1),
	mAstroid_2(astroid_2)
{

}

AstroidCollision::~AstroidCollision()
{

}

std::pair<const unsigned int&, const unsigned int&> AstroidCollision::GetAstroidIds() const
{
	return std::pair<const unsigned int&, const unsigned int&>(mAstroid_1, mAstroid_2);
}