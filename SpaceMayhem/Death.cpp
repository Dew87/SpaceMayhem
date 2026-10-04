#include "Death.hpp"
#include "Context.hpp"

Death::Death(const int score, Context *receiver) : mScore(score)
{
	mReceivers.insert(receiver);
}

int Death::getScore() const
{
	return mScore;
}
