#ifndef DESTROYER_HPP
#define DESTROYER_HPP

#include "Solid.hpp"
#include <string>

class Destroyer : public Solid
{
public:
	Destroyer(Context *context, const sf::Vector2f &position);
	virtual float getRadius() const;
	virtual void handle(Event *event);
	static void initialize(const std::string &file, int displayWidth, int displayHeight);
	static void finalize();

private:
	int mReload;
	int mShield;
	int mTurn;
};

#endif
