#ifndef MINE_HPP
#define MINE_HPP

#include "Solid.hpp"

class Mine : public Solid
{
protected:
	Mine(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction, const sf::Texture &texture, int xFrameWidth, int yFrameHeight);
};

#endif
