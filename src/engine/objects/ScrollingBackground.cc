#include"engine/objects/ScrollingBackground.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace scrolling_background {
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


void ScrollingBackground::Update(float dt)
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

void ScrollingBackground::ScrollSpeed(float speed)
{
	mScrollOffsetVec.y = speed;
}

void ScrollingBackground::MaxYOffset(float offset)
{
	mMaxYOffset = offset;
}

void ScrollingBackground::StartingPosition(const Transform& transform)
{
	mStartingPosition = transform;
}

float ScrollingBackground::ScrollSpeed() const
{
	return mScrollOffsetVec.y;
}

float ScrollingBackground::MaxYOffset() const
{
	return mMaxYOffset;
}

const Transform& ScrollingBackground::StartingPosition() const
{
	return mStartingPosition;
}
} // namespace scrolling_background
} // namespace impl
} // namespace objects
} // namespace engine
} // namespace sd_app