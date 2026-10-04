#ifndef SOLID_HPP
#define SOLID_HPP

#include "Entity.hpp"

class Solid : public Entity
{
public:
	const sf::Vector2f& getPosition() const;
	virtual float getRadius() const = 0;

protected:
	Solid(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction, const sf::Texture &texture, int xFrameWidth, int yFrameHeight);
	sf::Vector2f mDirection;
	sf::Vector2f mPosition;
};

#endif
