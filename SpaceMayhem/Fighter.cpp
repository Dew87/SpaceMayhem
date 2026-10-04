#include "Fighter.hpp"
#include "Bullet.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Explosion.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Score.hpp"
#include "Spawn.hpp"
#include "Tick.hpp"

static float BULLET_OFFSET;
static float HORIZONTAL_SPEED;
static float RADIUS;
static float SPEED;
static int DISPLAY_WIDTH;
static int DISPLAY_HEIGHT;
static int RELOAD_TIME;
static int SCORE;
static int TURN_TIME;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Texture TEXTURE;

Fighter::Fighter(Context *context, const sf::Vector2f &position, const sf::Vector2f &direction) : Solid(context, position, direction, TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT), mReload(-10), mTurn(0)
{}

void Fighter::initialize(const std::string &file, int displayWidth, int displayHeight)
{
	const Configuration CONFIGURATION(file);

	DISPLAY_WIDTH = displayWidth;
	DISPLAY_HEIGHT = displayHeight;

	BULLET_OFFSET = (float)CONFIGURATION.getReal("BULLET_OFFSET");
	HORIZONTAL_SPEED = (float)CONFIGURATION.getReal("HORIZONTAL_SPEED");
	RADIUS = (float)CONFIGURATION.getReal("RADIUS");
	SPEED = (float)CONFIGURATION.getReal("SPEED");
	RELOAD_TIME = CONFIGURATION.getInteger("RELOAD_TIME");
	SCORE = CONFIGURATION.getInteger("SCORE");
	TURN_TIME = CONFIGURATION.getInteger("TURN_TIME");
	TEXTURE.loadFromFile(CONFIGURATION.getString("TEXTURE"));
	X_FRAME_COUNT = CONFIGURATION.getInteger("X_FRAME_COUNT");
	X_FRAME_WIDTH = TEXTURE.getSize().x / X_FRAME_COUNT;
	Y_FRAME_COUNT = CONFIGURATION.getInteger("Y_FRAME_COUNT");
	Y_FRAME_HEIGHT = TEXTURE.getSize().y / Y_FRAME_COUNT;
}

void Fighter::finalize()
{}

void Fighter::handle(Event *event)
{
	if (Tick *tick = dynamic_cast<Tick*>(event))
	{
		if (mReload == 0)
		{
			++mReload;
			sf::Vector2f bulletPosition = mPosition + sf::Vector2f(0, BULLET_OFFSET);
			sf::Vector2f bullet0Direction = sf::Vector2f(-1, 1);
			sf::Vector2f bullet1Direction = sf::Vector2f(0, 1);
			sf::Vector2f bullet2Direction = sf::Vector2f(1, 1);
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet0Direction)));
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet1Direction)));
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet2Direction)));
		}
		else
		{
			++mReload;
			if (mReload >= RELOAD_TIME)
			{
				mReload = 0;
			}
		}

		if (mTurn == 0)
		{
			++mTurn;
			mDirection = sf::Vector2f((float)Random::getInt(-1, 1) * HORIZONTAL_SPEED, 1.f);
		}
		else
		{
			++mTurn;
			if (mTurn >= TURN_TIME)
			{
				mTurn = 0;
			}
		}

		mPosition += mDirection * SPEED;
		if (mPosition.x < 0)
		{
			float delta = -mPosition.x;
			mPosition.x = delta;
			mDirection = sf::Vector2f(HORIZONTAL_SPEED, 1.f);
		}
		else if (DISPLAY_WIDTH < mPosition.x)
		{
			float delta = DISPLAY_WIDTH - mPosition.x;
			mPosition.x = DISPLAY_WIDTH - delta;
			mDirection = sf::Vector2f(-HORIZONTAL_SPEED, 1.f);
		}
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
		mContext->post(new Score(SCORE));
		mContext->post(new Kill(this, mContext));
	}
}

float Fighter::getRadius() const
{
	return RADIUS;
}
