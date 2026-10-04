#include "Ship.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Bullet.hpp"
#include "Shield.hpp"
#include "Death.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Render.hpp"
#include "Score.hpp"
#include "Shared.hpp"
#include "Spawn.hpp"
#include "Tick.hpp"
#include <string>
#include <sstream>

using namespace std;

static float BULLET_OFFSET;
static float RADIUS;
static float SPEED;
static int DISPLAY_WIDTH;
static int DISPLAY_HEIGHT;
static int FONT_SIZE;
static int RELOAD_TIME;
static int REGEN_TIME;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Font FONT;
static sf::Texture TEXTURE;

Ship::Ship(Context *context, const sf::Vector2f &position) : Solid(context, position, sf::Vector2f(), TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT), mReload(0), mRegen(0), mScore(0), mShield(100)
{}

void Ship::initialize(const std::string &file, int displayWidth, int displayHeight)
{
	const Configuration CONFIGURATION(file);

	DISPLAY_WIDTH = displayWidth;
	DISPLAY_HEIGHT = displayHeight;

	BULLET_OFFSET = (float)CONFIGURATION.getReal("BULLET_OFFSET");
	RADIUS = (float)CONFIGURATION.getReal("RADIUS");
	SPEED = (float)CONFIGURATION.getReal("SPEED");
	FONT_SIZE = CONFIGURATION.getInteger("FONT_SIZE");
	RELOAD_TIME = CONFIGURATION.getInteger("RELOAD_TIME");
	REGEN_TIME = CONFIGURATION.getInteger("REGEN_TIME");
	FONT.openFromFile(CONFIGURATION.getString("FONT"));
	TEXTURE.loadFromFile(CONFIGURATION.getString("TEXTURE"));
	X_FRAME_COUNT = CONFIGURATION.getInteger("X_FRAME_COUNT");
	X_FRAME_WIDTH = TEXTURE.getSize().x / X_FRAME_COUNT;
	Y_FRAME_COUNT = CONFIGURATION.getInteger("Y_FRAME_COUNT");
	Y_FRAME_HEIGHT = TEXTURE.getSize().y / Y_FRAME_COUNT;
}

void Ship::finalize()
{}

void Ship::handle(Event *event)
{
	if (Tick *tick = dynamic_cast<Tick*>(event))
	{
		if (mShield < 100)
		{
			++mRegen;
			if (mRegen >= REGEN_TIME)
			{
				++mShield;
				mRegen = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && mPosition.y - RADIUS >= 0)
		{
			sf::Vector2f mDirection(0, -1);
			mPosition += mDirection * SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && mPosition.x - RADIUS >= 0)
		{
			sf::Vector2f mDirection(-1, 0);
			mPosition += mDirection * SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && mPosition.y + RADIUS <= DISPLAY_HEIGHT)
		{
			sf::Vector2f mDirection(0, 1);
			mPosition += mDirection * SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && mPosition.x + RADIUS <= DISPLAY_WIDTH)
		{
			sf::Vector2f mDirection(1, 0);
			mPosition += mDirection * SPEED;
		}
		if (mReload != 0)
		{
			++mReload;
			if (mReload >= RELOAD_TIME)
			{
				mReload = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			++mReload;
			sf::Vector2f bulletPosition = mPosition + sf::Vector2f(0, -BULLET_OFFSET);
			sf::Vector2f bullet0Direction = sf::Vector2f(-1, -1);
			sf::Vector2f bullet1Direction = sf::Vector2f(0, -1);
			sf::Vector2f bullet2Direction = sf::Vector2f(1, -1);
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet0Direction)));
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet1Direction)));
			mContext->post(new Spawn(new Bullet(mContext, bulletPosition, bullet2Direction)));
		}
	}
	else if (Render *render = dynamic_cast<Render*>(event))
	{
		if (render->getLayer() == Render::BACKGROUND)
		{
			mSprite.setPosition(mPosition);
			render->getWindow().draw(mSprite);
		}
		else if (render->getLayer() == Render::FOREGROUND)
		{
			stringstream score;
			score << "Score : " << mScore;

			const sf::Color scoreColor(255, 255, 255, 255);
			const sf::Vector2f scoreOrigin(0, 0);
			const sf::Vector2f scorePosition(0, 0);

			sf::Text scoreText(FONT, score.str(), 30);
			scoreText.setOrigin(scoreOrigin);
			scoreText.setPosition(scorePosition);

			stringstream shield;
			shield << "Shield : " << mShield;

			const sf::Color shieldColor(255, 255, 255, 255);
			const sf::Vector2f shieldOrigin(0, 1);
			const sf::Vector2f shieldPosition(0, DISPLAY_HEIGHT - 30);

			sf::Text shieldText(FONT, shield.str(), 30);
			shieldText.setOrigin(shieldOrigin);
			shieldText.setPosition(shieldPosition);

			render->getWindow().draw(scoreText);
			render->getWindow().draw(shieldText);
		}
	}
	else if (Hit *hit = dynamic_cast<Hit*>(event))
	{
		Shield *shield;
		if (shield = dynamic_cast<Shield*>(hit->getEntity0()))
		{
			mShield += 10;
		}
		else if (shield = dynamic_cast<Shield*>(hit->getEntity1()))
		{
			mShield += 10;
		}
		else
		{
			mShield -= 10;
			if (mShield <= 0)
			{
				mContext->post(new Death(mScore, mContext));
				mContext->post(new Kill(this, mContext));
			}
		}
	}
	else if (Score *score = dynamic_cast<Score*>(event))
	{
		mScore += score->getScore();
	}
}

float Ship::getRadius() const
{
	return RADIUS;
}
