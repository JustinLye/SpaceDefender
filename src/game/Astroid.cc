#include"game/Astroid.h"

Astroid::Astroid() :
	GameObject(),
	mSpeed(0.0f)
{

}

Astroid::~Astroid()
{

}

const float& Astroid::Speed() const
{
	return mSpeed;
}

const float& Astroid::TerminateYPos() const
{
	return mTerminateYPos;
}

void Astroid::Speed(const float& speed)
{
	mSpeed = speed;
}

void Astroid::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
}

void Astroid::Update(const float& dt)
{
	Translate(glm::vec3(0.0f, -dt * mSpeed, 0.0f));
}

bool Astroid::Terminate() const
{
	float term_ypos = mTerminateYPos;
	float curr_ypos = Position().y;
	return (std::abs(term_ypos) > 0.0f && ((term_ypos > 0.0f && curr_ypos > term_ypos) || (term_ypos < 0.0f && curr_ypos < term_ypos)));
}