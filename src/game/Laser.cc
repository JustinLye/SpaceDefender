#include"game/Laser.h"

Laser::Laser() :
	GameObject()
{

}

Laser::~Laser()
{

}

void Laser::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	RenderShapes(proj_mat, view_mat);
}

void Laser::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
}

const float& Laser::TerminateYPos() const
{
	return mTerminateYPos;
}

bool Laser::Terminate() const
{
	float term_ypos = mTerminateYPos;
	float curr_ypos = Position().y;
	return (std::abs(term_ypos) > 0.0f && ((term_ypos > 0.0f && curr_ypos > term_ypos) || (term_ypos < 0.0f && curr_ypos < term_ypos)));
}

void Laser::Update(const float& dt)
{
	static int counter = 61;
	Translate(glm::vec3(0.0f, dt*10.0f, 0.0f));
	if (counter > 60)
	{
		counter = 0;
	}
	else
	{
		++counter;
	}

}