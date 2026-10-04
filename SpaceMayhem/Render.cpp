#include "Render.hpp"

Render::Render(Layer layer, sf::RenderWindow &window) : mLayer(layer), mWindow(window)
{}

Render::Layer Render::getLayer() const
{
	return mLayer;
}

sf::RenderWindow& Render::getWindow() const
{
	return mWindow;
}
