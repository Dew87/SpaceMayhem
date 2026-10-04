#include "Bullet.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Explosion.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Render.hpp"
#include "Spawn.hpp"
#include "Tick.hpp"
#include <string>

static float RADIUS;
static float SPEED;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Texture TEXTURE;

Bullet::Bullet(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction) : Solid(context, position, direction, TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT)
{}

void Bullet::initialize(const std::string &file)
{
	const Configuration CONFIGURATION(file);

	RADIUS = (float)CONFIGURATION.getReal("RADIUS");
	SPEED = (float)CONFIGURATION.getReal("SPEED");
	TEXTURE.loadFromFile(CONFIGURATION.getString("TEXTURE"));
	X_FRAME_COUNT = CONFIGURATION.getInteger("X_FRAME_COUNT");
	X_FRAME_WIDTH = TEXTURE.getSize().x / X_FRAME_COUNT;
	Y_FRAME_COUNT = CONFIGURATION.getInteger("Y_FRAME_COUNT");
	Y_FRAME_HEIGHT = TEXTURE.getSize().y / Y_FRAME_COUNT;
}

void Bullet::finalize()
{}

void Bullet::handle(Event *event)
{
	if (Tick *tick = dynamic_cast<Tick*>(event))
	{
		mPosition += mDirection * SPEED;
	}
	else if (Render *render = dynamic_cast<Render*>(event))
	{
		if (render->getLayer() == Render::BACKGROUND)
		{
			mSprite.setPosition(mPosition);
			render->getWindow().draw(mSprite);
		}
	}
	else if (Hit *hit = dynamic_cast<Hit*>(event))
	{
		mContext->post(new Spawn(new Explosion(mContext, mPosition)));
		mContext->post(new Kill(this, mContext));
	}
}

float Bullet::getRadius() const
{
	return RADIUS;
}
