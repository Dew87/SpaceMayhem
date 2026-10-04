#ifndef SPAWN_HPP
#define SPAWN_HPP

#include "Event.hpp"

class Entity;

class Spawn : public Event
{
public:
	Spawn(Entity *entity);
	Entity* getEntity() const;

private:
	Entity *mEntity;
};

#endif
