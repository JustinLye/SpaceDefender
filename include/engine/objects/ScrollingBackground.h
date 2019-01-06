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
	void Update(float) override;
	void AddBackground(GameObject*);

	void ScrollSpeed(float);
	void MaxYOffset(float);
	void StartingPosition(const Transform&);

	float ScrollSpeed() const;
	float MaxYOffset() const;
	const Transform& StartingPosition() const;

protected:
	glm::vec3 mScrollOffsetVec;
	float mMaxYOffset;
	Transform mStartingPosition;
};

/*@}*/

#endif // !SCROLLING_BACKGROUND_HEADER_INCLUDED
