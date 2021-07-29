#pragma once
#include "../visualizer/Visualizer.h"
#include "../collisions/CircleCollider.h"
#include "../utils/Line.hpp"

//#define SHOW_ACC

class Body : public CollidableCircle {
	sf::Vector2f vel, acc;
	float mass;

#ifdef SHOW_ACC
	selbaward::Line line;
#endif

public:
	Body(const sf::Vector2f& _pos, const sf::Vector2f& _vel, float _r);

	void update(sf::Time dT);
	sf::Vector2f getGravityPull(const sf::Vector2f& p) const;
	void setAcc(const sf::Vector2f& a);
	float getMass() const;


#ifdef SHOW_ACC
	const selbaward::Line& getLine() const;
#endif
};


class Orbit : public Visualizer
{
protected:
	std::vector<Body> bodies;

	bool eraseCollisions = false, gravity = false;

	// Tool
	mutable sf::CircleShape circleTool;
	bool addingCircle = false;
	float currentR = 100.0f;

	// ImGUI
	float speed = 1.0f;

	virtual void captureEvents();
	virtual void update() override;
	virtual void draw() const override;

public:
	Orbit(sf::RenderWindow& _window, size_t nCircles, float radius, float cSize);

	virtual void loop() override;

};

