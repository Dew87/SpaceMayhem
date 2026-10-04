#ifndef HIT_HPP
#define HIT_HPP

#include "Event.hpp"

class Entity;

class Hit : public Event
{
public:
	Hit(Entity *entity0, Entity *entity1);
	Entity* getEntity0() const;
	Entity* getEntity1() const;

private:
	Entity *mEntity0;
	Entity *mEntity1;
};

#endif
