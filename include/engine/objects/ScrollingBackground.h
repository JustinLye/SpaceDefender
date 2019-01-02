#ifndef SCROLLING_BACKGROUND_HEADER_INCLUDED
#define SCROLLING_BACKGROUND_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

/** @addtogroup EngineObjects */
/*@{*/

class ScrollingBackground :
	protected GameObject
{
public:
	using GameObject::Render;
	
	ScrollingBackground();
	~ScrollingBackground();
	void Update(const float&) override;
	void AddBackground(GameObject*);

	void ScrollSpeed(const float&);
	void MaxYOffset(const float&);
	void StartingPosition(const Transform&);

	const float& ScrollSpeed() const;
	const float& MaxYOffset() const;
	const Transform& StartingPosition() const;

protected:
	glm::vec3 mScrollOffsetVec;
	float mMaxYOffset;
	Transform mStartingPosition;
};

/*@}*/

#endif // !SCROLLING_BACKGROUND_HEADER_INCLUDED
