#include "Game.hpp"
#include "Configuration.hpp"
#include "Destroyer.hpp"
#include "Bullet.hpp"
#include "Explosion.hpp"
#include "Fighter.hpp"
#include "SmallMine.hpp"
#include "LargeMine.hpp"
#include "Shield.hpp"
#include "Ship.hpp"
#include "Death.hpp"
#include "Hit.hpp"
#include "Kill.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Spawn.hpp"
#include "Tick.hpp"
#include <sstream>

using namespace std;

static int DISPLAY_WIDTH;
static int DISPLAY_HEIGHT;
static int FRAMES_PER_SECOND;
static int SPAWN_DELTA;
static int WORLD_EDGE_DELTA;
static double DESTROYER_PROBABILITY;
static double FIGHTER_PROBABILITY;
static double LARGE_MINE_PROBABILITY;
static double SMALL_MINE_PROBABILITY;
static double SHIELD_PROBABILITY;
static float SHIP_START_POSITION_X;
static float SHIP_START_POSITION_Y;

static sf::Color BACKGROUND_COLOR;
static sf::Font FONT;
static string MUSIC;

/// <summary>
/// Is bullet helper function.
/// </summary>
/// <param name="entity"></param>
/// <returns></returns>
bool isBullet(Entity *entity)
{
	return 0 != dynamic_cast<Bullet*>(entity);
}

/// <summary>
/// Collision helper function.
/// </summary>
/// <param name="entity0"></param>
/// <param name="entity1"></param>
/// <returns></returns>
bool collision(Entity *entity0, Entity *entity1)
{
	bool collision = false;
	Solid *solid0 = dynamic_cast<Solid*>(entity0);
	Solid *solid1 = dynamic_cast<Solid*>(entity1);
	if ((solid0 != 0) && (solid1 != 0) && (solid0 != solid1) && !(isBullet(solid0) && isBullet(solid1)))
	{
		const sf::Vector2f &position0 = solid0->getPosition();
		const sf::Vector2f &position1 = solid1->getPosition();
		const float radius0 = solid0->getRadius();
		const float radius1 = solid1->getRadius();
		const float radiusSum = radius0 + radius1;
		const float xDelta = position0.x - position1.x;
		const float yDelta = position0.y - position1.y;
		collision = (xDelta * xDelta) + (yDelta * yDelta) < (radiusSum * radiusSum);
	}
	return collision;
}

Game::Game() : mWindow(sf::VideoMode({ (unsigned int)DISPLAY_WIDTH, (unsigned int)DISPLAY_HEIGHT }), "Space Mayhem"), mGameOver(false), mScore(0)
{
	//Audio::Stream(MUSIC);
	//Audio::SetRepeat(MUSIC, true);
	//Audio::SetVolume(MUSIC, 0.5);
	//Audio::Play(MUSIC);

	mEntities.insert(new Ship(this, sf::Vector2f(SHIP_START_POSITION_X, SHIP_START_POSITION_Y)));
}

Game::~Game()
{
	//Audio::Stop(MUSIC);

	kill(mEntities);
	kill(mNewEntities);
	kill(mEvents);
}

void Game::dispatch()
{
	while (!mEvents.empty())
	{
		Event *event = mEvents.front();
		if (event->mReceivers.empty())
		{
			handle(event);
			for (Entities::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
			{
				Entity *entity = *i;
				entity->handle(event);
			}
		}
		else
		{
			for (std::set<Handler*>::iterator i = event->mReceivers.begin(); i != event->mReceivers.end(); ++i)
			{
				Handler *handler = *i;
				handler->handle(event);
			}
		}
		mEvents.pop();
		delete event;
	}
}

void Game::finalize()
{
	Bullet::finalize();
	Destroyer::finalize();
	Explosion::finalize();
	Fighter::finalize();
	LargeMine::finalize();
	Shield::finalize();
	Ship::finalize();
	SmallMine::finalize();
}

void Game::handle(Event *event)
{
	if (Tick *tick = dynamic_cast<Tick*>(event))
	{
		spawnObjects();
	}
	else if (Spawn *spawn = dynamic_cast<Spawn*>(event))
	{
		mNewEntities.insert(spawn->getEntity());
	}
	else if (Kill *kill = dynamic_cast<Kill*>(event))
	{
		mOldEntities.insert(kill->getEntity());
	}
	else if (Death *death = dynamic_cast<Death*>(event))
	{
		mGameOver = true;
		mScore = death->getScore();
	}
	else if (mGameOver)
	{
		if (Render *render = dynamic_cast<Render*>(event))
		{
			if (render->getLayer() == Render::FOREGROUND)
			{
				stringstream score;
				score << "You Scored " << mScore;

				const sf::Color scoreColor(255, 255, 255, 255);
				const sf::Vector2f scoreOrigin(0.5, 0.5);
				const sf::Vector2f scorePosition(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

				sf::Text text(FONT, score.str(), 30);
				text.setOrigin(scoreOrigin);
				text.setPosition(scorePosition);

				render->getWindow().draw(text);
			}
		}
	}
}

void Game::handleHits()
{
	for (Entities::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
	{
		for (Entities::iterator j = i; j != mEntities.end(); ++j)
		{
			Entity *entity0 = *i;
			Entity *entity1 = *j;
			if (collision(entity0, entity1))
			{
				post(new Hit(entity0, entity1));
			}
		}
	}
}

void Game::handleNewEntities()
{
	for (Entities::iterator i = mNewEntities.begin(); i != mNewEntities.end(); ++i)
	{
		Entity *entity = *i;
		mEntities.insert(entity);
	}
	mNewEntities.clear();
}

void Game::handleOldEntities()
{
	for (Entities::iterator i = mOldEntities.begin(); i != mOldEntities.end(); ++i)
	{
		Entity *entity = *i;
		mEntities.erase(entity);
		delete entity;
	}
	mOldEntities.clear();
}

void Game::handleWorldEdge()
{
	for (Entities::iterator i = mEntities.begin(); i != mEntities.end(); ++i)
	{
		Entity *entity = *i;
		Solid *solid = dynamic_cast<Solid*>(entity);
		if (dynamic_cast<Solid*>(entity))
		{
			const sf::Vector2f &position = solid->getPosition();
			const float x = position.x;
			if (x < -WORLD_EDGE_DELTA || DISPLAY_WIDTH + WORLD_EDGE_DELTA < x)
			{
				post(new Kill(entity, this));
			}
			const float y = position.y;
			if (y < -WORLD_EDGE_DELTA || DISPLAY_HEIGHT + WORLD_EDGE_DELTA < y)
			{
				post(new Kill(entity, this));
			}
		}
	}
}

void Game::initialize(const std::string &file)
{
	const Configuration CONFIGURATION(file);

	DISPLAY_WIDTH = CONFIGURATION.getInteger("DISPLAY_WIDTH");
	DISPLAY_HEIGHT = CONFIGURATION.getInteger("DISPLAY_HEIGHT");
	FRAMES_PER_SECOND = CONFIGURATION.getInteger("FRAMES_PER_SECOND");
	SPAWN_DELTA = CONFIGURATION.getInteger("SPAWN_DELTA");
	WORLD_EDGE_DELTA = CONFIGURATION.getInteger("WORLD_EDGE_DELTA");
	DESTROYER_PROBABILITY = CONFIGURATION.getReal("DESTROYER_PROBABILITY") / FRAMES_PER_SECOND;
	FIGHTER_PROBABILITY = CONFIGURATION.getReal("FIGHTER_PROBABILITY") / FRAMES_PER_SECOND;
	LARGE_MINE_PROBABILITY = CONFIGURATION.getReal("LARGE_MINE_PROBABILITY") / FRAMES_PER_SECOND;
	SMALL_MINE_PROBABILITY = CONFIGURATION.getReal("SMALL_MINE_PROBABILITY") / FRAMES_PER_SECOND;
	SHIELD_PROBABILITY = CONFIGURATION.getReal("SHIELD_PROBABILITY") / FRAMES_PER_SECOND;
	SHIP_START_POSITION_X = (float)(DISPLAY_WIDTH / 2);
	SHIP_START_POSITION_Y = (float)(DISPLAY_HEIGHT / 2);

	BACKGROUND_COLOR.r = CONFIGURATION.getInteger("BACKGROUND_COLOR_R");
	BACKGROUND_COLOR.g = CONFIGURATION.getInteger("BACKGROUND_COLOR_G");
	BACKGROUND_COLOR.b = CONFIGURATION.getInteger("BACKGROUND_COLOR_B");
	BACKGROUND_COLOR.a = CONFIGURATION.getInteger("BACKGROUND_COLOR_A");
	FONT.openFromFile(CONFIGURATION.getString("FONT"));
	MUSIC = CONFIGURATION.getString("MUSIC");;

	Bullet::initialize("lua\\Bullet.lua");
	Destroyer::initialize("lua\\Destroyer.lua", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	Explosion::initialize("lua\\Explosion.lua");
	Fighter::initialize("lua\\Fighter.lua", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	LargeMine::initialize("lua\\LargeMine.lua");
	Shield::initialize("lua\\Shield.lua");
	Ship::initialize("lua\\Ship.lua", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	SmallMine::initialize("lua\\SmallMine.lua");
}

void Game::kill(Entities &entities)
{
	for (Entities::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		Entity *entity = *i;
		delete entity;
	}
	entities.clear();
}

void Game::kill(Events &events)
{
	while (!events.empty())
	{
		Event *event = events.front();
		events.pop();
		delete event;
	}
}

void Game::post(Event *event)
{
	mEvents.push(event);
}

void Game::render()
{
	mWindow.clear(BACKGROUND_COLOR);
	post(new Render(Render::BACKGROUND, mWindow));
	post(new Render(Render::MIDDLEGROUND, mWindow));
	post(new Render(Render::FOREGROUND, mWindow));
	dispatch();
	mWindow.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time frameTime(sf::microseconds(1000000 / FRAMES_PER_SECOND));
	sf::Time nextFrame;

	while (mWindow.isOpen())
	{
		while (const std::optional event = mWindow.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				mWindow.close();
			}
		}

		post(new Tick());
		dispatch();
		handleHits();
		handleWorldEdge();
		dispatch();
		handleNewEntities();
		handleOldEntities();
		render();

		nextFrame += frameTime;
		sf::sleep(nextFrame - clock.getElapsedTime());
	}
}

void Game::spawnObjects()
{
	if (Random::getBool(DESTROYER_PROBABILITY))
	{
		sf::Vector2f position = sf::Vector2f(DISPLAY_WIDTH / 2, -SPAWN_DELTA);
		post(new Spawn(new Destroyer(this, position)));
	}
	if (Random::getBool(FIGHTER_PROBABILITY))
	{
		sf::Vector2f position = sf::Vector2f((float)Random::getInt(0, DISPLAY_WIDTH), (float)-SPAWN_DELTA);
		sf::Vector2f direction = sf::Vector2f(0, 1);
		post(new Spawn(new Fighter(this, position, direction)));
	}
	if (Random::getBool(LARGE_MINE_PROBABILITY))
	{
		sf::Vector2f position = sf::Vector2f((float)Random::getInt(0, DISPLAY_WIDTH), (float)-SPAWN_DELTA);
		sf::Vector2f direction = sf::Vector2f(0, 1);
		post(new Spawn(new LargeMine(this, position, direction)));
	}
	if (Random::getBool(SMALL_MINE_PROBABILITY))
	{
		sf::Vector2f position = sf::Vector2f((float)Random::getInt(0, DISPLAY_WIDTH), (float)-SPAWN_DELTA);
		sf::Vector2f direction = sf::Vector2f(0, 1);
		post(new Spawn(new SmallMine(this, position, direction)));
	}
	if (Random::getBool(SHIELD_PROBABILITY))
	{
		sf::Vector2f position = sf::Vector2f((float)Random::getInt(0, DISPLAY_WIDTH), (float)-SPAWN_DELTA);
		sf::Vector2f direction = sf::Vector2f(0, 1);
		post(new Spawn(new Shield(this, position, direction)));
	}
}
