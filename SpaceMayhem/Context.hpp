#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Handler.hpp"

class Event;

class Context : public Handler
{
public:
	virtual void post(Event *event) = 0;
	virtual void run() = 0;
};

#endif
