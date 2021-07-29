#pragma once
#include "../camera/Camera.h"

class Visualizer
{
protected:
	sf::RenderWindow& window;
	sf::Time dT = sf::seconds(0);

	Camera cam;

	void captureEvent(const sf::Event& event);
	virtual void update() = 0;
	virtual void draw() const = 0;


public:
	Visualizer(sf::RenderWindow& _window);

	virtual void loop() = 0;

};

