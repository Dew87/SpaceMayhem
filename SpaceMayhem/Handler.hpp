#ifndef HANDLER_HPP
#define HANDLER_HPP

class Event;

class Handler
{
public:
	virtual ~Handler() {};
	virtual void handle(Event *event) = 0;
};

#endif
