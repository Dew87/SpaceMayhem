#ifndef SHIELD_HPP
#define SHIELD_HPP

#include "PowerUp.hpp"
#include <string>

class Shield : public PowerUp
{
public:
	Shield(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file);
	static void finalize();
};

#endif
