#include"game/Laser.h"
namespace sd_app {
namespace game {
namespace impl {
namespace laser {
Laser::Laser() :
	GameObject(),
	mColor(DFLT_SHAPE_COLOR)
{

}

Laser::~Laser()
{

}

void Laser::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
	RenderDrawableObjects(proj_mat, view_mat);
}

void Laser::TerminateYPos(float ypos)
{
	mTerminateYPos = ypos;
}

void Laser::Color(const glm::vec4& color)
{
	mColor = color;
}

float Laser::TerminateYPos() const
{
	return mTerminateYPos;
}

const glm::vec4& Laser::Color() const
{
	return mColor;
}

bool Laser::Terminate() const
{
	float term_ypos = mTerminateYPos;
	float curr_ypos = Position().y;
	return (std::abs(term_ypos) > 0.0f && ((term_ypos > 0.0f && curr_ypos > term_ypos) || (term_ypos < 0.0f && curr_ypos < term_ypos)));
}

object_t Laser::Type() const
{
	return object_t::LASER;
}

void Laser::Collide(const GameObject& object) const
{
	switch (object.Type())
	{
	case object_t::ASTEROID:
	case object_t::ENEMY_SHIP:
		Despawn();
		break;
	}
}

void Laser::Update(float dt)
{
	Translate(glm::vec3(0.0f, dt*10.0f, 0.0f));
}
} // namespace laser
} // namespace impl
} // namespace game
} // namespace sd_app