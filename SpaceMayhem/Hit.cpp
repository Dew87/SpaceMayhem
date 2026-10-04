#include "Hit.hpp"
#include "Entity.hpp"

Hit::Hit(Entity *entity0, Entity *entity1) : mEntity0(entity0), mEntity1(entity1)
{
	mReceivers.insert(entity0);
	mReceivers.insert(entity1);
}

Entity* Hit::getEntity0() const
{
	return mEntity0;
}

Entity* Hit::getEntity1() const
{
	return mEntity1;
}
