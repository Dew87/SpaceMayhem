#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Entity.hpp"
#include <string>

class Explosion : public Entity
{
public:
	Explosion(Context *context, const sf::Vector2f &position);
	virtual void handle(Event *event);
	static void initialize(const std::string &file);
	static void finalize();

private:
	int mTimer;
	int mXFrameIndex;
};

#endif
