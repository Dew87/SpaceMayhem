#ifndef DEATH_HPP
#define DEATH_HPP

#include "Event.hpp"

class Context;

class Death : public Event
{
public:
	Death(const int score, Context *receiver);
	int getScore() const;

private:
	const int mScore;
};

#endif
