#ifndef SCORE_TEXT_HEADER_INCLUDED
#define SCORE_TEXT_HEADER_INCLUDED

#include"engine/objects/Text.h"

class ScoreText :
	public Text
{
public:
	ScoreText();
	~ScoreText();
	virtual void OnNotify(const GameObject&, const event_t&) override;
protected:
	unsigned int mPoints;
};

#endif