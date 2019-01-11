#include"game/ScoreText.h"
namespace sd_app {
namespace game {
namespace impl {
namespace score_text {
ScoreText::ScoreText() :
	Text(),
	mPoints(0)
{

}

ScoreText::~ScoreText()
{

}

void ScoreText::OnNotify(const GameObject& object, const event_t& event_name)
{
	switch (event_name)
	{
  case event_t::PLAYER_DESTROYED_ASTEROID:
		++mPoints;
		mMessage = std::string("Score: ") + std::to_string(mPoints);
		break;
	}
}

} // namespace score_text
} // namespace impl
} // namespace game
} // namespace sd_app