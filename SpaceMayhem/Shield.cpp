#include "Shield.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Render.hpp"
#include "Tick.hpp"

static float RADIUS;
static float SPEED;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Texture TEXTURE;

Shield::Shield(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction) : PowerUp(context, position, direction, TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT)
{}

void Shield::initialize(const std::string &file)
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

void Shield::finalize()
{}

void Shield::handle(Event *event)
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
		mContext->post(new Kill(this, mContext));
	}
}

float Shield::getRadius() const
{
	return RADIUS;
}
