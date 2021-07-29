#pragma once
#include "Collidable.h"
class CircleCollider : public Collidable
{
protected:
	sf::Vector2f pos;
	float r;
public:
	CircleCollider(const sf::Vector2f& pos, float rad);

	virtual bool collides(const CircleCollider& other);
	virtual std::optional<Collision> collision(const CircleCollider& other);
	// Inherited via Collidable
	virtual bool collides(const Collidable& other) override;
	virtual std::optional<Collision> collision(const Collidable& other) override;

	const sf::Vector2f& getPos() const;
	void setPos(const sf::Vector2f& pos);
	float getR() const;
	void setR(float _r);
};

class CollidableCircle : public CircleCollider, public sf::CircleShape {
public:
	CollidableCircle(const sf::Vector2f& _pos, float _r);
	void setPos(const sf::Vector2f& pos);
	void setR(float _r);
	void move(const sf::Vector2f& m);
};