#ifndef GAME_HPP
#define GAME_HPP

#include "Context.hpp"
#include <queue>
#include <set>
#include <SFML/Graphics.hpp>

class Entity;
class Event;

class Game : public Context
{
public:
	Game();
	virtual ~Game();
	virtual void handle(Event *event);
	virtual void post(Event *event);
	virtual void run();
	static void initialize(const std::string &file);
	static void finalize();

private:
	typedef std::set<Entity*> Entities;
	typedef std::queue<Event*> Events;

	void dispatch();
	void handleHits();
	void handleNewEntities();
	void handleOldEntities();
	void handleWorldEdge();
	void kill(Entities &entities);
	void kill(Events &events);
	void render();
	void spawnObjects();

	Entities mEntities;
	Entities mNewEntities;
	Entities mOldEntities;
	Events mEvents;
	sf::RenderWindow mWindow;

	bool mGameOver;
	int mScore;
};

#endif
