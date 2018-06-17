#include"engine/objects/ScrollingBackground.h"

ScrollingBackground::ScrollingBackground() :
	GameObject(),
	mScrollOffsetVec(glm::vec3(0.0f)),
	mMaxYOffset(0.0f),
	mStartingPosition(Transform())
{

}

ScrollingBackground::~ScrollingBackground()
{

}


void ScrollingBackground::Update(const float& dt)
{
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator iter = mGameObjectMap.begin();
	std::map<GameObject*, GameObject*, CompareGameObjectPtr>::iterator end_iter = mGameObjectMap.end();

	while (iter != end_iter)
	{
		GameObject* ptr = iter->second;
		ptr->Offset(mScrollOffsetVec);
		if (ptr->Offset().y >= mMaxYOffset)
		{
			ptr->Match(mStartingPosition);
		}
		++iter;
	}
}

void ScrollingBackground::AddBackground(GameObject* bg)
{
	AddGameObject(bg);
}

void ScrollingBackground::ScrollSpeed(const float& speed)
{
	mScrollOffsetVec.y = speed;
}

void ScrollingBackground::MaxYOffset(const float& offset)
{
	mMaxYOffset = offset;
}

void ScrollingBackground::StartingPosition(const Transform& transform)
{
	mStartingPosition = transform;
}

const float& ScrollingBackground::ScrollSpeed() const
{
	return mScrollOffsetVec.y;
}

const float& ScrollingBackground::MaxYOffset() const
{
	return mMaxYOffset;
}

const Transform& ScrollingBackground::StartingPosition() const
{
	return mStartingPosition;
}
