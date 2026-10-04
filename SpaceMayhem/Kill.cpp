#include "Kill.hpp"
#include "Context.hpp"

Kill::Kill(Entity *entity, Context *receiver) : mEntity(entity)
{
	mReceivers.insert(receiver);
}

Entity* Kill::getEntity() const
{
	return mEntity;
}
