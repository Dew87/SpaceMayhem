#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include "Solid.hpp"
#include <string>

class Fighter : public Solid
{
public:
	Fighter(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file, int displayWidth, int displayHeight);
	static void finalize();

private:
	int mReload;
	int mTurn;
};

#endif
