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
	RenderDrawableObjects(proj_mat, view_mat);
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

const Constants::Types::object_t& Laser::Type() const
{
	return Constants::Types::object_t::LASER;
}

void Laser::Collide(const GameObject& object) const
{
	switch (object.Type())
	{
	case Constants::Types::object_t::ASTROID:
		Despawn();
		break;
	}
}

void Laser::Update(const float& dt)
{
	Translate(glm::vec3(0.0f, dt*10.0f, 0.0f));
}