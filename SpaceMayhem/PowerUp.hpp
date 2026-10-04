#ifndef POWER_UP_HPP
#define POWER_UP_HPP

#include "Solid.hpp"

class PowerUp : public Solid
{
protected:
	PowerUp(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction, const sf::Texture &texture, int xFrameWidth, int yFrameHeight);
};

#endif
