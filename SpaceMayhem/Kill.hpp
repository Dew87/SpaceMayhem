#ifndef KILL_HPP
#define KILL_HPP

#include "Event.hpp"

class Entity;
class Context;

class Kill : public Event
{
public:
	Kill(Entity *entity, Context *receiver);
	Entity* getEntity() const;

private:
	Entity *mEntity;
};

#endif
