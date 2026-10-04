#include "Entity.hpp"

Entity::Entity(Context *context, const sf::Vector2f &position, const sf::Texture &texture, int xFrameWidth, int yFrameHeight) : mContext(context), mSprite(texture, sf::IntRect(sf::Vector2i(), sf::Vector2i(xFrameWidth, yFrameHeight)))
{
	mSprite.setOrigin(sf::Vector2f((float)xFrameWidth * 0.5f, (float)yFrameHeight * 0.5f));
	mSprite.setPosition(position);
}
