#include "Solid.hpp"

Solid::Solid(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction, const sf::Texture &texture, int xFrameWidth, int yFrameHeight) : Entity(context, position, texture, xFrameWidth, yFrameHeight), mDirection(direction), mPosition(position)
{}

const sf::Vector2f& Solid::getPosition() const
{
	return mPosition;
}
