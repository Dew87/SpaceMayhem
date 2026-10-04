#ifndef SCORE_HPP
#define SCORE_HPP

#include "Event.hpp"

class Score : public Event
{
public:
	Score(const int score);
	int getScore() const;

public:
	const int mScore;
};

#endif
