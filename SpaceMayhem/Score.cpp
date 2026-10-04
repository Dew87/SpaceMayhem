#include "Score.hpp"

Score::Score(const int score) : mScore(score)
{}

int Score::getScore() const
{
	return mScore;
}
