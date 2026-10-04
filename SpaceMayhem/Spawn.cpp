#include "Spawn.hpp"

Spawn::Spawn(Entity *entity) : mEntity(entity)
{}

Entity* Spawn::getEntity() const
{
	return mEntity;
}
