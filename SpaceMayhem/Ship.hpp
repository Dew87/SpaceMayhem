#ifndef SHIP_HPP
#define SHIP_HPP

#include "Solid.hpp"
#include <string>

class Ship : public Solid
{
public:
	Ship(Context *context, const sf::Vector2f &position);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file, int displayWidth, int displayHeight);
	static void finalize();

private:
	int mReload;
	int mRegen;
	int mScore;
	int mShield;
};

#endif
