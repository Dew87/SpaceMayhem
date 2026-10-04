#include "Explosion.hpp"
#include "Configuration.hpp"
#include "Context.hpp"
#include "Kill.hpp"
#include "Render.hpp"
#include "Tick.hpp"

static int ALIVE_TIME;
static int TICS_PER_FRAME;
static int X_FRAME_COUNT;
static int X_FRAME_WIDTH;
static int Y_FRAME_COUNT;
static int Y_FRAME_HEIGHT;
static sf::Texture TEXTURE;

Explosion::Explosion(Context *context, const sf::Vector2f &position) : Entity(context, position, TEXTURE, X_FRAME_WIDTH, Y_FRAME_HEIGHT), mTimer(0), mXFrameIndex(0)
{}

void Explosion::initialize(const std::string &file)
{
	const Configuration CONFIGURATION(file);

	ALIVE_TIME = CONFIGURATION.getInteger("ALIVE_TIME");
	TICS_PER_FRAME = CONFIGURATION.getInteger("TICS_PER_FRAME");
	TEXTURE.loadFromFile(CONFIGURATION.getString("TEXTURE"));
	X_FRAME_COUNT = CONFIGURATION.getInteger("X_FRAME_COUNT");
	X_FRAME_WIDTH = TEXTURE.getSize().x / X_FRAME_COUNT;
	Y_FRAME_COUNT = CONFIGURATION.getInteger("Y_FRAME_COUNT");
	Y_FRAME_HEIGHT = TEXTURE.getSize().y / Y_FRAME_COUNT;
}

void Explosion::finalize()
{}

void Explosion::handle(Event *event)
{
	if (Tick *tick = dynamic_cast<Tick*>(event))
	{
		++mTimer;
		mXFrameIndex = (mTimer / TICS_PER_FRAME) % X_FRAME_COUNT;
		if (mTimer > ALIVE_TIME)
		{
			mContext->post(new Kill(this, mContext));
		}
	}
	else if (Render *render = dynamic_cast<Render*>(event))
	{
		if (render->getLayer() == Render::MIDDLEGROUND)
		{
			sf::IntRect frame(sf::Vector2i(mXFrameIndex * X_FRAME_WIDTH, 0), sf::Vector2i(X_FRAME_WIDTH, Y_FRAME_HEIGHT));
			mSprite.setTextureRect(frame);
			render->getWindow().draw(mSprite);
		}
	}
}
