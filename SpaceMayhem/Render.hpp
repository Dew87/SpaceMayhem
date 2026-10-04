#ifndef RENDER_HPP
#define RENDER_HPP

#include "Event.hpp"
#include <SFML/Graphics.hpp>

class Render : public Event
{
public:
	enum Layer { BACKGROUND, MIDDLEGROUND, FOREGROUND };
	Render(Layer layer, sf::RenderWindow &window);
	Layer getLayer() const;
	sf::RenderWindow& getWindow() const;

private:
	const Layer mLayer;
	sf::RenderWindow &mWindow;
};

#endif
