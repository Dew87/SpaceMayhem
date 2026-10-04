#ifndef SMALL_MINE_HPP
#define SMALL_MINE_HPP

#include "Mine.hpp"
#include <string>

class SmallMine : public Mine
{
public:
	SmallMine(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file);
	static void finalize();
};

#endif
