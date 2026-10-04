#ifndef BULLET_HPP
#define BULLET_HPP

#include "Solid.hpp"
#include <string>

class Bullet : public Solid
{
public:
	Bullet(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file);
	static void finalize();
};

#endif
