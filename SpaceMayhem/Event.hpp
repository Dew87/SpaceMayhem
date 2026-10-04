#ifndef EVENT_HPP
#define EVENT_HPP

#include <set>

class Handler;

class Event
{
public:
	virtual ~Event();
	std::set<Handler*> mReceivers;
};

#endif
