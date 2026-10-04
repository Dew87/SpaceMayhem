#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Handler.hpp"
#include <SFML/Graphics.hpp>

class Context;

class Entity : public Handler
{
protected:
	Entity(Context *context, const sf::Vector2f &position, const sf::Texture &texture, int xFrameWidth, int yFrameHeight);
	Context *mContext;
	sf::Sprite mSprite;
};

#endif
