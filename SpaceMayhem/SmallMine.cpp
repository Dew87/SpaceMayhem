#include "SmallMine.hpp"
#include "Bullet.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Explosion.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Render.hpp"
#include "Score.hpp"
#include "Spawn.hpp"
#include "Tick.hpp"

static float RADIUS;
static float SPEED;
static int SCORE;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Font FONT;
static sf::Texture TEXTURE;

SmallMine::SmallMine(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction) : Mine(context, position, direction, TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT)
{}

void SmallMine::initialize(const std::string &file)
{
	const Configuration CONFIGURATION(file);

	RADIUS = (float)CONFIGURATION.getReal("RADIUS");
	SPEED = (float)CONFIGURATION.getReal("SPEED");
	SCORE = CONFIGURATION.getInteger("SCORE");
	TEXTURE.loadFromFile(CONFIGURATION.getString("TEXTURE"));
	X_FRAME_COUNT = CONFIGURATION.getInteger("X_FRAME_COUNT");
	X_FRAME_WIDTH = TEXTURE.getSize().x / X_FRAME_COUNT;
	Y_FRAME_COUNT = CONFIGURATION.getInteger("Y_FRAME_COUNT");
	Y_FRAME_HEIGHT = TEXTURE.getSize().y / Y_FRAME_COUNT;
}

void SmallMine::finalize()
{}

void SmallMine::handle(Event *event)
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
		sf::Vector2f bullet0Direction = sf::Vector2f(-1, 1);
		sf::Vector2f bullet1Direction = sf::Vector2f(0, -1);
		sf::Vector2f bullet2Direction = sf::Vector2f(1, 1);
		mContext->post(new Spawn(new Bullet(mContext, mPosition, bullet0Direction)));
		mContext->post(new Spawn(new Bullet(mContext, mPosition, bullet1Direction)));
		mContext->post(new Spawn(new Bullet(mContext, mPosition, bullet2Direction)));
		mContext->post(new Spawn(new Explosion(mContext, mPosition)));
		mContext->post(new Score(SCORE));
		mContext->post(new Kill(this, mContext));
	}
}

float SmallMine::getRadius() const
{
	return RADIUS;
}
