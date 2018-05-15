#include"game/ScoreText.h"

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
	case PLAYER_DESTROYED_ASTEROID:
		++mPoints;
		mMessage = std::string("Score: ") + boost::lexical_cast<std::string>(mPoints);
		break;
	}
}

